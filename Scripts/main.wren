
roomText = "
░█████╗░██╗░░░██╗███╗░░██╗██╗░█████╗░██╗░░░██╗██╗░░░░░██╗░░░██╗░██████╗
██╔══██╗██║░░░██║████╗░██║██║██╔══██╗██║░░░██║██║░░░░░██║░░░██║██╔════╝
██║░░╚═╝██║░░░██║██╔██╗██║██║██║░░╚═╝██║░░░██║██║░░░░░██║░░░██║╚█████╗░
██║░░██╗██║░░░██║██║╚████║██║██║░░██╗██║░░░██║██║░░░░░██║░░░██║░╚═══██╗
╚█████╔╝╚██████╔╝██║░╚███║██║╚█████╔╝╚██████╔╝███████╗╚██████╔╝██████╔╝
░╚════╝░░╚═════╝░╚═╝░░╚══╝╚═╝░╚════╝░░╚═════╝░╚══════╝░╚═════╝░╚═════╝░
"

Room.SetOnEnter( Fn.new {
	Display.SetTextSpeed(0) // make the crawl faster

	Room.SetText(roomText)

	Room.SetOption("Play", 0)
	Room.SetOption("Info", 1)
	Room.SetOption("Test Bite", 2)
	Room.SetOption("Test Slash", 3)
	Room.SetOption("Exit", 4)
})

Room.SetOnExit(Fn.new {
	// restore text speed
	Display.SetTextSpeed(-1)
})

Room.SetOnTextDone(Fn.new {})

Room.SetOnOption(Fn.new { |index|

	//play
	if(index == 0){
		return "Scripts/Animation/room1.wren"
	}

	if(index == 1){
	Display.SetRoomText(
		Room.GetText + "
		some more info")
	}

	//exit
	if(index == 2) {
		Player.Exit()
	}

	return "\0"
})
