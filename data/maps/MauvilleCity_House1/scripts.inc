
MauvilleCity_House1_MapScripts::
	.byte 0

MauvilleCity_House1_EventScript_RockSmashDude::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, MauvilleCity_House1_EventScript_ReceivedRockSmash
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	setflag FLAG_HIDE_ROUTE_111_ROCK_SMASH_TIP_GUY
	msgbox MauvilleCity_House1_Text_ExplainRockSmash, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_ReceivedRockSmash::
	msgbox MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis:
	.string "Woohoo!\p"
	.string "I hear people call me the ROCK SMASH\n"
	.string "GUY, but I find that sort of degrading.\p"
	.string "I think I deserve a bit more respect,\n"
	.string "like maybe the ROCK SMASH DUDE.\p"
	.string "Woohoo!\p"
	.string "Anyways, your POKéMON look pretty\n"
	.string "strong.\p"
	.string "I like that!\n"
	.string "Here, take this HIDDEN MACHINE!$"

MauvilleCity_House1_Text_ExplainRockSmash:
	.string "That HM contains ROCK SMASH.\p"
	.string "If you come across large boulders\n"
	.string "that block your path…\p"
	.string "Well, use that HM move and smash\n"
	.string "them right out of your way!\p"
	.string "Yes, sir! Smash rocks aside, I say!\n"
	.string "Woohoo!$"

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock:
	.string "Oh, yes, if you smash a rock, a POKéMON\n"
	.string "could come flying out of hiding.\p"
	.string "Woohoo!$"

MauvilleCity_House1_EventScript_EvTrainer::
	lock
	faceplayer
	checktrainerflag TRAINER_WATTSON_1
	goto_if 1, MauvilleCity_House1_EventScript_EvTrainer_1
	msgbox MauvilleCity_House1_EventScript_EvTrainer_Text_0
	msgbox MauvilleCity_House1_EventScript_EvTrainer_Text_10
	release
	end

MauvilleCity_House1_EventScript_EvTrainer_1:
	msgbox MauvilleCity_House1_EventScript_EvTrainer_Text_0, MSGBOX_DEFAULT
	goto_if_set FLAG_MINIMAL_GRINDING_MODE, MauvilleCity_House1_EventScript_EvTrainer_5
	msgbox MauvilleCity_House1_EventScript_EvTrainer_Text_2, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MauvilleCity_House1_EventScript_EvTrainer_7
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_House1_EventScript_EvTrainer_8
	return

MauvilleCity_House1_EventScript_EvTrainer_5:
	msgbox MauvilleCity_House1_EventScript_EvTrainer_Text_1
	release
	end

MauvilleCity_House1_EventScript_EvTrainer_7:
	msgbox MauvilleCity_House1_EventScript_EvTrainer_Text_3
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, PARTY_NOTHING_CHOSEN
	goto_if_eq MauvilleCity_House1_EventScript_EvTrainer_12
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq MauvilleCity_House1_EventScript_EvTrainer_15
	message MauvilleCity_House1_EventScript_EvTrainer_Text_6
	waitbuttonpress
	fadescreen FADE_TO_BLACK
	special RemoveAllEVs
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	closemessage
	fadescreen FADE_FROM_BLACK
	msgbox MauvilleCity_House1_EventScript_EvTrainer_Text_7, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MauvilleCity_House1_EventScript_EvTrainer_17
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_House1_EventScript_EvTrainer_18
	return

MauvilleCity_House1_EventScript_EvTrainer_8:
	message MauvilleCity_House1_EventScript_EvTrainer_Text_8
	waitbuttonpress
	closemessage
	goto MauvilleCity_House1_EventScript_EvTrainer_Continue
	return

MauvilleCity_House1_EventScript_EvTrainer_12:
	message MauvilleCity_House1_EventScript_EvTrainer_Text_4
	waitbuttonpress
	closemessage
	release
	end

MauvilleCity_House1_EventScript_EvTrainer_15:
	msgbox MauvilleCity_House1_EventScript_EvTrainer_Text_5
	release
	end

