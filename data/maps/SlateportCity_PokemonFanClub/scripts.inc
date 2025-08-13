
SlateportCity_PokemonFanClub_MapScripts::
	.byte 0

SlateportCity_PokemonFanClub_EventScript_Chairman::
	lock
	faceplayer
	goto_if_unset FLAG_ENTERED_CONTEST, SlateportCity_PokemonFanClub_EventScript_ChairmanNotEnteredContest
	call_if_unset FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN, SlateportCity_PokemonFanClub_EventScript_MeetChairman
	switch VAR_SLATEPORT_FAN_CLUB_STATE
	case 0, SlateportCity_PokemonFanClub_EventScript_ChairmanFirstAssessment
	case 1, SlateportCity_PokemonFanClub_EventScript_ChairmanTryAssessPokemon
	case 2, SlateportCity_PokemonFanClub_EventScript_NoMoreScarves
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanFirstAssessment::
	setvar VAR_SLATEPORT_FAN_CLUB_STATE, 1
	msgbox SlateportCity_PokemonFanClub_Text_AllowMeToExamineYourPokemon, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanTryAssessPokemon::
	setvar VAR_TEMP_2, 0
	call_if_set FLAG_RECEIVED_YELLOW_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_GREEN_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_PINK_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_BLUE_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_RED_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_eq VAR_TEMP_2, CONTEST_CATEGORIES_COUNT, SlateportCity_PokemonFanClub_EventScript_ReceivedAllScarves
	goto_if_eq VAR_SLATEPORT_FAN_CLUB_STATE, 2, SlateportCity_PokemonFanClub_EventScript_NoMoreScarves
	msgbox SlateportCity_PokemonFanClub_Text_HowIsYourPokemonGrowing, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon
	end

SlateportCity_PokemonFanClub_EventScript_NoMoreScarves::
	msgbox SlateportCity_PokemonFanClub_Text_NothingElseToGiveYou, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon::
	msgbox SlateportCity_PokemonFanClub_Text_HmHmISee, MSGBOX_DEFAULT
	setvar VAR_TEMP_1, 0
	call_if_unset FLAG_RECEIVED_YELLOW_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonTough
	call_if_unset FLAG_RECEIVED_GREEN_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonSmart
	call_if_unset FLAG_RECEIVED_PINK_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonCute
	call_if_unset FLAG_RECEIVED_BLUE_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonBeauty
	call_if_unset FLAG_RECEIVED_RED_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonCool
	bufferleadmonspeciesname STR_VAR_1
	switch VAR_TEMP_1
	case 0, SlateportCity_PokemonFanClub_EventScript_NoHighConditions
	case 1, SlateportCity_PokemonFanClub_EventScript_GiveRedScarf
	case 2, SlateportCity_PokemonFanClub_EventScript_GiveBlueScarf
	case 3, SlateportCity_PokemonFanClub_EventScript_GivePinkScarf
	case 4, SlateportCity_PokemonFanClub_EventScript_GiveGreenScarf
	case 5, SlateportCity_PokemonFanClub_EventScript_GiveYellowScarf
	release
	end

SlateportCity_PokemonFanClub_EventScript_ReceivedAllScarves::
	setvar VAR_SLATEPORT_FAN_CLUB_STATE, 2
	return

SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf::
	addvar VAR_TEMP_2, 1
	return

SlateportCity_PokemonFanClub_EventScript_NoHighConditions::
	msgbox SlateportCity_PokemonFanClub_Text_GiveMonMorePokeblocks, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveRedScarf::
	checkitemspace ITEM_RED_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_RED_SCARF
	giveitem ITEM_RED_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainRedScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveBlueScarf::
	checkitemspace ITEM_BLUE_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_BLUE_SCARF
	giveitem ITEM_BLUE_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainBlueScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GivePinkScarf::
	checkitemspace ITEM_PINK_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_PINK_SCARF
	giveitem ITEM_PINK_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainPinkScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveGreenScarf::
	checkitemspace ITEM_GREEN_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_GREEN_SCARF
	giveitem ITEM_GREEN_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainGreenScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveYellowScarf::
	checkitemspace ITEM_YELLOW_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_YELLOW_SCARF
	giveitem ITEM_YELLOW_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainYellowScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf::
	msgbox SlateportCity_PokemonFanClub_Text_NoSpaceForReward, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_CheckMonCool::
	specialvar VAR_RESULT, CheckLeadMonCool
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonCool
	return

