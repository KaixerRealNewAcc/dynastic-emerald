#include "constants/abilities.h"
#include "species_info/shared_dex_text.h"
#include "species_info/shared_front_pic_anims.h"

// Macros for ease of use.

#define EVOLUTION(...) (const struct Evolution[]) { __VA_ARGS__, { EVOLUTIONS_END }, }
#define CONDITIONS(...) ((const struct EvolutionParam[]) { __VA_ARGS__, {CONDITIONS_END} })

#define ANIM_FRAMES(...) (const union AnimCmd *const[]) { sAnim_GeneralFrame0, (const union AnimCmd[]) { __VA_ARGS__ ANIMCMD_END, }, }

#if P_FOOTPRINTS
#define FOOTPRINT(sprite) .footprint = gMonFootprint_## sprite,
#else
#define FOOTPRINT(sprite)
#endif

#if B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE
#define SHADOW(x, y, size)  .enemyShadowXOffset = x, .enemyShadowYOffset = y, .enemyShadowSize = size,
#define NO_SHADOW           .suppressEnemyShadow = TRUE,
#else
#define SHADOW(x, y, size)  .enemyShadowXOffset = 0, .enemyShadowYOffset = 0, .enemyShadowSize = 0,
#define NO_SHADOW           .suppressEnemyShadow = FALSE,
#endif

#define SIZE_32x32 1
#define SIZE_64x64 0

// Set .compressed = OW_GFX_COMPRESS
#define COMP OW_GFX_COMPRESS

#if OW_POKEMON_OBJECT_EVENTS
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
#define OVERWORLD_PAL(...)                                  \
    .overworldPalette = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPalette = DEFAULT_2(NULL, __VA_ARGS__),
#if P_GENDER_DIFFERENCES
#define OVERWORLD_PAL_FEMALE(...)                                 \
    .overworldPaletteFemale = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPaletteFemale = DEFAULT_2(NULL, __VA_ARGS__),
#else
#define OVERWORLD_PAL_FEMALE(...)
#endif //P_GENDER_DIFFERENCES
#else
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE

#define OVERWORLD_DATA(picTable, _size, shadow, _tracks, _anims)                                                                     \
{                                                                                                                                       \
    .tileTag = TAG_NONE,                                                                                                                \
    .paletteTag = OBJ_EVENT_PAL_TAG_DYNAMIC,                                                                                            \
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,                                                                                     \
    .size = (_size == SIZE_32x32 ? 512 : 2048),                                                                                         \
    .width = (_size == SIZE_32x32 ? 32 : 64),                                                                                           \
    .height = (_size == SIZE_32x32 ? 32 : 64),                                                                                          \
    .paletteSlot = PALSLOT_NPC_1,                                                                                                       \
    .shadowSize = shadow,                                                                                                               \
    .inanimate = FALSE,                                                                                                                 \
    .compressed = COMP,                                                                                                                 \
    .tracks = _tracks,                                                                                                                  \
    .oam = (_size == SIZE_32x32 ? &gObjectEventBaseOam_32x32 : &gObjectEventBaseOam_64x64),                                             \
    .subspriteTables = (_size == SIZE_32x32 ? sOamTables_32x32 : sOamTables_64x64),                                                     \
    .anims = _anims,                                                                                                                    \
    .images = picTable,                                                                                                                 \
    .affineAnims = gDummySpriteAffineAnimTable,                                                                                         \
}

#define OVERWORLD(objEventPic, _size, shadow, _tracks, _anims, ...)                                 \
    .overworldData = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),                   \
    OVERWORLD_PAL(__VA_ARGS__)

#if P_GENDER_DIFFERENCES
#define OVERWORLD_FEMALE(objEventPic, _size, shadow, _tracks, _anims, ...)                          \
    .overworldDataFemale = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),             \
    OVERWORLD_PAL_FEMALE(__VA_ARGS__)
#else
#define OVERWORLD_FEMALE(...)
#endif //P_GENDER_DIFFERENCES

#else
#define OVERWORLD(...)
#define OVERWORLD_FEMALE(...)
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_POKEMON_OBJECT_EVENTS

