#ifndef GGJ23_DISPLAY_H
#define GGJ23_DISPLAY_H

void Display_Update(void);

void Display_RoomTextTick(void);

void Display_SetRoomText(char const* txt);

int Display_GetDone();

void Display_SkipToNextLine();

void Display_SetOption(char const* optText, size_t index);

size_t Display_GetOptionCount();

size_t Display_SetSelected(size_t i);

void Display_ResetOptions();

#endif //GGJ23_DISPLAY_H
