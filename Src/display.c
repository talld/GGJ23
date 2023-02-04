#include "display.h"

#define TB_IMPL 1
#include "Termbox2/termbox.h"

static char const* sRoomStr;
static size_t sRoomStrLen;

static size_t sRoomStrLineOffset; // total of \n's passed
static size_t sRoomStrOffset; //  the [index] of the string we've displayed too

void Display_RoomTextTick()
{

}

void Display_SetRoomText(char const* txt)
{
	sRoomStr = txt;
	sRoomStrLen = strlen(txt);
	sRoomStrOffset = 0;
	sRoomStrLineOffset = 0;
}

void Display_SkipToNextLine()
{
	while (sRoomStr[sRoomStrOffset] != '\n') sRoomStrOffset++;
}

void Display_AddOption(const char* optText, size_t index)
{

}