// Maximum value for a female Pokémon is 254 (MON_FEMALE) which is 100% female.
// 255 (MON_GENDERLESS) is reserved for genderless Pokémon.
#define PERCENT_FEMALE(percent) min(254, ((percent * 255) / 100))

#define MON_TYPES(type1, ...) { type1, DEFAULT(type1, __VA_ARGS__) }
#define MON_EGG_GROUPS(group1, ...) { group1, DEFAULT(group1, __VA_ARGS__) }

#define FLIP    0
#define NO_FLIP 1

const struct SpeciesInfo gSpeciesInfo[] =
{
    [SPECIES_NONE] =
    {
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = gFallbackPokedexText,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_TwoFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(40, 40),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(QuestionMark)
        SHADOW(-1, 0, SHADOW_SIZE_M)
    #if OW_POKEMON_OBJECT_EVENTS
        .overworldData = {
            .tileTag = TAG_NONE,
            .paletteTag = OBJ_EVENT_PAL_TAG_SUBSTITUTE,
            .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
            .size = 512,
            .width = 32,
            .height = 32,
            .paletteSlot = PALSLOT_NPC_1,
            .shadowSize = SHADOW_SIZE_M,
            .inanimate = FALSE,
            .compressed = COMP,
            .tracks = TRACKS_FOOT,
            .oam = &gObjectEventBaseOam_32x32,
            .subspriteTables = sOamTables_32x32,
            .anims = sAnimTable_Following,
            .images = sPicTable_Substitute,
            .affineAnims = gDummySpriteAffineAnimTable,
        },
    #endif
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .eggMoveLearnset = sNoneEggMoveLearnset,
    },

    #include "species_info/gen_1_families.h"
    #include "species_info/gen_2_families.h"
    #include "species_info/gen_3_families.h"
    #include "species_info/gen_4_families.h"
    #include "species_info/gen_5_families.h"
    #include "species_info/gen_6_families.h"
    #include "species_info/gen_7_families.h"
    #include "species_info/gen_8_families.h"
    #include "species_info/gen_9_families.h"

    [SPECIES_EGG] =
    {
        .frontPic = gMonFrontPic_Egg,
        .frontPicSize = MON_COORDS_SIZE(24, 24),
        .frontPicYOffset = 20,
        .backPic = gMonFrontPic_Egg,
        .backPicSize = MON_COORDS_SIZE(24, 24),
        .backPicYOffset = 20,
        .palette = gMonPalette_Egg,
        .shinyPalette = gMonPalette_Egg,
        .iconSprite = gMonIcon_Egg,
        .iconPalIndex = 1,
    },

    /* You may add any custom species below this point based on the following structure: */

    [SPECIES_CLEFABLE_MEGA] =
    {
        .baseHP        = 95,
        .baseAttack    = 80,
        .baseDefense   = 93,
        .baseSpeed     = 70,
        .baseSpAttack  = 135,
        .baseSpDefense = 110,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_FLYING),
        .catchRate = 25,
        .expYield = 242,
        .evYield_HP = 3,
        .itemRare = ITEM_MOON_STONE,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 10,
        .friendship = 140,
        .growthRate = GROWTH_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_MAGIC_GUARD, ABILITY_UNAWARE },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("Clefable"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_CLEFABLE_MEGA,
    #else
        .cryId = CRY_CLEFABLE,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_CLEFABLE,
        .categoryName = _("Fairy"),
        .height = 17,
        .weight = 423,
        .description = COMPOUND_STRING(
            "It flies by using the power of\n"
            "moonlight to control gravity within\n"
            "a radius of over 32 feet around it."),
        .frontPic = gMonFrontPic_ClefableMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 8,
        .backPic = gMonBackPic_ClefableMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_ClefableMega,
        .shinyPalette = gMonShinyPalette_ClefableMega,
        .iconSprite = gMonIcon_ClefableMega,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Clefable)
        SHADOW(5, 20, SHADOW_SIZE_S)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sClefableLevelUpLearnset,
        .teachableLearnset = sClefableTeachableLearnset,
    },

    [SPECIES_VICTREEBEL_MEGA] =
    {
        .baseHP        = 80,
        .baseAttack    = 105,
        .baseDefense   = 95,
        .baseSpeed     = 70,
        .baseSpAttack  = 135,
        .baseSpDefense = 105,
        .types = MON_TYPES(TYPE_GRASS, TYPE_POISON),
        .catchRate = 45,
        .expYield = 245,
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_CHLOROPHYLL, ABILITY_NONE, ABILITY_GLUTTONY },
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = TRUE,
        .speciesName = _("Victreebel"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_VICTREEBEL_MEGA,
    #else
        .cryId = CRY_VICTREEBEL,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_VICTREEBEL,
        .categoryName = _("Flycatcher"),
        .height = 45,
        .weight = 1255,
        .description = COMPOUND_STRING(
            "The volume of this Pokémon's acid\n"
            "has increased due to Mega Evolution,\n"
            "filling its mouth. If not careful,\n"
            "the acid will overflow and spill out."),
        .frontPic = gMonFrontPic_VictreebelMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_VictreebelMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 1,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_VictreebelMega,
        .shinyPalette = gMonShinyPalette_VictreebelMega,
        .iconSprite = gMonIcon_VictreebelMega,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Victreebel)
        SHADOW(-2, 13, SHADOW_SIZE_L)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sVictreebelLevelUpLearnset,
        .teachableLearnset = sVictreebelTeachableLearnset,
    },

    [SPECIES_STARMIE_MEGA] =
    {
        .baseHP        = 60,
        .baseAttack    = 100,
        .baseDefense   = 105,
        .baseSpeed     = 120,
        .baseSpAttack  = 130,
        .baseSpDefense = 105,
        .types = MON_TYPES(TYPE_WATER, TYPE_PSYCHIC),
        .catchRate = 60,
        .expYield = 182,
        .evYield_Speed = 2,
        .itemCommon = ITEM_STARDUST,
        .itemRare = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_3),
        .abilities = { ABILITY_PURE_POWER, ABILITY_PURE_POWER, ABILITY_PURE_POWER },
        .bodyColor = BODY_COLOR_PURPLE,
        .speciesName = _("Starmie"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_STARMIE_MEGA,
    #else
        .cryId = CRY_STARMIE,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_STARMIE,
        .categoryName = _("Mysterious"),
        .height = 23,
        .weight = 800,
        .description = COMPOUND_STRING(
            "Its movements have become more\n"
            "humanlike. Whether it's simply\n"
            "trying to communicate or wants to\n"
            "supplant humanity is unclear."),
        .frontPic = gMonFrontPic_StarmieMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_StarmieMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_StarmieMega,
        .shinyPalette = gMonShinyPalette_StarmieMega,
        .iconSprite = gMonIcon_StarmieMega,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Starmie)
        SHADOW(0, 15, SHADOW_SIZE_M)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sStarmieLevelUpLearnset,
        .teachableLearnset = sStarmieTeachableLearnset,
    },

    [SPECIES_DRAGONITE_MEGA] =
    {
        .baseHP        = 91,
        .baseAttack    = 124,
        .baseDefense   = 115,
        .baseSpeed     = 100,
        .baseSpAttack  = 145,
        .baseSpDefense = 125,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_FLYING),
        .catchRate = 45,
        .expYield = 300,
        .evYield_Attack = 3,
        .itemRare = ITEM_DRAGON_SCALE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_MULTISCALE, ABILITY_MULTISCALE, ABILITY_MULTISCALE },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Dragonite"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_DRAGONITE_MEGA,
    #else
        .cryId = CRY_DRAGONITE,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_DRAGONITE,
        .categoryName = _("Dragon"),
        .height = 22,
        .weight = 2900,
        .description = COMPOUND_STRING(
            "Mega Evolution has excessively\n"
            "powered up this Pokémon's feelings\n"
            "of kindness. It finishes off its\n"
            "opponents with mercy in its heart."),
        .frontPic = gMonFrontPic_DragoniteMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 8,
        .backPic = gMonBackPic_DragoniteMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_DragoniteMega,
        .shinyPalette = gMonShinyPalette_DragoniteMega,
        .iconSprite = gMonIcon_DragoniteMega,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Dragonite)
        SHADOW(4, 20, SHADOW_SIZE_M)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sDragoniteLevelUpLearnset,
        .teachableLearnset = sDragoniteTeachableLearnset,
    },

    [SPECIES_MEGANIUM_MEGA] =
    {
        .baseHP        = 80,
        .baseAttack    = 92,
        .baseDefense   = 115,
        .baseSpeed     = 80,
        .baseSpAttack  = 143,
        .baseSpDefense = 115,
        .types = MON_TYPES(TYPE_GRASS, TYPE_FAIRY),
        .catchRate = 45,
        .expYield = 263,
        .evYield_Defense = 1,
        .evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_GRASS),
        .abilities = { ABILITY_MEGA_SOL, ABILITY_MEGA_SOL, ABILITY_MEGA_SOL },
        .innateAbility = ABILITY_FORESTS_RAGE,
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Meganium"),
        .cryId = CRY_MEGANIUM, // CRY_MEGANIUM_MEGA,
        .natDexNum = NATIONAL_DEX_MEGANIUM,
        .categoryName = _("Herb"),
        .height = 24,
        .weight = 2010,
        .description = COMPOUND_STRING(
            "This Pokémon can fire a tremendously\n"
            "powerful Solar Beam from its four\n"
            "flowers. Another name for this is\n"
            "Mega Sol Cannon."),
        .frontPic = gMonFrontPic_MeganiumMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_MeganiumMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_MeganiumMega,
        .shinyPalette = gMonShinyPalette_MeganiumMega,
        .iconSprite = gMonIcon_MeganiumMega,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Meganium)
        //SHADOW(-1, 0, SHADOW_SIZE_M)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sMeganiumLevelUpLearnset,
        .teachableLearnset = sMeganiumTeachableLearnset,
        .formSpeciesIdTable = sMeganiumFormSpeciesIdTable,
        .formChangeTable = sMeganiumFormChangeTable,
    },

    [SPECIES_FERALIGATR_MEGA] =
    {
        .baseHP        = 85,
        .baseAttack    = 160,
        .baseDefense   = 125,
        .baseSpeed     = 88,
        .baseSpAttack  = 79,
        .baseSpDefense = 93,
        .types = MON_TYPES(TYPE_WATER, TYPE_DRAGON),
        .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 265,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 239,
    #else
        .expYield = 210,
    #endif
        .evYield_Attack = 2,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_WATER_1),
        .abilities = { ABILITY_DRAGONIZE, ABILITY_PROTECTIVE_HIDE, ABILITY_SHEER_FORCE },
        .innateAbility = ABILITY_TIDAL_WRATH,
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Feraligatr"),
        .cryId = CRY_FERALIGATR,
        .natDexNum = NATIONAL_DEX_FERALIGATR,
        .categoryName = _("Big Jaw"),
        .height = 23,
        .weight = 888,
        .description = COMPOUND_STRING(
            "It opens its huge mouth to intimidate\n"
            "enemies. In battle, it runs using its thick\n"
            "and powerful hind legs to charge the\n"
            "foe with incredible speed."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 342,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_FeraligatrMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 0 : 1,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(1, 10),
            ANIMCMD_FRAME(0, 10),
            ANIMCMD_FRAME(1, 25),
            ANIMCMD_FRAME(0, 40),
        ),
        .frontAnimId = ANIM_H_SHAKE,
        .frontAnimDelay = 5,
        .backPic = gMonBackPic_FeraligatrMega,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 64) : MON_COORDS_SIZE(56, 64),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 1 : 2,
        .backAnimId = BACK_ANIM_V_SHAKE,
        .palette = gMonPalette_FeraligatrMega,
        .shinyPalette = gMonShinyPalette_FeraligatrMega,
        .iconSprite = gMonIcon_FeraligatrMega,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 2 : 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(3, 11, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Feraligatr)
        OVERWORLD(
            sPicTable_Feraligatr,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Feraligatr,
            gShinyOverworldPalette_Feraligatr
        )
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sFeraligatrLevelUpLearnset,
        .teachableLearnset = sFeraligatrTeachableLearnset,
        .formSpeciesIdTable = sFeraligatrFormSpeciesIdTable,
        .formChangeTable = sFeraligatrFormChangeTable,
    },

    [SPECIES_SKARMORY_MEGA] =
    {
        .baseHP        = 65,
        .baseAttack    = 140,
        .baseDefense   = 110,
        .baseSpeed     = 110,
        .baseSpAttack  = 40,
        .baseSpDefense = 100,
        .types = MON_TYPES(TYPE_STEEL, TYPE_FLYING),
        .catchRate = 25,
        .expYield = 163,
        .evYield_Defense = 2,
        .itemRare = ITEM_METAL_COAT,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_KEEN_EYE, ABILITY_STURDY, ABILITY_WEAK_ARMOR },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Skarmory"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_SKARMORY_MEGA,
    #else
        .cryId = CRY_SKARMORY,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_SKARMORY,
        .categoryName = _("Armor Bird"),
        .height = 17,
        .weight = 404,
        .description = COMPOUND_STRING(
            "Due to the effects of Mega Evolution,\n"
            "its pincers have taken a more\n"
            "diabolical form, ripping anything\n"
            "they pierce to shreds."),
        .frontPic = gMonFrontPic_SkarmoryMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 6,
        .backPic = gMonBackPic_SkarmoryMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 1,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_SkarmoryMega,
        .shinyPalette = gMonShinyPalette_SkarmoryMega,
        .iconSprite = gMonIcon_SkarmoryMega,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Skarmory)
        SHADOW(2, 16, SHADOW_SIZE_M)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sSkarmoryLevelUpLearnset,
        .teachableLearnset = sSkarmoryTeachableLearnset,
    },

    [SPECIES_FROSLASS_MEGA] =
    {
        .baseHP        = 70,
        .baseAttack    = 80,
        .baseDefense   = 70,
        .baseSpeed     = 120,
        .baseSpAttack  = 140,
        .baseSpDefense = 100,
        .types = MON_TYPES(TYPE_ICE, TYPE_GHOST),
        .catchRate = 75,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 168 : 187,
        .evYield_Speed = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_SNOW_WARNING, ABILITY_SNOW_WARNING, ABILITY_SNOW_WARNING },
        .innateAbility = ABILITY_CURSED_BODY,
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Froslass"),
        .cryId = CRY_FROSLASS,
        .natDexNum = NATIONAL_DEX_FROSLASS,
        .categoryName = _("Snow Land"),
        .height = 13,
        .weight = 266,
        .description = COMPOUND_STRING(
            "When it finds people or Pokémon it likes,\n"
            "it freezes them and takes them to its\n"
            "chilly den, where they become its\n"
            "decorations."),
        .pokemonScale = 272,
        .pokemonOffset = 3,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_FroslassMega,
        .frontPicSize = MON_COORDS_SIZE(48, 48),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 9,
        .backPic = gMonBackPic_FroslassMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 1,
        .backAnimId = BACK_ANIM_CONVEX_DOUBLE_ARC,
        .palette = gMonPalette_FroslassMega,
        .shinyPalette = gMonShinyPalette_FroslassMega,
        .iconSprite = gMonIcon_FroslassMega,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 10, SHADOW_SIZE_S)
        FOOTPRINT(Froslass)
        OVERWORLD(
            sPicTable_Froslass,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Froslass,
            gShinyOverworldPalette_Froslass
        )
        .levelUpLearnset = sFroslassLevelUpLearnset,
        .teachableLearnset = sFroslassTeachableLearnset,
    },

    [SPECIES_EMBOAR_MEGA] =
    {
        .baseHP        = 110,
        .baseAttack    = 148,
        .baseDefense   = 75,
        .baseSpeed     = 75,
        .baseSpAttack  = 110,
        .baseSpDefense = 110,
        .types = MON_TYPES(TYPE_FIRE, TYPE_FIGHTING),
        .catchRate = 45,
        .expYield = 264,
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_BLAZE, ABILITY_NONE, ABILITY_RECKLESS },
        .bodyColor = BODY_COLOR_RED,
        .noFlip = TRUE,
        .speciesName = _("Emboar"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_EMBOAR_MEGA,
    #else
        .cryId = CRY_EMBOAR,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_EMBOAR,
        .categoryName = _("Fire Pig"),
        .height = 18,
        .weight = 1803,
        .description = COMPOUND_STRING(
            "Brandishing a blazing flame\n"
            "shaped like a serpentine spear,\n"
            "it rushes in to save its\n"
            "imperiled allies."),
        .frontPic = gMonFrontPic_EmboarMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_EmboarMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 1,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_EmboarMega,
        .shinyPalette = gMonShinyPalette_EmboarMega,
        .iconSprite = gMonIcon_EmboarMega,
        .iconPalIndex = 5,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Emboar)
        SHADOW(-2, 14, SHADOW_SIZE_L)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sEmboarLevelUpLearnset,
        .teachableLearnset = sEmboarTeachableLearnset,
    },

    [SPECIES_EXCADRILL_MEGA] =
    {
        .baseHP        = 110,
        .baseAttack    = 165,
        .baseDefense   = 100,
        .baseSpeed     = 103,
        .baseSpAttack  = 65,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_GROUND, TYPE_STEEL),
        .catchRate = 60,
        .expYield = 178,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_SAND_RUSH, ABILITY_SAND_FORCE, ABILITY_MOLD_BREAKER },
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = TRUE,
        .speciesName = _("Excadrill"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_EXCADRILL_MEGA,
    #else
        .cryId = CRY_EXCADRILL,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_EXCADRILL,
        .categoryName = _("Subterrene"),
        .height = 9,
        .weight = 600,
        .description = COMPOUND_STRING(
            "If this Pokémon brings its arms and\n"
            "head together to form a streamlined\n"
            "shape and spins at high speeds,\n"
            "it can destroy anything."),
        .frontPic = gMonFrontPic_ExcadrillMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_ExcadrillMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_ExcadrillMega,
        .shinyPalette = gMonShinyPalette_ExcadrillMega,
        .iconSprite = gMonIcon_ExcadrillMega,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Excadrill)
        SHADOW(5, 13, SHADOW_SIZE_XL_BATTLE_ONLY)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sExcadrillLevelUpLearnset,
        .teachableLearnset = sExcadrillTeachableLearnset,
    },

    [SPECIES_SCOLIPEDE_MEGA] =
    {
        .baseHP        = 60,
        .baseAttack    = 140,
        .baseDefense   = 149,
        .baseSpeed     = 62,
        .baseSpAttack  = 75,
        .baseSpDefense = 99,
        .types = MON_TYPES(TYPE_BUG, TYPE_POISON),
        .catchRate = 45,
        .expYield = 243,
        .evYield_Speed = 3,
        .itemRare = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_SPEED_BOOST, ABILITY_SPEED_BOOST, ABILITY_SPEED_BOOST },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Scolipede"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_SCOLIPEDE_MEGA,
    #else
        .cryId = CRY_SCOLIPEDE,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_SCOLIPEDE,
        .categoryName = _("Megapede"),
        .height = 32,
        .weight = 2305,
        .description = COMPOUND_STRING(
            "Its deadly venom gives off a faint\n"
            "glow. The venom affects Scolipede's\n"
            "mind, honing its viciousness."),
        .frontPic = gMonFrontPic_ScolipedeMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_ScolipedeMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_ScolipedeMega,
        .shinyPalette = gMonShinyPalette_ScolipedeMega,
        .iconSprite = gMonIcon_ScolipedeMega,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Scolipede)
        SHADOW(2, 14, SHADOW_SIZE_L)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sScolipedeLevelUpLearnset,
        .teachableLearnset = sScolipedeTeachableLearnset,
    },

    [SPECIES_SCRAFTY_MEGA] =
    {
        .baseHP        = 65,
        .baseAttack    = 130,
        .baseDefense   = 135,
        .baseSpeed     = 68,
        .baseSpAttack  = 55,
        .baseSpDefense = 135,
        .types = MON_TYPES(TYPE_DARK, TYPE_FIGHTING),
        .catchRate = 90,
        .expYield = 171,
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .itemRare = ITEM_SHED_SHELL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_SHED_SKIN, ABILITY_MOXIE, ABILITY_INTIMIDATE },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Scrafty"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_SCRAFTY_MEGA,
    #else
        .cryId = CRY_SCRAFTY,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_SCRAFTY,
        .categoryName = _("Hoodlum"),
        .height = 11,
        .weight = 310,
        .description = COMPOUND_STRING(
            "Mega Evolution has caused Scrafty's\n"
            "shed skin to turn white, growing\n"
            "tough and supple. Of course, this\n"
            "Pokémon is still as feisty as ever."),
        .frontPic = gMonFrontPic_ScraftyMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_ScraftyMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_ScraftyMega,
        .shinyPalette = gMonShinyPalette_ScraftyMega,
        .iconSprite = gMonIcon_ScraftyMega,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Scrafty)
        SHADOW(-4, 12, SHADOW_SIZE_M)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sScraftyLevelUpLearnset,
        .teachableLearnset = sScraftyTeachableLearnset,
    },

    [SPECIES_EELEKTROSS_MEGA] =
    {
        .baseHP        = 85,
        .baseAttack    = 145,
        .baseDefense   = 80,
        .baseSpeed     = 80,
        .baseSpAttack  = 135,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_DRAGON),
        .catchRate = 30,
        .expYield = 258 ,
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_LEVITATE, ABILITY_LEVITATE, ABILITY_LEVITATE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Eelektross"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_EELEKTROSS_MEGA,
    #else
        .cryId = CRY_EELEKTROSS,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_EELEKTROSS,
        .categoryName = _("EleFish"),
        .height = 30,
        .weight = 1800,
        .description = COMPOUND_STRING(
            "It now generates 10 times the\n"
            "electricity it did before Mega\n"
            "Evolving. It discharges this energy\n"
            "from its false Eelektrik made of mucus."),
        .frontPic = gMonFrontPic_EelektrossMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 6,
        .backPic = gMonBackPic_EelektrossMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_EelektrossMega,
        .shinyPalette = gMonShinyPalette_EelektrossMega,
        .iconSprite = gMonIcon_EelektrossMega,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Eelektross)
        SHADOW(-2, 16, SHADOW_SIZE_L)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sEelektrossLevelUpLearnset,
        .teachableLearnset = sEelektrossTeachableLearnset,
    },

    [SPECIES_CHANDELURE_MEGA] =
    {
        .baseHP        = 60,
        .baseAttack    = 75,
        .baseDefense   = 110,
        .baseSpeed     = 90,
        .baseSpAttack  = 175,
        .baseSpDefense = 110,
        .types = MON_TYPES(TYPE_GHOST, TYPE_FIRE),
        .catchRate = 45,
        .expYield = 260,
        .evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_FLASH_FIRE, ABILITY_FLAME_BODY, ABILITY_INFILTRATOR },
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = TRUE,
        .speciesName = _("Chandelure"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_CHANDELURE_MEGA,
    #else
        .cryId = CRY_CHANDELURE,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_CHANDELURE,
        .categoryName = _("Luring"),
        .height = 25,
        .weight = 696,
        .description = COMPOUND_STRING(
            "One of its eyes is a window linking\n"
            "our world with the afterlife.\n"
            "This Pokémon draws in hatred and\n"
            "converts it into power."),
        .frontPic = gMonFrontPic_ChandelureMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 6,
        .backPic = gMonBackPic_ChandelureMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_ChandelureMega,
        .shinyPalette = gMonShinyPalette_ChandelureMega,
        .iconSprite = gMonIcon_ChandelureMega,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Chandelure)
        SHADOW(-1, 16, SHADOW_SIZE_L)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sChandelureLevelUpLearnset,
        .teachableLearnset = sChandelureTeachableLearnset,
    },

    [SPECIES_RAICHU_MEGA_X] =
    {
        .baseHP        = 60,
        .baseAttack    = 135,
        .baseDefense   = 90,
        .baseSpeed     = 115,
        .baseSpAttack  = 95,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_FIGHTING),
        .catchRate = 75,
        .expYield = RAICHU_EXP_YIELD,
        .evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_ELECTRO_BOOSTER, ABILITY_ELECTRO_BOOSTER, ABILITY_ELECTRO_BOOSTER },
        .innateAbility = ABILITY_SHORT_CIRCUIT,
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Raichu"),
        .cryId = CRY_RAICHU,
        .natDexNum = NATIONAL_DEX_RAICHU,
        .categoryName = _("Mouse"),
        .height = 8,
        .weight = 300,
        .description = COMPOUND_STRING(
            "If it stores too much electricity, its\n"
            "behavior turns aggressive. To avoid this,\n"
            "it occasionally discharges excess energy\n"
            "and calms itself down."),
        .pokemonScale = 426,
        .pokemonOffset = 13,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_RaichuMegaX,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_RaichuMegaX,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 1,
        //.backAnimId = BACK_ANIM_SHAKE_FLASH_YELLOW,
        .palette = gMonPalette_RaichuMegaX,
        .shinyPalette = gMonShinyPalette_RaichuMegaX,
        .iconSprite = gMonIcon_RaichuMegaX,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 10, SHADOW_SIZE_L)
        FOOTPRINT(Raichu)
        OVERWORLD(
            sPicTable_Raichu,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Raichu,
            gShinyOverworldPalette_Raichu
        )
        .levelUpLearnset = sRaichuLevelUpLearnset,
        .teachableLearnset = sRaichuTeachableLearnset,
        .formSpeciesIdTable = sRaichuFormSpeciesIdTable,
    },

    [SPECIES_RAICHU_MEGA_Y] =
    {
        .baseHP        = 60,
        .baseAttack    = 135,
        .baseDefense   = 90,
        .baseSpeed     = 115,
        .baseSpAttack  = 95,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_FIGHTING),
        .catchRate = 75,
        .expYield = RAICHU_EXP_YIELD,
        .evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_ELECTRO_BOOSTER, ABILITY_ELECTRO_BOOSTER, ABILITY_ELECTRO_BOOSTER },
        .innateAbility = ABILITY_SHORT_CIRCUIT,
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Raichu"),
        .cryId = CRY_RAICHU,
        .natDexNum = NATIONAL_DEX_RAICHU,
        .categoryName = _("Mouse"),
        .height = 8,
        .weight = 300,
        .description = COMPOUND_STRING(
            "If it stores too much electricity, its\n"
            "behavior turns aggressive. To avoid this,\n"
            "it occasionally discharges excess energy\n"
            "and calms itself down."),
        .pokemonScale = 426,
        .pokemonOffset = 13,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_RaichuMegaY,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_RaichuMegaY,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        //.backAnimId = BACK_ANIM_SHAKE_FLASH_YELLOW,
        .palette = gMonPalette_RaichuMegaY,
        .shinyPalette = gMonShinyPalette_RaichuMegaY,
        .iconSprite = gMonIcon_RaichuMegaY,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 10, SHADOW_SIZE_M)
        FOOTPRINT(Raichu)
        OVERWORLD(
            sPicTable_Raichu,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Raichu,
            gShinyOverworldPalette_Raichu
        )
        .levelUpLearnset = sRaichuLevelUpLearnset,
        .teachableLearnset = sRaichuTeachableLearnset,
        .formSpeciesIdTable = sRaichuFormSpeciesIdTable,
    },


    /*
    [SPECIES_NONE] =
    {
        .baseHP        = 1,
        .baseAttack    = 1,
        .baseDefense   = 1,
        .baseSpeed     = 1,
        .baseSpAttack  = 1,
        .baseSpDefense = 1,
        .types = MON_TYPES(TYPE_MYSTERY),
        .catchRate = 255,
        .expYield = 67,
        .evYield_HP = 1,
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        .frontPicFemale = gMonFrontPic_CircledQuestionMark,
        .frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .backPicFemale = gMonBackPic_CircledQuestionMarkF,
        .backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .paletteFemale = gMonPalette_CircledQuestionMarkF,
        .shinyPaletteFemale = gMonShinyPalette_CircledQuestionMarkF,
        .iconSpriteFemale = gMonIcon_QuestionMarkF,
        .iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        FOOTPRINT(QuestionMark)
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    */
};
