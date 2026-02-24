
LilycoveCity_House2_MapScripts::
	.byte 0

LilycoveCity_House2_EventScript_ReceivedRest::
	msgbox LilycoveCity_House2_Text_SleepIsEssential, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House2_Text_NotAwakeYetHaveThis:
	.string "Huh? What? What's that?\p"
	.string "I'm not near awake yet…\n"
	.string "You can have this…$"

LilycoveCity_House2_Text_SleepIsEssential:
	.string "Yawn…\p"
	.string "Sleep is essential for good health…\n"
	.string "Sleep and regain health…$"

LilycoveCity_House2_EventScript_GrassyGlideWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_GRASSY_GLIDE, LilycoveCity_House2_EventScript_GrassyGlideWoman_2
	msgbox LilycoveCity_House2_EventScript_GrassyGlideWoman_Text_1, MSGBOX_DEFAULT
	giveitem ITEM_TM_GRASSY_GLIDE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_GRASSY_GLIDE
	release
	end

LilycoveCity_House2_EventScript_GrassyGlideWoman_2:
	msgbox LilycoveCity_House2_EventScript_GrassyGlideWoman_Text_0, MSGBOX_NPC
	release
	end


LilycoveCity_House2_EventScript_GrassyGlideWoman_Text_0:
	.string "How's that TM going for you?\n"
	.string "Me and Rillaboom had a good fight\l"
	.string "yesterday, choice band ain't no joke.$"

LilycoveCity_House2_EventScript_GrassyGlideWoman_Text_1:
	.string "Hello there, have you ever heard of\n"
	.string "the move Grassy Glide?\p"
	.string "Me and my Rillaboom use it everyday\n"
	.string "to win every battle!\p"
	.string "Grassy Glide might only be 55 bp, but\n"
	.string "with Grassy Terrain active on the field\l"
	.string "it hits like a truck and it has priority!\p"
	.string "here take this!$"