SlateportCity_PokemonFanClub_EventScript_SetMonCool::
	setvar VAR_TEMP_1, 1
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonBeauty::
	specialvar VAR_RESULT, CheckLeadMonBeauty
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonBeauty
	return

SlateportCity_PokemonFanClub_EventScript_SetMonBeauty::
	setvar VAR_TEMP_1, 2
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonCute::
	specialvar VAR_RESULT, CheckLeadMonCute
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonCute
	return

SlateportCity_PokemonFanClub_EventScript_SetMonCute::
	setvar VAR_TEMP_1, 3
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonSmart::
	specialvar VAR_RESULT, CheckLeadMonSmart
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonSmart
	return

SlateportCity_PokemonFanClub_EventScript_SetMonSmart::
	setvar VAR_TEMP_1, 4
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonTough::
	specialvar VAR_RESULT, CheckLeadMonTough
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonTough
	return

SlateportCity_PokemonFanClub_EventScript_SetMonTough::
	setvar VAR_TEMP_1, 5
	return

SlateportCity_PokemonFanClub_EventScript_ChairmanNotEnteredContest::
	goto_if_set FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN, SlateportCity_PokemonFanClub_EventScript_ChairmanEnterContest
	msgbox SlateportCity_PokemonFanClub_Text_MeetChairman, MSGBOX_DEFAULT
	setflag FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanEnterContest::
	msgbox SlateportCity_PokemonFanClub_Text_LikeToSeeEnteredContestPokemon, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_MeetChairman::
	msgbox SlateportCity_PokemonFanClub_Text_MeetChairman, MSGBOX_DEFAULT
	setflag FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN
	return

SlateportCity_PokemonFanClub_EventScript_SootheBellWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SOOTHE_BELL, SlateportCity_PokemonFanClub_EventScript_ReceivedSootheBell
	msgbox SlateportCity_PokemonFanClub_Text_ShowMePokemonThatLoveYou, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_150_TO_199, SlateportCity_PokemonFanClub_EventScript_GiveSootheBell
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveSootheBell::
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_PokemonFanClub_Text_PokemonAdoresYou, MSGBOX_DEFAULT
	giveitem ITEM_SOOTHE_BELL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SOOTHE_BELL
	release
	end

SlateportCity_PokemonFanClub_EventScript_ReceivedSootheBell::
	msgbox SlateportCity_PokemonFanClub_Text_TreatPokemonWithLove, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_Man::
	msgbox SlateportCity_PokemonFanClub_Text_PokemonDontLikeFainting, MSGBOX_NPC
	end

SlateportCity_PokemonFanClub_EventScript_Twin::
	msgbox SlateportCity_PokemonFanClub_Text_MonEnjoyedProtein, MSGBOX_NPC
	end

SlateportCity_PokemonFanClub_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_EventScript_Azumarill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_Text_MeetChairman:
	.string "Er-hem! I am the CHAIRMAN of the\n"
	.string "POKéMON FAN CLUB!\p"
	.string "Being the CHAIRMAN, I am naturally\n"
	.string "the most important!\p"
	.string "No one can best me when it comes\n"
	.string "to raising POKéMON. No one!\p"
	.string "Well, let me tell you about\n"
	.string "POKéMON CONTESTS.\p"
	.string "They're events where one can show off\n"
	.string "POKéMON for the world to see!\p"
	.string "However, they're held in far-off towns,\n"
	.string "so I cannot participate often enough.\p"
	.string "That is why we gather here to show\n"
	.string "off our POKéMON, and have others\l"
	.string "show us theirs.$"

SlateportCity_PokemonFanClub_Text_LikeToSeeEnteredContestPokemon:
	.string "The POKéMON of a TRAINER who has\n"
	.string "entered a POKéMON CONTEST…\l"
	.string "That, I would like to see.$"

SlateportCity_PokemonFanClub_Text_AllowMeToExamineYourPokemon:
	.string "Er-hem! I see you've participated in\n"
	.string "a POKéMON CONTEST!\p"
	.string "Please! Allow me to examine how you\n"
	.string "have raised your POKéMON.\p"
	.string "It delights me no end to see POKéMON\n"
	.string "raised by other TRAINERS.\p"
	.string "The happy expressions of POKéMON\n"
	.string "raised with proper care…\p"
	.string "The kindly eyes of the TRAINER that\n"
	.string "nurtured and raised the POKéMON…\p"
	.string "The very thought fills my heart to\n"
	.string "overwhelming with joy.\p"
	.string "Oh! I do beg your pardon!\n"
	.string "Forgive me for prattling on so!\p"
	.string "Please! Allow me to examine how much\n"
	.string "your POKéMON has grown!$"

