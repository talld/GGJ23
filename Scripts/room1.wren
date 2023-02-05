Room.SetOnEnter(Fn.new {
	Room.SetText("this is room1")
})

Room.SetOnExit(Fn.new {})

Room.SetOnTextDone(Fn.new {})

Room.SetOnOption(Fn.new { |index|
	// if(index == x) here

	// return next room to run ( can be self )
	return "\0"
})
