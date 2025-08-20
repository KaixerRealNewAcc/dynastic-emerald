
InsideOfTruck_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, InsideOfTruck_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, InsideOfTruck_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, InsideOfTruck_OnResume
	.byte 0

InsideOfTruck_OnLoad:
	setmetatile 4, 1, METATILE_InsideOfTruck_ExitLight_Top, FALSE
	setmetatile 4, 2, METATILE_InsideOfTruck_ExitLight_Mid, FALSE
	setmetatile 4, 3, METATILE_InsideOfTruck_ExitLight_Bottom, FALSE
	end

InsideOfTruck_OnFrame:
	map_script_2 VAR_REGION_CHECK, 0, InsideOfTruck_EventScript_StartSettingsMenu @MinimalGrindingAsk
	.2byte 0

InsideOfTruck_OnResume:
	setstepcallback STEP_CB_TRUCK
	end

InsideOfTruck_EventScript_SetIntroFlags::
	lockall
	setflag FLAG_HIDE_MAP_NAME_POPUP
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, InsideOfTruck_EventScript_SetIntroFlagsMale
	goto_if_eq VAR_RESULT, FEMALE, InsideOfTruck_EventScript_SetIntroFlagsFemale
	end

InsideOfTruck_EventScript_SetIntroFlagsMale::
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F
	setvar VAR_LITTLEROOT_INTRO_STATE, 1
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_SIBLING
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 1
	setdynamicwarp MAP_LITTLEROOT_TOWN, 3, 10
	releaseall
	end

InsideOfTruck_EventScript_SetIntroFlagsFemale::
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F
	setvar VAR_LITTLEROOT_INTRO_STATE, 2
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_SIBLING
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 1
	setdynamicwarp MAP_LITTLEROOT_TOWN, 12, 10
	releaseall
	end

InsideOfTruck_EventScript_MovingBox::
	msgbox InsideOfTruck_Text_BoxPrintedWithMonLogo, MSGBOX_SIGN
	end

ChooseStarterSet::
	lock
	message KaixerHello
	waitmessage
	dynmultichoice 0,0,FALSE,6,0,DYN_MULTICHOICE_CB_NONE, StarterRegionStringKanto, StarterRegionStringJohto, StarterRegionStringHoenn, StarterRegionStringSinnoh, StarterRegionStringUnova, StarterRegionStringKalos, StarterRegionStringAlola, StarterRegionStringGalar, StarterRegionStringPaldea
	switch VAR_RESULT
	case 0, LittlerootTown_BrendansHouse_1F_EventScript_Kanto
	case 1, LittlerootTown_BrendansHouse_1F_EventScript_Johto
	case 2, LittlerootTown_BrendansHouse_1F_EventScript_Hoenn
	case 3, LittlerootTown_BrendansHouse_1F_EventScript_Sinnoh
	case 4, LittlerootTown_BrendansHouse_1F_EventScript_Unova
	case 5, LittlerootTown_BrendansHouse_1F_EventScript_Kalos
	case 6, LittlerootTown_BrendansHouse_1F_EventScript_Alola
	case 7, LittlerootTown_BrendansHouse_1F_EventScript_Galar
	case 8, LittlerootTown_BrendansHouse_1F_EventScript_Paldea
	end

LittlerootTown_BrendansHouse_1F_EventScript_Kanto:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 1
	bufferstring 1, StarterRegionStringKanto
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_1_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Johto:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 2
	bufferstring 1, StarterRegionStringJohto
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_1_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Hoenn:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 3
	bufferstring 1, StarterRegionStringHoenn
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_1_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Sinnoh:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 4
	bufferstring 1, StarterRegionStringSinnoh
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_1_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Unova:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 5
	bufferstring 1, StarterRegionStringUnova
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_1_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Kalos:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 6
	bufferstring 1, StarterRegionStringKalos
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_1_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Alola:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 7
	bufferstring 1, StarterRegionStringAlola
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_1_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Galar:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 8
	bufferstring 1, StarterRegionStringGalar
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_1_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Paldea:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 9
	bufferstring 1, StarterRegionStringPaldea
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_1_Continue