MauvilleCity_House1_EventScript_EvTrainer_17:
	message MauvilleCity_House1_EventScript_EvTrainer_Text_8
	waitbuttonpress
	closemessage
	goto MauvilleCity_House1_EventScript_EvTrainer_Continue
	end

MauvilleCity_House1_EventScript_EvTrainer_18:
	message MauvilleCity_House1_EventScript_EvTrainer_Text_9
	waitbuttonpress
	closemessage
	release
	end


MauvilleCity_House1_EventScript_EvTrainer_Continue::
	message MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_0
	dynmultichoice 0, 0, TRUE, 5, 0, DYN_MULTICHOICE_CB_NONE, MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_1, MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_2, MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_3, MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_4, MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_5, MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_6
	switch VAR_RESULT
	case 0, MauvilleCity_House1_EventScript_EvTrainer_Continue_2
	case 1, MauvilleCity_House1_EventScript_EvTrainer_Continue_3
	case 2, MauvilleCity_House1_EventScript_EvTrainer_Continue_4
	case 3, MauvilleCity_House1_EventScript_EvTrainer_Continue_5
	case 4, MauvilleCity_House1_EventScript_EvTrainer_Continue_6
	case 5, MauvilleCity_House1_EventScript_EvTrainer_Continue_7
	return

MauvilleCity_House1_EventScript_EvTrainer_Continue_2:
	closemessage
	trainerbattle_no_intro EV_TRAINER_HP, MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_7
	release
	end

MauvilleCity_House1_EventScript_EvTrainer_Continue_3:
	closemessage
	trainerbattle_no_intro EV_TRAINER_ATK, MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_7
	release
	end

MauvilleCity_House1_EventScript_EvTrainer_Continue_4:
	closemessage
	trainerbattle_no_intro EV_TRAINER_DEF, MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_7
	release
	end

MauvilleCity_House1_EventScript_EvTrainer_Continue_5:
	closemessage
	trainerbattle_no_intro EV_TRAINER_SPA, MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_7
	release
	end

MauvilleCity_House1_EventScript_EvTrainer_Continue_6:
	closemessage
	trainerbattle_no_intro EV_TRAINER_SPD, MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_7
	release
	end

MauvilleCity_House1_EventScript_EvTrainer_Continue_7:
	closemessage
	trainerbattle_no_intro EV_TRAINER_SPEED, MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_7
	release
	end


MauvilleCity_House1_EventScript_HiddenSecretPowerSetter::
	lock
	faceplayer
	goto_if_set FLAG_MINIMAL_GRINDING_MODE, MauvilleCity_House1_EventScript_HiddenSecretPowerSetter_2
	goto_if_set FLAG_BADGE08_GET, MauvilleCity_House1_EventScript_HiddenSecretPowerSetter_2
MauvilleCity_House1_EventScript_HiddenSecretPowerSetter_1:
	msgbox HpChangerHelloCantChange
	release
	end

MauvilleCity_House1_EventScript_HiddenSecretPowerSetter_2:
	goto MauvilleCity_House1_EventScript_ChangeHP
	goto MauvilleCity_House1_EventScript_HiddenSecretPowerSetter_1


MauvilleCity_House1_EventScript_ChangeHP::
	msgbox HpChangerHelloCanChange, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_House1_EventScript_ChangeHP_2
MauvilleCity_House1_EventScript_ChangeHP_1:
	msgbox MauvilleCity_House1_EventScript_ChangeHP_Text_0
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, PARTY_NOTHING_CHOSEN
	goto_if_eq MauvilleCity_House1_EventScript_ChangeHP_5
