#!/usr/bin/env python3
"""
Encounter Table Generator

Reads a pokeemerald(-expansion) style wild_encounters.json file and produces
an Excel file with per-species encounter percentages for each map and
encounter type.

- Uses weighted slot ratios (not equal slots).
- Groups fishing encounters by rod: old_rod, good_rod, super_rod.
"""

import json
import argparse
from pathlib import Path
from typing import Dict, List, Any
import pandas as pd

# --------- Slot ratio configuration ---------

LAND_RATIOS = [20, 20, 10, 10, 10, 10, 5, 5, 4, 4, 1, 1]
WATER_RATIOS = [60, 30, 5, 4, 1]
ROCK_SMASH_RATIOS = [60, 30, 5, 4, 1]

FISHING_RATIOS = {
    "old_rod":  [70, 30],
    "good_rod": [60, 20, 20],
    "super_rod": [40, 40, 15, 4, 1],
}


# --------- Core logic ---------

def find_fishing_groups_from_fields(fields: List[Dict[str, Any]]) -> Dict[str, List[int]]:
    """
    In the JSON, rod slot indices live in wild_encounter_groups[...]["fields"]
    next to the fishing_mons definition.
    """
    for f in fields:
        if f.get("type") == "fishing_mons":
            groups = f.get("groups")
            if not isinstance(groups, dict):
                raise ValueError("fishing_mons definition exists but has no 'groups' object.")
            return groups
    # If we reach here, no fishing groups defined
    return {}


def aggregate_weighted_species(
    mons: List[Dict[str, Any]],
    slot_weights: List[int]
) -> Dict[str, float]:
    """
    Given a list of mons and a matching list of slot weights,
    sum weights by species.
    """
    if len(mons) != len(slot_weights):
        raise ValueError(
            f"Length mismatch: {len(mons)} mons but {len(slot_weights)} weights."
        )

    species_weights: Dict[str, float] = {}
    for m, w in zip(mons, slot_weights):
        sp = m["species"]
        species_weights[sp] = species_weights.get(sp, 0) + w

    return species_weights


def species_weights_to_percentages(species_weights: Dict[str, float]) -> Dict[str, float]:
    total = sum(species_weights.values())
    if total == 0:
        return {sp: 0.0 for sp in species_weights}
    return {sp: (w / total * 100.0) for sp, w in species_weights.items()}


def process_encounter_group(group: Dict[str, Any]) -> pd.DataFrame:
    """
    Process a single wild_encounter_groups entry (with fields + encounters)
    and return a DataFrame with columns:
      map, encounter_type, group, species, percentage
    """
    fields = group.get("fields", [])
    encounters = group.get("encounters", [])
    fishing_slot_groups = find_fishing_groups_from_fields(fields)

    rows = []

    for enc in encounters:
        map_name = enc.get("map", "UNKNOWN_MAP")

        for etype, block in enc.items():
            if etype not in ("land_mons", "water_mons", "rock_smash_mons", "fishing_mons"):
                continue  # ignore other keys like base_label

            mons = block.get("mons", [])
            if not mons:
                continue

            # ---- Land / Water / Rock Smash (single 'default' group) ----
            if etype in ("land_mons", "water_mons", "rock_smash_mons"):
                if etype == "land_mons":
                    slot_weights = LAND_RATIOS
                elif etype == "water_mons":
                    slot_weights = WATER_RATIOS
                else:  # rock_smash_mons
                    slot_weights = ROCK_SMASH_RATIOS

                species_weights = aggregate_weighted_species(mons, slot_weights)
                percentages = species_weights_to_percentages(species_weights)

                for sp, pct in percentages.items():
                    rows.append({
                        "map": map_name,
                        "encounter_type": etype,
                        "group": "default",
                        "species": sp,
                        "percentage": round(pct, 4),
                    })

            # ---- Fishing (split by rod) ----
            elif etype == "fishing_mons":
                if not fishing_slot_groups:
                    raise ValueError(
                        "Encounter data has fishing_mons, but no rod groups were found in 'fields'."
                    )

                # mons is the shared fishing slot array, rods define which indices belong to which rod
                for rod_name, slot_indices in fishing_slot_groups.items():
                    if rod_name not in FISHING_RATIOS:
                        raise ValueError(f"No slot ratios defined for rod group '{rod_name}'.")

                    rod_weights = FISHING_RATIOS[rod_name]
                    if len(slot_indices) != len(rod_weights):
                        raise ValueError(
                            f"Rod '{rod_name}' has {len(slot_indices)} slots but "
                            f"{len(rod_weights)} weights configured."
                        )

                    # Build a local mons list for this rod
                    rod_mons = [mons[i] for i in slot_indices]
                    species_weights = aggregate_weighted_species(rod_mons, rod_weights)
                    percentages = species_weights_to_percentages(species_weights)

                    for sp, pct in percentages.items():
                        rows.append({
                            "map": map_name,
                            "encounter_type": "fishing_mons",
                            "group": rod_name,
                            "species": sp,
                            "percentage": round(pct, 4),
                        })

    return pd.DataFrame(rows)


def generate_encounter_table(input_path: Path, output_path: Path) -> None:
    with input_path.open("r", encoding="utf-8") as f:
        data = json.load(f)

    wild_groups = data.get("wild_encounter_groups", [])
    if not wild_groups:
        raise ValueError("No 'wild_encounter_groups' found in JSON.")

    all_frames = []
    for group in wild_groups:
        if not group.get("for_maps", False) and "encounters" not in group:
            continue
        df = process_encounter_group(group)
        all_frames.append(df)

    if not all_frames:
        raise ValueError("No encounter data could be parsed from the JSON.")

    final_df = pd.concat(all_frames, ignore_index=True)

    # Sort for nicer readability
    final_df.sort_values(
        by=["map", "encounter_type", "group", "species"],
        inplace=True
    )

    output_path.parent.mkdir(parents=True, exist_ok=True)
    final_df.to_excel(output_path, index=False)
    print(f"✅ Encounter table written to: {output_path}")


# --------- CLI ---------

def main():
    parser = argparse.ArgumentParser(
        description="Generate an encounter table XLSX from a wild_encounters.json file."
    )
    parser.add_argument(
        "input_json",
        help="Path to wild_encounters.json"
    )
    parser.add_argument(
        "output_xlsx",
        nargs="?",
        help="Path to output .xlsx file (default: same name with _encounter_table.xlsx)"
    )

    args = parser.parse_args()

    input_path = Path(args.input_json)
    if not input_path.is_file():
        raise SystemExit(f"Input file not found: {input_path}")

    if args.output_xlsx:
        output_path = Path(args.output_xlsx)
    else:
        output_path = input_path.with_name(input_path.stem + "_encounter_table.xlsx")

    generate_encounter_table(input_path, output_path)


if __name__ == "__main__":
    main()