ChooseStarterSet2::
	lock
	message KaixerHello
	waitmessage
	dynmultichoice 0,0,FALSE,6,0,DYN_MULTICHOICE_CB_NONE, StarterRegionStringKanto, StarterRegionStringJohto, StarterRegionStringHoenn, StarterRegionStringSinnoh, StarterRegionStringUnova, StarterRegionStringKalos, StarterRegionStringAlola, StarterRegionStringGalar, StarterRegionStringPaldea
	switch VAR_RESULT
	case 0, LittlerootTown_BrendansHouse_1F_EventScript_Kanto2
	case 1, LittlerootTown_BrendansHouse_1F_EventScript_Johto2
	case 2, LittlerootTown_BrendansHouse_1F_EventScript_Hoenn2
	case 3, LittlerootTown_BrendansHouse_1F_EventScript_Sinnoh2
	case 4, LittlerootTown_BrendansHouse_1F_EventScript_Unova2
	case 5, LittlerootTown_BrendansHouse_1F_EventScript_Kalos2
	case 6, LittlerootTown_BrendansHouse_1F_EventScript_Alola2
	case 7, LittlerootTown_BrendansHouse_1F_EventScript_Galar2
	case 8, LittlerootTown_BrendansHouse_1F_EventScript_Paldea2
	end

LittlerootTown_BrendansHouse_1F_EventScript_Kanto2:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 1
	bufferstring 1, StarterRegionStringKanto
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_2_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Johto2:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 2
	bufferstring 1, StarterRegionStringJohto
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_2_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Hoenn2:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 3
	bufferstring 1, StarterRegionStringHoenn
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_2_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Sinnoh2:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 4
	bufferstring 1, StarterRegionStringSinnoh
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_2_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Unova2:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 5
	bufferstring 1, StarterRegionStringUnova
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_2_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Kalos2:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 6
	bufferstring 1, StarterRegionStringKalos
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_2_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Alola2:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 7
	bufferstring 1, StarterRegionStringAlola
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_2_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Galar2:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 8
	bufferstring 1, StarterRegionStringGalar
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_2_Continue

LittlerootTown_BrendansHouse_1F_EventScript_Paldea2:
	msgbox RivalsHouse_1F_Text_SureAboutRegion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChooseStarterSet
	setvar VAR_REGION_CHOICE, 9
	bufferstring 1, StarterRegionStringPaldea
	setvar VAR_REGION_CHECK, 1
	goto InsideOfTruck_EventScript_SaveSettingsDone_2_Continue

StarterRegionStringKanto:
	.string "Kanto$"

StarterRegionStringJohto:
	.string "Johto$"

StarterRegionStringHoenn:
	.string "Hoenn$"

StarterRegionStringSinnoh:
	.string "Sinnoh$"

StarterRegionStringUnova:
	.string "Unova$"

StarterRegionStringKalos:
	.string "Kalos$"

StarterRegionStringAlola:
	.string "Alola$"

StarterRegionStringGalar:
	.string "Galar$"

StarterRegionStringPaldea:
	.string "Paldea$"

InsideOfTruck_Text_BoxPrintedWithMonLogo:
	.string "The box is printed with a Pokémon logo.\p"
	.string "It's a Pokémon brand moving and\n"
	.string "delivery service.$"

InsideOfTruck_EventScript_FadeToBlack::
	fadescreen FADE_TO_BLACK
	release
	end


InsideOfTruck_EventScript_StartSettingsMenu::
	lock
	special ForceBattleStyleSet
	fadescreen FADE_TO_BLACK
	msgbox InsideOfTruck_EventScript_StartSettingsMenu_Text_0, MSGBOX_DEFAULT
	msgbox InsideOfTruck_EventScript_StartSettingsMenu_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq InsideOfTruck_EventScript_StartSettingsMenu_1
	goto InsideOfTruck_EventScript_StartSettingsMenuCon
	return

InsideOfTruck_EventScript_StartSettingsMenu_1:
	setflag FLAG_NUZLOCKE_MODE
	msgbox InsideOfTruck_EventScript_StartSettingsMenu_Text_2
	goto InsideOfTruck_EventScript_StartSettingsMenuCon
	return


