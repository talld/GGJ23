
roomText = "
░█████╗░██╗░░░██╗███╗░░██╗██╗░█████╗░██╗░░░██╗██╗░░░░░██╗░░░██╗░██████╗
██╔══██╗██║░░░██║████╗░██║██║██╔══██╗██║░░░██║██║░░░░░██║░░░██║██╔════╝
██║░░╚═╝██║░░░██║██╔██╗██║██║██║░░╚═╝██║░░░██║██║░░░░░██║░░░██║╚█████╗░
██║░░██╗██║░░░██║██║╚████║██║██║░░██╗██║░░░██║██║░░░░░██║░░░██║░╚═══██╗
╚█████╔╝╚██████╔╝██║░╚███║██║╚█████╔╝╚██████╔╝███████╗╚██████╔╝██████╔╝
░╚════╝░░╚═════╝░╚═╝░░╚══╝╚═╝░╚════╝░░╚═════╝░╚══════╝░╚═════╝░╚═════╝░
"

Room.SetOnEnter( Fn.new {
	Display.SetTextSpeed(600) // make the crawl faster

	Inventory.AddItem("sword",1)

	Room.SetText(roomText)

	Room.SetOption("Play", 0)
	Room.SetOption("Info", 1)
	Room.SetOption("Exit", 2)

})

Room.SetOnExit(Fn.new {
	// restore text speed
	Display.SetTextSpeed(-1)
})

Room.SetOnTextDone(Fn.new {})

Room.SetOnOption(Fn.new { |index|

	//play
	if(index == 0){
		Room.SetAnimReturn("Scripts/room1.wren")
		return "Scripts/Animation/bite1.wren"
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
