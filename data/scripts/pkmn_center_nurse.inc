
Common_EventScript_PkmnCenterNurse::
	lock
	faceplayer
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, CountPlayerTrainerStars
	goto_if_eq VAR_RESULT, 4, EventScript_PkmnCenterNurse_GoldCard
	msgbox gText_WouldYouLikeToRestYourPkmn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, EventScript_PkmnCenterNurse_HealPkmn
	goto_if_eq VAR_RESULT, NO, EventScript_PkmnCenterNurse_Goodbye
	end

EventScript_PkmnCenterNurse_Goodbye::
	message gText_WeHopeToSeeYouAgain
	return

@ VAR_0x8004 is 1 when player has Gold Card; jumps are identical
EventScript_PkmnCenterNurse_HealPkmn::
	incrementgamestat GAME_STAT_USED_POKECENTER
	call_if_eq VAR_0x8004, 0, EventScript_PkmnCenterNurse_IllTakeYourPkmn
	call_if_eq VAR_0x8004, 1, EventScript_PkmnCenterNurse_IllTakeYourPkmn2
	waitmessage
	call EventScript_PkmnCenterNurse_TakeAndHealPkmn
	goto_if_unset FLAG_POKERUS_EXPLAINED, EventScript_PkmnCenterNurse_CheckPokerus
	goto EventScript_PkmnCenterNurse_CheckTrainerHillAndUnionRoom
	end

EventScript_PkmnCenterNurse_IllTakeYourPkmn::
	message gText_IllTakeYourPkmn
	return

EventScript_PkmnCenterNurse_IllTakeYourPkmn2::
	message gText_IllTakeYourPkmn2
	return

EventScript_PkmnCenterNurse_TakeAndHealPkmn::
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Turn @ Changed from Common_Movement_WalkInPlaceFasterLeft to force the follower to enter their Poké Ball
	waitmovement 0
	dofieldeffect FLDEFF_POKECENTER_HEAL
.if OW_UNION_DISABLE_CHECK == FALSE && OW_FLAG_MOVE_UNION_ROOM_CHECK != 0
	setflag OW_FLAG_MOVE_UNION_ROOM_CHECK
	call CableClub_OnResume
	clearflag OW_FLAG_MOVE_UNION_ROOM_CHECK
.endif
	waitfieldeffect FLDEFF_POKECENTER_HEAL
	applymovement VAR_0x800B, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	return

EventScript_PkmnCenterNurse_CheckTrainerHillAndUnionRoom::
	specialvar VAR_RESULT, PlayerNotAtTrainerHillEntrance
	goto_if_eq VAR_RESULT, 0, EventScript_PkmnCenterNurse_ReturnPkmn
	specialvar VAR_RESULT, BufferUnionRoomPlayerName
	copyvar VAR_0x8008, VAR_RESULT
	goto_if_eq VAR_0x8008, 0, EventScript_PkmnCenterNurse_ReturnPkmn
	goto_if_eq VAR_0x8008, 1, EventScript_PkmnCenterNurse_PlayerWaitingInUnionRoom
	end

@ VAR_0x8004 is 1 when player has Gold Card
EventScript_PkmnCenterNurse_ReturnPkmn::
	goto_if_eq VAR_0x8004, 1, EventScript_PkmnCenterNurse_ReturnPkmn2
	message gText_RestoredPkmnToFullHealth
	waitmessage
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message gText_WeHopeToSeeYouAgain
	return

EventScript_PkmnCenterNurse_ReturnPkmn2::
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Bow
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	return


EventScript_PkmnCenterNurse_PlayerWaitingInUnionRoom::
	goto_if_set FLAG_NURSE_UNION_ROOM_REMINDER, EventScript_PkmnCenterNurse_ReturnPkmn
	msgbox gText_RestoredPkmnToFullHealth, MSGBOX_DEFAULT
	setflag FLAG_NURSE_UNION_ROOM_REMINDER
	message CableClub_Text_PlayerIsWaiting
	waitmessage
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message gText_WeHopeToSeeYouAgain
	return