SlateportCity_PokemonFanClub_Text_HowIsYourPokemonGrowing:
	.string "How is your POKéMON growing?\n"
	.string "Allow me to examine it.$"

SlateportCity_PokemonFanClub_Text_HmHmISee:
	.string "Hm, hm…\n"
	.string "I see…$"

SlateportCity_PokemonFanClub_Text_GiveMonMorePokeblocks:
	.string "Hmmm… It's not bad, but it's not\n"
	.string "good, either…\p"
	.string "You, the TRAINER, must put more\n"
	.string "effort into raising this POKéMON!\p"
	.string "For instance, may I suggest that\n"
	.string "you give it more {POKEBLOCK}S?$"

SlateportCity_PokemonFanClub_Text_NoSpaceForReward:
	.string "Oh, my…\p"
	.string "Your POKéMON is growing quite well,\n"
	.string "so you deserve a reward.\p"
	.string "Unfortunately, you have no space for\n"
	.string "this in your BAG.$"

SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis:
	.string "Your {STR_VAR_1}, it is growing in\n"
	.string "a most impressive manner!\l"
	.string "It is one fine specimen!\p"
	.string "But! If you were to give it this,\n"
	.string "it would grow even better! Indeed!$"

SlateportCity_PokemonFanClub_Text_ExplainRedScarf:
	.string "Let a POKéMON hold that RED SCARF.\p"
	.string "Everyone will recognize the coolness\n"
	.string "of that POKéMON!$"

SlateportCity_PokemonFanClub_Text_ExplainBlueScarf:
	.string "Let a POKéMON hold that BLUE SCARF.\p"
	.string "Its beauty will be accentuated much\n"
	.string "more than now!$"

SlateportCity_PokemonFanClub_Text_ExplainPinkScarf:
	.string "Let a POKéMON hold that PINK SCARF.\p"
	.string "It will draw out the cuteness of\n"
	.string "the POKéMON some more!$"

SlateportCity_PokemonFanClub_Text_ExplainGreenScarf:
	.string "Let a POKéMON hold that GREEN SCARF.\p"
	.string "That will enhance the\n"
	.string "smartness of POKéMON!$"

SlateportCity_PokemonFanClub_Text_ExplainYellowScarf:
	.string "Let a POKéMON hold that YELLOW SCARF.\p"
	.string "It will bolster your POKéMON's\n"
	.string "toughness so much more!$"

SlateportCity_PokemonFanClub_Text_NothingElseToGiveYou:
	.string "I'm sorry, but I've nothing else to\n"
	.string "give you! None at all!\p"
	.string "After all, you're blessed with the gift\n"
	.string "of raising POKéMON without resorting\l"
	.string "to any items!$"

SlateportCity_PokemonFanClub_Text_ShowMePokemonThatLoveYou:
	.string "I love seeing POKéMON that love\n"
	.string "their TRAINERS.\p"
	.string "POKéMON are very sensitive to\n"
	.string "the feelings of their TRAINERS.\p"
	.string "If you treat your POKéMON with love\n"
	.string "and care, they'll love you back.\p"
	.string "When your POKéMON grow to love you,\n"
	.string "please come show me.$"

SlateportCity_PokemonFanClub_Text_PokemonAdoresYou:
	.string "Your POKéMON really adores you.\p"
	.string "For you, a most compassionate\n"
	.string "TRAINER, a gift from the FAN CLUB!$"

SlateportCity_PokemonFanClub_Text_TreatPokemonWithLove:
	.string "POKéMON are very sensitive to\n"
	.string "the feelings of their TRAINERS.\p"
	.string "If you treat your POKéMON with love\n"
	.string "and care, they'll love you back.$"

SlateportCity_PokemonFanClub_Text_PokemonDontLikeFainting:
	.string "If you keep letting a POKéMON faint\n"
	.string "in battle, it'll come to resent it.\p"
	.string "Soon, it will become less trusting\n"
	.string "of the TRAINER.\p"
	.string "In other words, it certainly won't\n"
	.string "like you very much.$"

