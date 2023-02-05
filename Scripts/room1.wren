Room.SetOnEnter(Fn.new {

	Room.SetText("
You Didn't ask for this quest,
but when the lord Barons sceptre went missing it was you they came too.
...
your escapades in the village are well known,
Perhaps news of you even reached the keep.
		")

	Room.SetOption("No good deed goes unpunished", 0)
	Room.SetOption("My reputation proceeds me", 1)
})

Room.SetOnExit(Fn.new {})

Room.SetOnTextDone(Fn.new {})

Room.SetOnOption(Fn.new { |index|

	if(index == 0) {
	Room.SetText(Room.GetText() + "
at least you are being paid for this...")

		Room.SetEncounterReturn("Scripts/warrenEntrance.wren")
	}

	if(index == 1) {
		Room.SetText(Room.GetText() + "
at last a chance to prove yourself")

	Room.SetEncounterReturn("Scripts/warrenEntrance.wren")
	}

	return "Scripts/Continue.wren"
})