EventScript_PkmnCenterNurse_CheckPokerus::
	specialvar VAR_RESULT, IsPokerusInParty
	goto_if_eq VAR_RESULT, TRUE, EventScript_PkmnCenterNurse_ExplainPokerus
	goto_if_eq VAR_RESULT, FALSE, EventScript_PkmnCenterNurse_CheckTrainerHillAndUnionRoom
	end

EventScript_PkmnCenterNurse_ExplainPokerus::
	message gText_PokerusExplanation
	setflag FLAG_POKERUS_EXPLAINED
	return

EventScript_PkmnCenterNurse_GoldCard::
	goto_if_set FLAG_NURSE_MENTIONS_GOLD_CARD, EventScript_PkmnCenterNurse_AskForUsual
	setflag FLAG_NURSE_MENTIONS_GOLD_CARD
	msgbox gText_WelcomeCutShort, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement VAR_0x800B, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x800B, Common_Movement_Delay48
	waitmovement 0
	msgbox gText_NoticesGoldCard, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, EventScript_PkmnCenterNurse_GoldCardHealPkmn
	message gText_WeHopeToSeeYouAgain2
	return

EventScript_PkmnCenterNurse_AskForUsual::
	msgbox gText_YouWantTheUsual, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, EventScript_PkmnCenterNurse_GoldCardHealPkmn
	message gText_WeHopeToSeeYouAgain2
	return

EventScript_PkmnCenterNurse_GoldCardHealPkmn::
	setvar VAR_0x8004, 1
	goto EventScript_PkmnCenterNurse_HealPkmn
	end

Movement_PkmnCenterNurse_Bow:
	nurse_joy_bow
	delay_4
	step_end

Movement_PkmnCenterNurse_Turn:
	walk_in_place_faster_left
	step_end

EventScript_PkmnCenterPokeHelper::
	lock
	faceplayer
	message EventScript_PkmnCenterPokeHelper_Text_0
	waitmessage
	dynmultipush EventScript_PkmnCenterPokeHelper_Text_1, 0
	dynmultipush EventScript_PkmnCenterPokeHelper_Text_2, 1
	dynmultipush EventScript_PkmnCenterPokeHelper_Text_3, 2
	dynmultipush EventScript_PkmnCenterPokeHelper_Text_4, 3
	dynmultipush EventScript_PkmnCenterPokeHelper_Text_5, MULTI_B_PRESSED
	dynmultistack 0, 0, TRUE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, EventScript_PkmnCenterPokeHelper_3
	case 1, EventScript_PkmnCenterPokeHelper_4
	case 2, EventScript_PkmnCenterPokeHelper_5
	case 3, EventScript_PkmnCenterPokeHelper_6
	case MULTI_B_PRESSED, EventScript_PkmnCenterPokeHelper_7
EventScript_PkmnCenterPokeHelper_1:
	release
	end

EventScript_PkmnCenterPokeHelper_3:
	goto NatureChanger
	goto EventScript_PkmnCenterPokeHelper_1

EventScript_PkmnCenterPokeHelper_4:
	goto GenderChanger
	goto EventScript_PkmnCenterPokeHelper_1

EventScript_PkmnCenterPokeHelper_5:
	goto ModeInfo
	goto EventScript_PkmnCenterPokeHelper_1

EventScript_PkmnCenterPokeHelper_6:
	goto VersionInfo
	goto EventScript_PkmnCenterPokeHelper_1

EventScript_PkmnCenterPokeHelper_7:
	msgbox EventScript_PkmnCenterPokeHelper_Text_6
	release
	end