SlateportCity_PokemonFanClub_Text_MonEnjoyedProtein:
	.string "Do POKéMON enjoy having items used\n"
	.string "on them?\p"
	.string "Mine acted really happy when I gave\n"
	.string "it some PROTEIN.$"

SlateportCity_PokemonFanClub_Text_Skitty:
	.string "SKITTY: Fffnyaaaah…$"

SlateportCity_PokemonFanClub_Text_Zigzagoon:
	.string "ZIGZAGOON: Kyuuu…$"

SlateportCity_PokemonFanClub_Text_Azumarill:
	.string "AZUMARILL: Marimari?$"

SlateportCity_PokemonFanClub_EventScript_FossilGiver::
	lock
	faceplayer
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_FossilGiver_1
	goto SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue
	return

SlateportCity_PokemonFanClub_EventScript_FossilGiver_1:
	goto FossilGiver_Explain
	return


SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue::
	message SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_0
	waitmessage
	dynmultipush SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_1, 0
	dynmultipush SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_2, 1
	dynmultipush SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_3, 2
	dynmultipush SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_4, 3
	dynmultipush SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_5, 127
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	compare VAR_RESULT, 127
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_2
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_5
	compare VAR_RESULT, 1
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_8
	compare VAR_RESULT, 2
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_14
	compare VAR_RESULT, 3
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_19
	return

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_2:
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_6
	release
	end

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_5:
	checkitem ITEM_GREEN_SHARD
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_ComeBackWithGreenShard
	getpartysize
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_11
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_8
	playfanfare MUS_OBTAIN_ITEM
	message SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_9
	waitfanfare
	randomelement SPECIES_ANORITH, SPECIES_LILEEP
	givemon VAR_RESULT, 5
	removeitem ITEM_GREEN_SHARD
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_10
	release
	end

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_8:
	checkitem ITEM_BLUE_SHARD
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_ComeBackWithBlueShard
	getpartysize
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_17
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_8
	playfanfare MUS_OBTAIN_ITEM
	message SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_9
	waitfanfare
	randomelement SPECIES_OMANYTE, SPECIES_KABUTO, SPECIES_TIRTOUGA
	givemon VAR_RESULT, 5
	removeitem ITEM_BLUE_SHARD
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_10
	release
	end

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_11:
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_7, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_14:
	checkitem ITEM_RED_SHARD
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_ComeBackWithRedShard
	getpartysize
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_22
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_8
	playfanfare MUS_OBTAIN_ITEM
	message SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_9
	waitfanfare
	randomelement SPECIES_CRANIDOS, SPECIES_TYRUNT, SPECIES_ARCHEN
	givemon VAR_RESULT, 5
	removeitem ITEM_RED_SHARD
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_10
	release
	end

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_17:
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_7, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_19:
	checkitem ITEM_YELLOW_SHARD
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_ComeBackWithYellowShard
	getpartysize
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_25
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_8
	playfanfare MUS_OBTAIN_ITEM
	message SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_9
	waitfanfare
	randomelement SPECIES_SHIELDON, SPECIES_AMAURA, SPECIES_AERODACTYL
	givemon VAR_RESULT, 5
	removeitem ITEM_YELLOW_SHARD
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_10
	release
	end

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_22:
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_7, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_25:
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_7, MSGBOX_DEFAULT
	release
	end


FossilGiver_Explain::
	message FossilGiver_Explain_Text_0
	waitmessage
	dynmultipush FossilGiver_Explain_Text_1, 0
	dynmultipush FossilGiver_Explain_Text_2, 1
	dynmultipush FossilGiver_Explain_Text_3, 2
	dynmultipush FossilGiver_Explain_Text_4, 3
	dynmultipush FossilGiver_Explain_Text_5, 127
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	compare VAR_RESULT, 127
	goto_if_eq FossilGiver_Explain_2
FossilGiver_Explain_1:
	compare VAR_RESULT, 0
	goto_if_eq FossilGiver_Explain_5
FossilGiver_Explain_4:
	compare VAR_RESULT, 1
	goto_if_eq FossilGiver_Explain_8
FossilGiver_Explain_7:
	compare VAR_RESULT, 2
	goto_if_eq FossilGiver_Explain_14
FossilGiver_Explain_13:
	compare VAR_RESULT, 3
	goto_if_eq FossilGiver_Explain_19
	return

