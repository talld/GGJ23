class Display {

     foreign static SetTextSpeed(speed)

     foreign static SetRoomText(str)

     foreign static SetOption(str, index)
}

class Inventory {
    foreign static AddItem(str, count)

    foreign static CheckItem(str)
}

class Player {
    foreign static GotoRoom(roomStr)
}
