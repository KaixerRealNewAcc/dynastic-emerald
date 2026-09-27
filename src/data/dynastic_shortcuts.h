#ifndef GUARD_DYNASTIC_SHORTCUTS_H
#define GUARD_DYNASTIC_SHORTCUTS_H

#include "difficulty.h"
#include "constants/difficulty.h"
#include "script.h"
#include "event_data.h"
#include "constants/global.h"

static inline u32 IsFollowerEnabled(void)
{
    return FlagClear(FLAG_DISABLED_FOLLOWERS);
}

static inline u32 SetFollowerToDisabled(void)
{
    return FlagSet(FLAG_DISABLED_FOLLOWERS);
}

static inline u32 IsFollowerDisabled(void)
{
    return FlagGet(FLAG_DISABLED_FOLLOWERS);
}

static inline u32 IsNuzlockeModeActive(void)
{
    return (FlagGet(FLAG_NUZLOCKE_MODE) && FlagGet(FLAG_SYS_POKEDEX_GET));
}

#endif //GUARD_DYNASTIC_SHORTCUTS_H