InsideOfTruck_EventScript_StartSettingsMenuCon::
	msgbox InsideOfTruck_EventScript_StartSettingsMenuCon_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq InsideOfTruck_EventScript_StartSettingsMenuCon_1
	goto InsideOfTruck_EventScript_SaveSettingsDone_1
	return

InsideOfTruck_EventScript_StartSettingsMenuCon_1:
	goto InsideOfTruck_EventScript_StartSettingsMenu_Continue
	return


InsideOfTruck_EventScript_StartSettingsMenu_Continue::
	message InsideOfTruck_EventScript_StartSettingsMenu_Continue_Text_0
	waitmessage
	dynmultipush InsideOfTruck_EventScript_StartSettingsMenu_Continue_Text_1, 1
	dynmultipush InsideOfTruck_EventScript_StartSettingsMenu_Continue_Text_2, 2
	dynmultipush InsideOfTruck_EventScript_StartSettingsMenu_Continue_Text_3, 127
	dynmultistack 0, 0, TRUE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	compare VAR_RESULT, 1
	goto_if_eq InsideOfTruck_EventScript_StartSettingsMenu_Continue_2
InsideOfTruck_EventScript_StartSettingsMenu_Continue_1:
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_StartSettingsMenu_Continue_5
InsideOfTruck_EventScript_StartSettingsMenu_Continue_4:
	compare VAR_RESULT, 127
	goto_if_eq InsideOfTruck_EventScript_StartSettingsMenu_Continue_7
	return

InsideOfTruck_EventScript_StartSettingsMenu_Continue_2:
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions
	goto InsideOfTruck_EventScript_StartSettingsMenu_Continue_1

InsideOfTruck_EventScript_StartSettingsMenu_Continue_5:
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous
	goto InsideOfTruck_EventScript_StartSettingsMenu_Continue_4

InsideOfTruck_EventScript_StartSettingsMenu_Continue_7:
	goto InsideOfTruck_EventScript_SaveSettingsDone_2
	return


InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions::
	message InsideOfTruck_EventScript_StartSettingsMenu_Continue_Text_0
	waitmessage
	dynmultipush InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_0, 0
	goto_if_set FLAG_MINIMAL_GRINDING_MODE, InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_2
	dynmultipush InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_2, 1
InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_1:
	goto_if_set FLAG_VGC_MODE, InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_6
	dynmultipush InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_4, 3
InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_5:
	dynmultipush InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_5, 127
	dynmultistack 0, 0, TRUE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_10
InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_9:
	compare VAR_RESULT, 1
	goto_if_eq InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_13
InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_12:
	compare VAR_RESULT, 3
	goto_if_eq InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_16
InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_15:
	compare VAR_RESULT, 127
	goto_if_eq InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_21
	return

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_2:
	dynmultipush InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_1, 1
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_1

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_6:
	dynmultipush InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_3, 3
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_5

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_10:
	msgbox InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_6
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_9

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_13:
	goto_if_set FLAG_MINIMAL_GRINDING_MODE, InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_18
	msgbox ModesCheck_Text_MinimalGrinding, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_26
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_12

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_16:
	goto_if_set FLAG_VGC_MODE, InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_23
	msgbox ModesCheck_Text_DoublesOnly, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_29
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_15

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_18:
	clearflag FLAG_MINIMAL_GRINDING_MODE
	msgbox InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_7
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_12

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_21:
	goto InsideOfTruck_EventScript_StartSettingsMenu_Continue
	return

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_23:
	clearflag FLAG_VGC_MODE
	msgbox InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_9
	goto InsideOfTruck_EventScript_StartSettingsMenu_Continue
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_15

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_26:
	setflag FLAG_MINIMAL_GRINDING_MODE
	msgbox InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_8
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_12

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_29:
	setflag FLAG_VGC_MODE
	msgbox InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_10
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions
	goto InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_15


InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous::
	message InsideOfTruck_EventScript_StartSettingsMenu_Continue_Text_0
	waitmessage
	goto_if_set EZLEVELING_CODE, InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_2
	dynmultipush InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_1, 0
InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_1:
	goto_if_set EZCATCH_CODE, InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_6
	dynmultipush InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_3, 1
InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_5:
	goto_if_set DEXALL_CODE, InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_10
	dynmultipush InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_5, 2
InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_9:
	dynmultipush InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_5, 127
	dynmultistack 0, 0, TRUE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_14
InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_13:
	compare VAR_RESULT, 1
	goto_if_eq InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_17
InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_16:
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_23
InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_22:
	compare VAR_RESULT, 127
	goto_if_eq InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_28
	return

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_2:
	dynmultipush InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_0, 0
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_1

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_6:
	dynmultipush InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_2, 1
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_5

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_10:
	dynmultipush InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_4, 2
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_9

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_14:
	goto_if_set EZLEVELING_CODE, InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_19
	setflag EZLEVELING_CODE
	msgbox InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_7, MSGBOX_DEFAULT
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_13

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_17:
	goto_if_set EZCATCH_CODE, InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_25
	setflag EZCATCH_CODE
	msgbox InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_9, MSGBOX_DEFAULT
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_16

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_19:
	clearflag EZLEVELING_CODE
	msgbox InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_6, MSGBOX_DEFAULT
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_13

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_23:
	goto_if_set DEXALL_CODE, InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_30
	setflag DEXALL_CODE
	msgbox InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_11, MSGBOX_DEFAULT
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_22

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_25:
	clearflag EZCATCH_CODE
	msgbox InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_8, MSGBOX_DEFAULT
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_16

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_28:
	goto InsideOfTruck_EventScript_StartSettingsMenu_Continue
	return

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_30:
	clearflag DEXALL_CODE
	msgbox InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_10, MSGBOX_DEFAULT
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous
	goto InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_22


InsideOfTruck_EventScript_SaveSettingsDone_1::
	goto ChooseStarterSet
	return


InsideOfTruck_EventScript_SaveSettingsDone_2::
	goto ChooseStarterSet2
	return


InsideOfTruck_EventScript_SaveSettingsDone_1_Continue::
	msgbox InsideOfTruck_EventScript_SaveSettingsDone_1_Continue_Text_0
	fadescreen FADE_FROM_BLACK
	releaseall
	end


InsideOfTruck_EventScript_SaveSettingsDone_2_Continue::
	msgbox InsideOfTruck_EventScript_SaveSettingsDone_2_Continue_Text_0
	fadescreen FADE_FROM_BLACK
	releaseall
	end


InsideOfTruck_EventScript_StartSettingsMenu_Text_0:
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Kaixer{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}: Please stop smashing {A_BUTTON} and\n"
	.string "properly answer the following\l"
	.string "questions.$"

InsideOfTruck_EventScript_StartSettingsMenu_Text_1:
	.string "Would you like to play with the\n"
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Nuzlock Challenge enabled{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}?$"

InsideOfTruck_EventScript_StartSettingsMenu_Text_2:
	.string "Nuzlocke Mode is {COLOR GREEN}{SHADOW LIGHT_GREEN}Enabled.$"

InsideOfTruck_EventScript_StartSettingsMenuCon_Text_0:
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Kaixer{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}: and would you like to play\n"
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Dynastic Emerald {COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}with custom options\l"
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}enabled{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}?$"

InsideOfTruck_EventScript_StartSettingsMenu_Continue_Text_0:
	.string "Press {A_BUTTON} to select an Option.$"

InsideOfTruck_EventScript_StartSettingsMenu_Continue_Text_1:
	.string "Difficulty Options$"

InsideOfTruck_EventScript_StartSettingsMenu_Continue_Text_2:
	.string "Miscellaneous$"

InsideOfTruck_EventScript_StartSettingsMenu_Continue_Text_3:
	.string "Done$"

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_0:
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Normal Mode$"

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_1:
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Minimal Grinding Mode$"

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_2:
	.string "{COLOR RED}{SHADOW LIGHT_RED}Minimal Grinding Mode$"

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_3:
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Doubles Mode$"

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_4:
	.string "{COLOR RED}{SHADOW LIGHT_RED}Doubles Mode$"

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_5:
	.string "Return$"

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_6:
	.string "Normal Mode is {COLOR GREEN}{SHADOW LIGHT_GREEN}Enabled{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} by default.$"

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_7:
	.string "Minimal Grinding Mode is {COLOR RED}{SHADOW LIGHT_RED}Disabled.$"

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_8:
	.string "Minimal Grinding Mode is {COLOR GREEN}{SHADOW LIGHT_GREEN}Enabled.$"

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_9:
	.string "Doubles Mode is {COLOR RED}{SHADOW LIGHT_RED}Disabled.$"