FossilGiver_Explain_2:
	goto SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue
	goto FossilGiver_Explain_1

FossilGiver_Explain_5:
	msgbox FossilGiver_Explain_Text_6
	msgbox FossilGiver_Explain_Text_7, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq FossilGiver_Explain_10
	goto SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue
	goto FossilGiver_Explain_4

FossilGiver_Explain_8:
	msgbox FossilGiver_Explain_Text_8
	msgbox FossilGiver_Explain_Text_7, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq FossilGiver_Explain_16
	goto SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue
	goto FossilGiver_Explain_7

FossilGiver_Explain_10:
	goto FossilGiver_Explain
	goto FossilGiver_Explain_4

FossilGiver_Explain_14:
	msgbox FossilGiver_Explain_Text_9
	msgbox FossilGiver_Explain_Text_7, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq FossilGiver_Explain_21
	goto SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue
	goto FossilGiver_Explain_13

FossilGiver_Explain_16:
	goto FossilGiver_Explain
	goto FossilGiver_Explain_7

FossilGiver_Explain_19:
	msgbox FossilGiver_Explain_Text_10
	msgbox FossilGiver_Explain_Text_7, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq FossilGiver_Explain_24
	goto SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue
	return

FossilGiver_Explain_21:
	goto FossilGiver_Explain
	goto FossilGiver_Explain_13

FossilGiver_Explain_24:
	goto FossilGiver_Explain
	return


SlateportCity_PokemonFanClub_EventScript_EggGiver::
	lock
	faceplayer
	msgbox EggManIntro
	message SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_0
	waitmessage
	dynmultipush SlateportCity_PokemonFanClub_EventScript_EggGiver_Text_0, 0
	dynmultipush SlateportCity_PokemonFanClub_EventScript_EggGiver_Text_1, 1
	dynmultipush SlateportCity_PokemonFanClub_EventScript_EggGiver_Text_2, 127
	dynmultistack 0, 0, FALSE, 6, FALSE, 3, DYN_MULTICHOICE_CB_NONE
	compare VAR_RESULT, 127
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_EggGiver_2
SlateportCity_PokemonFanClub_EventScript_EggGiver_1:
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_EggGiver_5
SlateportCity_PokemonFanClub_EventScript_EggGiver_4:
	compare VAR_RESULT, 1
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_EggGiver_7
	return

SlateportCity_PokemonFanClub_EventScript_EggGiver_2:
	goto SlateportCity_PokemonFanClub_EventScript_EggManNo
	goto SlateportCity_PokemonFanClub_EventScript_EggGiver_1

SlateportCity_PokemonFanClub_EventScript_EggGiver_5:
	goto SlateportCity_PokemonFanClub_EventScript_StarterEggGive
	goto SlateportCity_PokemonFanClub_EventScript_EggGiver_4

SlateportCity_PokemonFanClub_EventScript_EggGiver_7:
	goto SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose
	return


SlateportCity_PokemonFanClub_EventScript_StarterEggGive::
	message SlateportCity_PokemonFanClub_EventScript_StarterEggGive_Text_0
	waitmessage
	dynmultipush SlateportCity_PokemonFanClub_EventScript_StarterEggGive_Text_1, ITEM_RED_SHARD
	dynmultipush SlateportCity_PokemonFanClub_EventScript_StarterEggGive_Text_2, ITEM_BLUE_SHARD
	dynmultipush SlateportCity_PokemonFanClub_EventScript_StarterEggGive_Text_3, ITEM_GREEN_SHARD
	dynmultipush FossilGiver_Explain_Text_5, 127
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	compare VAR_RESULT, 127
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_StarterEggGive_2
SlateportCity_PokemonFanClub_EventScript_StarterEggGive_1:
	compare VAR_RESULT, ITEM_RED_SHARD
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_StarterEggGive_5
SlateportCity_PokemonFanClub_EventScript_StarterEggGive_4:
	compare VAR_RESULT, ITEM_BLUE_SHARD
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_StarterEggGive_8
SlateportCity_PokemonFanClub_EventScript_StarterEggGive_7:
	compare VAR_RESULT, ITEM_GREEN_SHARD
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_StarterEggGive_11
SlateportCity_PokemonFanClub_EventScript_StarterEggGive_10:
	release
	end

SlateportCity_PokemonFanClub_EventScript_StarterEggGive_2:
	goto SlateportCity_PokemonFanClub_EventScript_EggGiver
	goto SlateportCity_PokemonFanClub_EventScript_StarterEggGive_1