MauvilleCity_House1_EventScript_ChangeHP_4:
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq MauvilleCity_House1_EventScript_ChangeHP_8
	special BufferMonNickname
	msgbox MauvilleCity_House1_EventScript_ChangeHP_Text_2
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_3, TYPE_FIGHTING
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_4, TYPE_FLYING
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_5, TYPE_POISON
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_6, TYPE_GROUND
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_7, TYPE_ROCK
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_8, TYPE_BUG
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_9, TYPE_GHOST
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_10, TYPE_STEEL
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_11, TYPE_FIRE
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_12, TYPE_WATER
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_13, TYPE_GRASS
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_14, TYPE_ELECTRIC
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_15, TYPE_PSYCHIC
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_16, TYPE_ICE
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_17, TYPE_DRAGON
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_18, TYPE_DARK
	dynmultipush MauvilleCity_House1_EventScript_ChangeHP_Text_19, MULTI_B_PRESSED
	dynmultistack 0, 0, FALSE, 6, FALSE, TYPE_FIGHTING, DYN_MULTICHOICE_CB_NONE
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq MauvilleCity_House1_EventScript_ChangeHP_11
MauvilleCity_House1_EventScript_ChangeHP_10:
	copyvar VAR_0x8005, VAR_RESULT
	bufferhptypeinfo STR_VAR_2, STR_VAR_3, VAR_RESULT
	msgbox AreYouSureHPTypeChange, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_House1_EventScript_ChangeHP_14
MauvilleCity_House1_EventScript_ChangeHP_13:
	msgbox MauvilleCity_House1_EventScript_EvTrainer_Text_6
	fadescreen FADE_TO_BLACK
	special ChangeMonIVsForHPAndSP
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	closemessage
	fadescreen FADE_FROM_BLACK
	msgbox HPTypeChangedComeBackSoon
	release
	end

MauvilleCity_House1_EventScript_ChangeHP_2:
	goto MauvilleCity_House1_EventScript_HPChangerNo
	goto MauvilleCity_House1_EventScript_ChangeHP_1

MauvilleCity_House1_EventScript_ChangeHP_5:
	goto MauvilleCity_House1_EventScript_HPChangerNo
	goto MauvilleCity_House1_EventScript_ChangeHP_4

MauvilleCity_House1_EventScript_ChangeHP_8:
	msgbox MauvilleCity_House1_EventScript_ChangeHP_Text_1
	release
	end

MauvilleCity_House1_EventScript_ChangeHP_11:
	goto MauvilleCity_House1_EventScript_HPChangerNo
	goto MauvilleCity_House1_EventScript_ChangeHP_10

MauvilleCity_House1_EventScript_ChangeHP_14:
	goto MauvilleCity_House1_EventScript_HPChangerNo
	goto MauvilleCity_House1_EventScript_ChangeHP_13


MauvilleCity_House1_EventScript_HPChangerNo::
	msgbox MauvilleCity_House1_EventScript_HPChangerNo_Text_0
	release
	end


MauvilleCity_House1_EventScript_EvTrainer_Text_0:
	.string "Hello there trainer, I'm the EV Trainer\n"
	.string "If you need your Pokémon EV Trained\p"
	.string "I'm the girl for the job.$"

MauvilleCity_House1_EventScript_EvTrainer_Text_1:
	.string "Oh it appears you can't use EV's for\n"
	.string "some strange reason, I'm sorry but i\l"
	.string "can't train with you this way :($"

MauvilleCity_House1_EventScript_EvTrainer_Text_2:
	.string "Before we start training do you want to\n"
	.string "Remove all the EV's your Pokémon\l"
	.string "already have?\p"
	.string "This can make EvTraining easy for you.$"

MauvilleCity_House1_EventScript_EvTrainer_Text_3:
	.string "Which Pokémon would you like their EV's\n"
	.string "to be removed?$"

MauvilleCity_House1_EventScript_EvTrainer_Text_4:
	.string "No Pokémon... Aww.. i see, come back\n"
	.string "soon!$"

MauvilleCity_House1_EventScript_EvTrainer_Text_5:
	.string "I can't change the EV's\nof an Egg you silly goose.$"

MauvilleCity_House1_EventScript_EvTrainer_Text_6:
	.string "I shall begin at once.$"

MauvilleCity_House1_EventScript_EvTrainer_Text_7:
	.string "Do you want to continue?$"

MauvilleCity_House1_EventScript_EvTrainer_Text_8:
	.string "Alrighty, Lets train.$"

MauvilleCity_House1_EventScript_EvTrainer_Text_9:
	.string "No Training...? Aww.. i see, come back\n"
	.string "soon!$"