NatureChanger::
	message NatureChanger_Text_0
	waitmessage
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, PARTY_NOTHING_CHOSEN
	goto_if_eq NatureChanger_2
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq NatureChanger_5
NatureChanger_4:
	special BufferMonNickname
	message NatureChanger_Text_2
	waitmessage
	dynmultipush NatureChanger_Text_3, NATURE_ADAMANT
	dynmultipush NatureChanger_Text_4, NATURE_BASHFUL
	dynmultipush NatureChanger_Text_5, NATURE_BOLD
	dynmultipush NatureChanger_Text_6, NATURE_BRAVE
	dynmultipush NatureChanger_Text_7, NATURE_CALM
	dynmultipush NatureChanger_Text_8, NATURE_CAREFUL
	dynmultipush NatureChanger_Text_9, NATURE_DOCILE
	dynmultipush NatureChanger_Text_10, NATURE_GENTLE
	dynmultipush NatureChanger_Text_11, NATURE_HARDY
	dynmultipush NatureChanger_Text_12, NATURE_HASTY
	dynmultipush NatureChanger_Text_13, NATURE_IMPISH
	dynmultipush NatureChanger_Text_14, NATURE_JOLLY
	dynmultipush NatureChanger_Text_15, NATURE_LAX
	dynmultipush NatureChanger_Text_16, NATURE_LONELY
	dynmultipush NatureChanger_Text_17, NATURE_MILD
	dynmultipush NatureChanger_Text_18, NATURE_MODEST
	dynmultipush NatureChanger_Text_19, NATURE_NAIVE
	dynmultipush NatureChanger_Text_20, NATURE_NAUGHTY
	dynmultipush NatureChanger_Text_21, NATURE_QUIET
	dynmultipush NatureChanger_Text_22, NATURE_QUIRKY
	dynmultipush NatureChanger_Text_23, NATURE_RASH
	dynmultipush NatureChanger_Text_24, NATURE_RELAXED
	dynmultipush NatureChanger_Text_25, NATURE_SASSY
	dynmultipush NatureChanger_Text_26, NATURE_SERIOUS
	dynmultipush NatureChanger_Text_27, NATURE_TIMID
	dynmultipush EventScript_PkmnCenterPokeHelper_Text_5, MULTI_B_PRESSED
	dynmultistack 0, 0, FALSE, 6, FALSE, 3, DYN_MULTICHOICE_CB_NONE
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq NatureChanger_8
	copyvar VAR_0x8005, VAR_RESULT
	special BufferMonNickname
	msgbox NatureChanger_Text_28, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq NatureChanger_11
	msgbox NatureChanger_Text_29
	fadescreen FADE_TO_BLACK
	special ChangeMonNature
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	closemessage
	fadescreen FADE_FROM_BLACK
	msgbox NatureChanger_Text_30
	release
	end

NatureChanger_2:
	msgbox EventScript_PkmnCenterPokeHelper_Text_6
	release
	end

NatureChanger_5:
	message NatureChanger_Text_1
	waitmessage
	waitbuttonpress
	goto NatureChanger_4

NatureChanger_8:
	msgbox EventScript_PkmnCenterPokeHelper_Text_6
	release
	end

NatureChanger_11:
	msgbox EventScript_PkmnCenterPokeHelper_Text_6
	release
	end


GenderChanger::
	msgbox GenderChanger_Text_0
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, PARTY_NOTHING_CHOSEN
	goto_if_eq GenderChanger_2
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	switch VAR_RESULT
	case SPECIES_SNORUNT, GenderChanger_6
	case SPECIES_RALTS, GenderChanger_6
	case SPECIES_KIRLIA, GenderChanger_6
	case SPECIES_SALANDIT, GenderChanger_6
	case SPECIES_BURMY_PLANT, GenderChanger_6
	case SPECIES_BURMY_SANDY, GenderChanger_6
	case SPECIES_BURMY_TRASH, GenderChanger_6
	case SPECIES_COMBEE, GenderChanger_6
	case SPECIES_ESPURR, GenderChanger_6
	case SPECIES_BASCULIN_RED_STRIPED, GenderChanger_6
	case SPECIES_BASCULIN_BLUE_STRIPED, GenderChanger_6
	case SPECIES_BASCULIN_WHITE_STRIPED, GenderChanger_6
	case SPECIES_LECHONK, GenderChanger_6
	case SPECIES_EGG, GenderChanger_7
	msgbox GenderChanger_Text_4
GenderChanger_4:
	release
	end

GenderChanger_2:
	msgbox EventScript_PkmnCenterPokeHelper_Text_6
	release
	end