SlateportCity_PokemonFanClub_EventScript_StarterEggGive_5:
	goto SlateportCity_PokemonFanClub_EventScript_GiveFireEgg
	goto SlateportCity_PokemonFanClub_EventScript_StarterEggGive_4

SlateportCity_PokemonFanClub_EventScript_StarterEggGive_8:
	goto SlateportCity_PokemonFanClub_EventScript_GiveWaterEgg
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_10
	goto SlateportCity_PokemonFanClub_EventScript_StarterEggGive_7

SlateportCity_PokemonFanClub_EventScript_StarterEggGive_11:
	goto SlateportCity_PokemonFanClub_EventScript_GiveGrassEgg
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_10
	goto SlateportCity_PokemonFanClub_EventScript_StarterEggGive_10


SlateportCity_PokemonFanClub_EventScript_GiveFireEgg::
	checkitem ITEM_RED_SHARD
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_ComeBackWithRedShard
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, SlateportCity_PokemonFanClub_EventScript_NoRoomForEgg
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_8
	playfanfare MUS_OBTAIN_ITEM
	message SlateportCity_PokemonFanClub_Text_ReceivedTheEgg
	waitfanfare
	randomelement SPECIES_CHARMANDER, SPECIES_CYNDAQUIL, SPECIES_TORCHIC, SPECIES_CHIMCHAR, SPECIES_TEPIG, SPECIES_FENNEKIN, SPECIES_LITTEN, SPECIES_SCORBUNNY, SPECIES_FUECOCO
	givemon VAR_RESULT, 5, ITEM_CHARCOAL
	removeitem ITEM_RED_SHARD
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_10
	release
	end


SlateportCity_PokemonFanClub_EventScript_GiveWaterEgg::
	checkitem ITEM_BLUE_SHARD
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_ComeBackWithBlueShard
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, SlateportCity_PokemonFanClub_EventScript_NoRoomForEgg
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_8
	playfanfare MUS_OBTAIN_ITEM
	message SlateportCity_PokemonFanClub_Text_ReceivedTheEgg
	waitfanfare
	randomelement SPECIES_SQUIRTLE, SPECIES_TOTODILE, SPECIES_MUDKIP, SPECIES_PIPLUP, SPECIES_OSHAWOTT, SPECIES_FROAKIE, SPECIES_POPPLIO, SPECIES_SOBBLE, SPECIES_QUAXLY
	givemon VAR_RESULT, 5, ITEM_MYSTIC_WATER
	removeitem ITEM_BLUE_SHARD
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_10
	release
	end


SlateportCity_PokemonFanClub_EventScript_GiveGrassEgg::
	checkitem ITEM_GREEN_SHARD
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_ComeBackWithGreenShard
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, SlateportCity_PokemonFanClub_EventScript_NoRoomForEgg
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_8
	playfanfare MUS_OBTAIN_ITEM
	message SlateportCity_PokemonFanClub_Text_ReceivedTheEgg
	waitfanfare
	randomelement SPECIES_BULBASAUR, SPECIES_CHIKORITA, SPECIES_TREECKO, SPECIES_TURTWIG, SPECIES_SNIVY, SPECIES_CHESPIN, SPECIES_ROWLET, SPECIES_GROOKEY, SPECIES_SPRIGATITO
	givemon VAR_RESULT, 5, ITEM_MIRACLE_SEED
	removeitem ITEM_GREEN_SHARD
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_10
	release
	end


SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose::
	message SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_Text_0
	waitmessage
	dynmultipush SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_Text_1, 0
	dynmultipush SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_Text_2, 1
	dynmultipush FossilGiver_Explain_Text_5, 127
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	compare VAR_RESULT, 127
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_2
SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_1:
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_5
SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_4:
	compare VAR_RESULT, 1
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_8
SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_7:
	release
	end

SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_2:
	goto SlateportCity_PokemonFanClub_EventScript_EggGiver
	goto SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_1

SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_5:
	goto SlateportCity_PokemonFanClub_EventScript_GiveCostumeEgg
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_10
	goto SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_4

SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_8:
	goto SlateportCity_PokemonFanClub_EventScript_GiveCapEgg
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_10
	goto SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_7


