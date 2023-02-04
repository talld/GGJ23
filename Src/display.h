#ifndef GGJ23_DISPLAY_H
#define GGJ23_DISPLAY_H

void Display_Update(void);

void Display_RoomTextTick(void);

void Display_SetRoomText(char const* txt);

void Display_SkipToNextLine();

void Display_SetOption(char const* optText, size_t index);

#endif //GGJ23_DISPLAY_H