GenderChanger_6:
	special BufferMonNickname
	msgbox GenderChanger_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq GenderChanger_10
	msgbox NatureChanger_Text_29
	fadescreen FADE_TO_BLACK
	special ChangeMonGender
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	closemessage
	fadescreen FADE_FROM_BLACK
	msgbox GenderChanger_Text_2
	goto GenderChanger_4

GenderChanger_7:
	msgbox GenderChanger_Text_3
	goto GenderChanger_4

GenderChanger_10:
	msgbox EventScript_PkmnCenterPokeHelper_Text_6
	release
	end


ModeInfo::
	msgbox ModeInfo_Text_0
	release
	end


VersionInfo::
	msgbox VersionInfo_Text_0
	release
	end


PkmnCenterChansey::
	lock
	faceplayer
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
	message PkmnCenterChansey_Text_0
	waitmoncry
	waitbuttonpress
	dynmultichoice 0, 0, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, PkmnCenterChansey_Text_1, PkmnCenterChansey_Text_2, EventScript_PkmnCenterPokeHelper_Text_5
	switch VAR_RESULT
	case 0, PkmnCenterChansey_2
	case 1, PkmnCenterChansey_3
	case 2, PkmnCenterChansey_4
	return

PkmnCenterChansey_2:
	closemessage
	message PkmnCenterChansey_Text_3
	playfanfare MUS_HEAL
	waitfanfare
	waitbuttonpress
	closemessage
	callnative UpdateFollowingPokemon
	release
	end

PkmnCenterChansey_3:
	closemessage
	message PkmnCenterChansey_Text_4
	playfanfare MUS_HEAL
	waitfanfare
	waitbuttonpress
	closemessage
	callnative UpdateFollowingPokemon
	release
	end

PkmnCenterChansey_4:
	release
	end


EventScript_PkmnCenterPokeHelper_Text_0:
	.string "Welcome!\nWhat service are you looking for?$"

EventScript_PkmnCenterPokeHelper_Text_1:
	.string "Change Nature$"

EventScript_PkmnCenterPokeHelper_Text_2:
	.string "Change Gender$"

EventScript_PkmnCenterPokeHelper_Text_3:
	.string "Mode Info$"

EventScript_PkmnCenterPokeHelper_Text_4:
	.string "Current Release Info$"

EventScript_PkmnCenterPokeHelper_Text_5:
	.string "Cancel$"

EventScript_PkmnCenterPokeHelper_Text_6:
	.string "I see. Come back if you need\nsomething else.$"

NatureChanger_Text_0:
	.string "Which Pokemon would you like to change\n"
	.string "its nature?$"

NatureChanger_Text_1:
	.string "Thats.. an egg.\n"
	.string "Eggs can't be nature swapped.$"

NatureChanger_Text_2:
	.string "Which new Nature suits {STR_VAR_1}\n"
	.string "best?$"

NatureChanger_Text_3:
	.string "Adamant: {COLOR RED}{SHADOW LIGHT_RED}+Atk{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-SpAtk$"

NatureChanger_Text_4:
	.string "Bashful: Neutral$"

NatureChanger_Text_5:
	.string "Bold:    {COLOR RED}{SHADOW LIGHT_RED}+Def{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-Atk       $"

NatureChanger_Text_6:
	.string "Brave:   {COLOR RED}{SHADOW LIGHT_RED}+Atk{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-Speed     $"

NatureChanger_Text_7:
	.string "Calm:    {COLOR RED}{SHADOW LIGHT_RED}+SpDef{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-Atk     $"

NatureChanger_Text_8:
	.string "Careful: {COLOR RED}{SHADOW LIGHT_RED}+SpDef{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-SpAtk   $"

NatureChanger_Text_9:
	.string "Docile:  Neutral$"

NatureChanger_Text_10:
	.string "Gentle:  {COLOR RED}{SHADOW LIGHT_RED}+SpDef{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-Def     $"

NatureChanger_Text_11:
	.string "Hardy:   Neutral$"

NatureChanger_Text_12:
	.string "Hasty:   {COLOR RED}{SHADOW LIGHT_RED}+Speed{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-Def     $"

NatureChanger_Text_13:
	.string "Impish:  {COLOR RED}{SHADOW LIGHT_RED}+Def{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-SpAtk   $"