SlateportCity_PokemonFanClub_EventScript_GiveCostumeEgg::
	checkitem ITEM_YELLOW_SHARD
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_ComeBackWithYellowShard
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, SlateportCity_PokemonFanClub_EventScript_NoRoomForPikachu
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_8
	playfanfare MUS_OBTAIN_ITEM
	message SlateportCity_PokemonFanClub_Text_ReceivedThePikachu
	waitfanfare
	randomelement SPECIES_PIKACHU_POP_STAR, SPECIES_PIKACHU_BELLE, SPECIES_PIKACHU_ROCK_STAR, SPECIES_PIKACHU_LIBRE, SPECIES_PIKACHU_PHD
	givemon VAR_RESULT, 5, ITEM_LIGHT_BALL
	removeitem ITEM_YELLOW_SHARD
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_10
	release
	end


SlateportCity_PokemonFanClub_EventScript_GiveCapEgg::
	checkitem ITEM_YELLOW_SHARD
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_ComeBackWithYellowShard
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, SlateportCity_PokemonFanClub_EventScript_NoRoomForPikachu
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_8
	playfanfare MUS_OBTAIN_ITEM
	message SlateportCity_PokemonFanClub_Text_ReceivedThePikachu
	waitfanfare
	randomelement SPECIES_PIKACHU_ORIGINAL, SPECIES_PIKACHU_HOENN, SPECIES_PIKACHU_SINNOH, SPECIES_PIKACHU_UNOVA, SPECIES_PIKACHU_KALOS, SPECIES_PIKACHU_ALOLA, SPECIES_PIKACHU_PARTNER, SPECIES_PIKACHU_WORLD
	givemon VAR_RESULT, 5, ITEM_LIGHT_BALL
	removeitem ITEM_YELLOW_SHARD
	msgbox SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_10
	release
	end


SlateportCity_PokemonFanClub_EventScript_EggManNo::
	msgbox SlateportCity_PokemonFanClub_EventScript_EggManNo_Text_0
	release
	end


SlateportCity_PokemonFanClub_EventScript_ComeBackWithRedShard::
	msgbox SlateportCity_PokemonFanClub_Text_ComeBackWithRedShard, MSGBOX_DEFAULT
	release
	end


SlateportCity_PokemonFanClub_EventScript_ComeBackWithBlueShard::
	msgbox SlateportCity_PokemonFanClub_Text_ComeBackWithBlueShard, MSGBOX_DEFAULT
	release
	end


SlateportCity_PokemonFanClub_EventScript_ComeBackWithGreenShard::
	msgbox SlateportCity_PokemonFanClub_Text_ComeBackWithGreenShard, MSGBOX_DEFAULT
	release
	end


SlateportCity_PokemonFanClub_EventScript_ComeBackWithYellowShard::
	msgbox SlateportCity_PokemonFanClub_Text_ComeBackWithYellowShard, MSGBOX_DEFAULT
	release
	end


SlateportCity_PokemonFanClub_EventScript_NoRoomForEgg::
	msgbox SlateportCity_PokemonFanClub_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end


SlateportCity_PokemonFanClub_EventScript_NoRoomForPikachu::
	msgbox SlateportCity_PokemonFanClub_Text_NoRoomForThisPikachu, MSGBOX_DEFAULT
	release
	end


SlateportCity_PokemonFanClub_EventScript_FossilGiver_Text_0:
	.string "Hello, I am a shard collector.\n"
	.string "If you give me a some Shards, I can give\l"
	.string "you an\l"
	.string "Fossil in Return!\p"
	.string "Would you like me to Explain which shard\n"
	.string "gives which fossil?$"

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_0:
	.string "Well im waiting.$"

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_1:
	.string "Plant Fossils$"

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_2:
	.string "Aquatic Fossils$"

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_3:
	.string "Dinosaur Fossils$"

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_4:
	.string "Others Fossils$"

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_5:
	.string "Leave$"

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_6:
	.string "I see.\nCome back when you\nwant a Fossil$"

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_7:
	.string "It seems like you got no room\nFor this fossil\pPlease come back with Space.$"

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_8:
	.string "A wise choice. Here you go.$"

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_9:
	.string "{PLAYER} Recieved the Random Fossil$"

SlateportCity_PokemonFanClub_EventScript_FossilGiver_Continue_Text_10:
	.string "Come back if you have more shards!$"

FossilGiver_Explain_Text_0:
	.string "Which shard would you like me to\n"
	.string "explain?$"