MauvilleCity_House1_EventScript_EvTrainer_Text_10:
	.string "Oh... its seems like u don't have the\n"
	.string "Dynamo Badge yet. Come back when you\l"
	.string "have gotten the Dynamo Badge!$"

MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_0:
	.string "Wich EV stat would you like to train?$"

MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_1:
	.string "HP$"

MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_2:
	.string "Attack$"

MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_3:
	.string "Defense$"

MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_4:
	.string "Special Attack$"

MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_5:
	.string "Special Defense$"

MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_6:
	.string "Speed$"

MauvilleCity_House1_EventScript_EvTrainer_Continue_Text_7:
	.string "Ur Welcome.$"

MauvilleCity_House1_EventScript_ChangeHP_Text_0:
	.string "Which Pokémon?$"

MauvilleCity_House1_EventScript_ChangeHP_Text_1:
	.string "I can't change the Hidden Power\nof an Egg.$"

MauvilleCity_House1_EventScript_ChangeHP_Text_2:
	.string "Which new Hidden and Secret Power type would\nyou like for {STR_VAR_1}?$"

MauvilleCity_House1_EventScript_ChangeHP_Text_3:
	.string "Fighting$"

MauvilleCity_House1_EventScript_ChangeHP_Text_4:
	.string "Flying$"

MauvilleCity_House1_EventScript_ChangeHP_Text_5:
	.string "Poison$"

MauvilleCity_House1_EventScript_ChangeHP_Text_6:
	.string "Ground$"

MauvilleCity_House1_EventScript_ChangeHP_Text_7:
	.string "Rock$"

MauvilleCity_House1_EventScript_ChangeHP_Text_8:
	.string "Bug$"

MauvilleCity_House1_EventScript_ChangeHP_Text_9:
	.string "Ghost$"

MauvilleCity_House1_EventScript_ChangeHP_Text_10:
	.string "Steel$"

MauvilleCity_House1_EventScript_ChangeHP_Text_11:
	.string "Fire$"

MauvilleCity_House1_EventScript_ChangeHP_Text_12:
	.string "Water$"

MauvilleCity_House1_EventScript_ChangeHP_Text_13:
	.string "Grass$"

MauvilleCity_House1_EventScript_ChangeHP_Text_14:
	.string "Electric$"

MauvilleCity_House1_EventScript_ChangeHP_Text_15:
	.string "Psychic$"

MauvilleCity_House1_EventScript_ChangeHP_Text_16:
	.string "Ice$"

MauvilleCity_House1_EventScript_ChangeHP_Text_17:
	.string "Dragon$"

MauvilleCity_House1_EventScript_ChangeHP_Text_18:
	.string "Dark$"

MauvilleCity_House1_EventScript_ChangeHP_Text_19:
	.string "Cancel$"

MauvilleCity_House1_EventScript_HPChangerNo_Text_0:
	.string "I see. Come back if you change\nyour mind.$"

HpChangerHelloCantChange::
	.string "Hello, I am the Hidden Power type\n"
	.string "changer.\p"
	.string "Oh, it looks like you are not in\n"
	.string "Minimal Grinding Mode.\p"
	.string "I can't modify your Pokémon's IVs until\n"
	.string "you have 3 Badges in that case.$"

HpChangerHelloCanChange::
	.string "Hiya there trainer, im the infamous\n"
	.string "Hidden Power or Secret Power type\l"
	.string "changer. You can choose a Pokémon i can\l"
	.string "quickly modify its IV's to change the\l"
	.string "type of Hidden Power and Secret Power.$"

AreYouSureHPTypeChange::
	.string "So you want me to change\n"
	.string "{STR_VAR_1}'s Hidden Power type\l"
	.string "to {STR_VAR_2}?\p"
	.string "This will modify {STR_VAR_1}'s\n"
	.string "IVs to be the following:\p"
	.string "HP   Atk   Def   SpAtk   SpDef   Spd\n"
	.string "{STR_VAR_3}$"

HPTypeChangedComeBackSoon::
	.string "{STR_VAR_1}'s Hidden Power type\n"
	.string "has been changed to {STR_VAR_2}.\p"
	.string "Come back if you need me to change\n"
	.string "the Hidden Power type of\l"
	.string "another Pokémon.$"