NatureChanger_Text_14:
	.string "Jolly:   {COLOR RED}{SHADOW LIGHT_RED}+Speed{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-SpAtk   $"

NatureChanger_Text_15:
	.string "Lax:     {COLOR RED}{SHADOW LIGHT_RED}+Def{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-SpDef   $"

NatureChanger_Text_16:
	.string "Lonely:  {COLOR RED}{SHADOW LIGHT_RED}+Atk{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-Def     $"

NatureChanger_Text_17:
	.string "Mild:    {COLOR RED}{SHADOW LIGHT_RED}+SpAtk{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-Def   $"

NatureChanger_Text_18:
	.string "Modest:  {COLOR RED}{SHADOW LIGHT_RED}+SpAtk{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-Atk   $"

NatureChanger_Text_19:
	.string "Naive:   {COLOR RED}{SHADOW LIGHT_RED}+Speed{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-SpDef $"

NatureChanger_Text_20:
	.string "Naughty: {COLOR RED}{SHADOW LIGHT_RED}+Atk{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-SpDef   $"

NatureChanger_Text_21:
	.string "Quiet:   {COLOR RED}{SHADOW LIGHT_RED}+SpAtk{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-Speed $"

NatureChanger_Text_22:
	.string "Quirky:  Neutral$"

NatureChanger_Text_23:
	.string "Rash:    {COLOR RED}{SHADOW LIGHT_RED}+SpAtk{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-SpDef $"

NatureChanger_Text_24:
	.string "Relaxed: {COLOR RED}{SHADOW LIGHT_RED}+Def{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-Speed   $"

NatureChanger_Text_25:
	.string "Sassy:   {COLOR RED}{SHADOW LIGHT_RED}+SpDef{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-Speed $"

NatureChanger_Text_26:
	.string "Serious: Neutral$"

NatureChanger_Text_27:
	.string "Timid:   {COLOR RED}{SHADOW LIGHT_RED}+Speed{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}/{COLOR BLUE}{SHADOW LIGHT_BLUE}-Atk   $"

NatureChanger_Text_28:
	.string "I will now change\n"
	.string "{STR_VAR_1}'s Nature.\p"
	.string "Is that okay?$"

NatureChanger_Text_29:
	.string "Excellent. We shall begin at once!$"

NatureChanger_Text_30:
	.string "{STR_VAR_1}'s Nature has been\nchanged.\pCome again if you need\nsomething else.$"

GenderChanger_Text_0:
	.string "I can swap the Gender of the\n"
	.string "following Pokémon:\p"
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Snorunt, Ralts, Kirlia, Salandit, Burmy,\n"
	.string "Combee, Espurr, Basculin, and Lechonk.\p"
	.string "{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}This is because these Pokémon have\n"
	.string "Gender-based evolutions.\p"
	.string "Which Pokémon's Gender should I swap?$"

GenderChanger_Text_1:
	.string "I will now swap\n"
	.string "{STR_VAR_1}'s Gender.\p"
	.string "Is that okay?$"

GenderChanger_Text_2:
	.string "{STR_VAR_1}'s Gender has been\nswapped. Come again if you need\lsomething else.$"

GenderChanger_Text_3:
	.string "I can't swap the Gender of an Egg.$"

GenderChanger_Text_4:
	.string "Sorry, I can't swap the Gender of\nthat Pokémon.$"

ModeInfo_Text_0:
	.string "To be worked on.$"

VersionInfo_Text_0:
	.string "Current version: {COLOR GREEN}{SHADOW LIGHT_GREEN}Beta v1.1.\n"
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Beta v1.1 {COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}goes up to {COLOR GREEN}{SHADOW LIGHT_GREEN}Elite Four.$"

PkmnCenterChansey_Text_0:
	.string "Chansey: Chansey!$"

PkmnCenterChansey_Text_1:
	.string "Healing$"

PkmnCenterChansey_Text_2:
	.string "Status Removal$"

PkmnCenterChansey_Text_3:
	.string "Chansey used Soft Boiled!$"

PkmnCenterChansey_Text_4:
	.string "Chansey used Heal Bell!$"