InsideOfTruck_EventScript_SaveSettingsMenu_DifficultyOptions_Text_10:
	.string "Doubles Mode is {COLOR GREEN}{SHADOW LIGHT_GREEN}Enabled.$"

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_0:
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}EZLeveling$"

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_1:
	.string "{COLOR RED}{SHADOW LIGHT_RED}EZLeveling$"

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_2:
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}EZCatch$"

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_3:
	.string "{COLOR RED}{SHADOW LIGHT_RED}EZCatch$"

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_4:
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}DexAll$"

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_5:
	.string "{COLOR RED}{SHADOW LIGHT_RED}DexAll$"

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_6:
	.string "EZLeveling is {COLOR RED}{SHADOW LIGHT_RED}disabled.$"

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_7:
	.string "EZLeveling is {COLOR GREEN}{SHADOW LIGHT_GREEN}enabled.$"

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_8:
	.string "EZCatch is {COLOR RED}{SHADOW LIGHT_RED}disabled.$"

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_9:
	.string "EZCatch is {COLOR GREEN}{SHADOW LIGHT_GREEN}enabled.$"

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_10:
	.string "DexAll is {COLOR RED}{SHADOW LIGHT_RED}disabled.$"

InsideOfTruck_EventScript_SaveSettingsMenu_Miscellaneous_Text_11:
	.string "DexAll is {COLOR GREEN}{SHADOW LIGHT_GREEN}enabled.$"

InsideOfTruck_EventScript_SaveSettingsDone_1_Continue_Text_0:
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Kaixer:{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} Very well then.\n"
	.string "good luck and have fun!$"

InsideOfTruck_EventScript_SaveSettingsDone_2_Continue_Text_0:
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Kaixer:{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} Custom settings saved.\n"
	.string "Very well then. good luck and have fun!$"

RivalsHouse_1F_Text_SureAboutRegion::
	.string "Are you sure about the region?$"

RivalsHouse_1F_Text_Which_Region::
	.string "Oh, darn. Which region was it again?$"

ModesCheck_Text_MinimalGrinding::
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Minimal Grinding Mode{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} makes EVs\n"
	.string "unobtainable.\p"
	.string "This is mostly for people who dislike\n"
	.string "training for EVs.\p"
	.string "Do you want to turn on {COLOR GREEN}{SHADOW LIGHT_GREEN}Minimal Grinding\n"
	.string "Mode?$"

ModesCheck_Text_DoublesOnly::
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Doubles Only Mode{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} turns trainer battles\n"
	.string "into forced double battles.\p"
	.string "This is mainly for people who like a\n"
	.string "challenge or for people who are more\p"
	.string "into VGC than Singles.\p"
	.string "Do you want to turn on {COLOR GREEN}{SHADOW LIGHT_GREEN}Doubles Only\n"
	.string "Mode?$"

ModesCheck_Text_NuzlockeChallenge::
	.string "The {COLOR GREEN}{SHADOW LIGHT_GREEN}Nuzlocke Challenge{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} makes it so i\n"
	.string "\p"
	.string "This is mainly for people who like a\n"
	.string "challenge or for people who are more\p"
	.string "into VGC than Singles.\p"
	.string "Do you want to turn on {COLOR GREEN}{SHADOW LIGHT_GREEN}Doubles Only\n"
	.string "Mode?$"

ModesCheck_Text_NoWeatherMode::
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}No Weather Mode{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} Makes it so no pokemon\n"
	.string "can learn weather moves and weather\l"
	.string "abilities are changed into other\l"
	.string "abilities.\p"
	.string "some weather moves, like Chilly\n"
	.string "Reception are usable but work as a\l"
	.string "different move. Would you like to turn\l"
	.string "on {COLOR GREEN}{SHADOW LIGHT_GREEN}No Weather Mode?$"

KaixerHello::
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Kaixer:{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} So {COLOR GREEN}{SHADOW LIGHT_GREEN}{PLAYER}{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY} Which region\n"
	.string "would you like to use?$"