FossilGiver_Explain_Text_1:
	.string "Green Shard$"

FossilGiver_Explain_Text_2:
	.string "Blue Shard$"

FossilGiver_Explain_Text_3:
	.string "Red Shard$"

FossilGiver_Explain_Text_4:
	.string "Yellow Shard$"

FossilGiver_Explain_Text_5:
	.string "Return$"

FossilGiver_Explain_Text_6:
	.string "The Green Shard gets you Lilleep and\n"
	.string "Anorith!$"

FossilGiver_Explain_Text_7:
	.string "Would you like me to explain more?$"

FossilGiver_Explain_Text_8:
	.string "The Blue Shard gets you Omanyte,\n"
	.string "Kabuto and Tirtouga!$"

FossilGiver_Explain_Text_9:
	.string "The Red Shard gets you Cranidos, Archen\n"
	.string "and Tyrunt!$"

FossilGiver_Explain_Text_10:
	.string "The Yellow Shard gets you Shieldon,\n"
	.string "Amaura and Aerodactyl!$"

SlateportCity_PokemonFanClub_EventScript_EggGiver_Text_0:
	.string "Starters$"

SlateportCity_PokemonFanClub_EventScript_EggGiver_Text_1:
	.string "Pikachu Forms$"

SlateportCity_PokemonFanClub_EventScript_EggGiver_Text_2:
	.string "Cancel$"

SlateportCity_PokemonFanClub_EventScript_StarterEggGive_Text_0:
	.string "Which Type of Starter did you want?$"

SlateportCity_PokemonFanClub_EventScript_StarterEggGive_Text_1:
	.string "{COLOR RED}{SHADOW LIGHT_RED}Fire Starters$"

SlateportCity_PokemonFanClub_EventScript_StarterEggGive_Text_2:
	.string "{COLOR BLUE}{SHADOW LIGHT_BLUE}Water Starters$"

SlateportCity_PokemonFanClub_EventScript_StarterEggGive_Text_3:
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}Grass Starters$"

SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_Text_0:
	.string "Which Type of Pikachu forms did you\n"
	.string "want?$"

SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_Text_1:
	.string "Costume$"

SlateportCity_PokemonFanClub_EventScript_PikachuEggChoose_Text_2:
	.string "Caps$"

SlateportCity_PokemonFanClub_EventScript_EggManNo_Text_0:
	.string "I see.\nCome back when you\lwant a Starter\lOr Pikachu form.$"

EggManIntro::
	.string "Hello, I am a shard collector. If you\n"
	.string "give me a Red Shard, I can give you an\l"
	.string "a Fire-type starter Pokémon.\p"
	.string "I can do the same with Blue Shards and\n"
	.string "Green Shards for the other types of\l"
	.string "Starters.\p"
	.string "Or maybe ur more of a pikachu fan.\n"
	.string "well lucky for you i can give you\l"
	.string "a Pikachu Form for a yellow shard.$"

SlateportCity_PokemonFanClub_Text_ComeBackWithRedShard::
	.string "It doesn't look like you have a Red\n"
	.string "Shard. Come back when you do.$"

SlateportCity_PokemonFanClub_Text_ComeBackWithBlueShard::
	.string "It doesn't look like you have a Blue\n"
	.string "Shard. Come back when you do.$"

SlateportCity_PokemonFanClub_Text_ComeBackWithGreenShard::
	.string "It doesn't look like you have a Green\n"
	.string "Shard. Come back when you do.$"

SlateportCity_PokemonFanClub_Text_ComeBackWithYellowShard::
	.string "It doesn't look like you have a Yellow\n"
	.string "Shard. Come back when you do.$"

SlateportCity_PokemonFanClub_Text_NoRoomForThisEgg::
	.string "Oh? You've too many Pokémon.\n"
	.string "There's no room for this Starter.$"

SlateportCity_PokemonFanClub_Text_NoRoomForThisPikachu::
	.string "Oh? You've too many Pokémon.\n"
	.string "There's no room for this Pikachu Form.$"

SlateportCity_PokemonFanClub_Text_ReceivedTheFossil::
	.string "{PLAYER} received a Random Fossil.$"

SlateportCity_PokemonFanClub_Text_ReceivedTheEgg::
	.string "{PLAYER} received a Random Starter.$"

SlateportCity_PokemonFanClub_Text_ReceivedThePikachu::
	.string "{PLAYER} received a Random Pikachu Form.$"
