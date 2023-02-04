#include "display.h"

#define TB_IMPL 1
#include "Termbox2/termbox.h"

static int sHasBeenInited;
static int sDisplayNeedsUpdate;

static char const*  sRoomStr;
static size_t sRoomStrLen;

static size_t sRoomStrLineOffset; // total of \n's passed
static size_t sRoomStrOffset; //  the [index] of the string we've displayed too

static size_t sOptionCount;
static char const** sOptionTexts;

static size_t sOptionsOnScreen;
static size_t sSelectedIndex;

static void Display_Deinit(void)
{
	tb_deinit();
	tb_shutdown();
}

static void Display_Init(void)
{
	tb_init();
	atexit(Display_Deinit);
}

void Display_Update()
{
	if(sDisplayNeedsUpdate)
	{
		sDisplayNeedsUpdate = 0;
		tb_present();
		tb_clear();
	}
}

// go till we hit n '\n' then return a pointer to the first char past
static char const* Display_SkipLines(size_t n, char const* str)
{
	char const* runner = str;

	while (n)
	{
		n--;
		char c;
		while( (c = *runner) && c != '\n' )
		{
			runner++;
		}

		if(*runner == '\n') runner++;
	}

	return runner;
}



static int Display_GetRemainingLines(char const* str)
{
	size_t linesFound = 0;
	char const* runner = str;

	char c;
	while( (c = *runner) )
	{
		if(c == '\n')
		{
			linesFound++;
		}
		runner++;
	}

	return (int)linesFound;
}

static size_t Display_GetIndexOfFirstNewline(char const* str)
{
	size_t i = 0;

	while(str[i] && str[i] != '\n') i++;

	return i;
}

void Display_RoomTextTick()
{

		char const *preSkip = strndup(sRoomStr, sRoomStrOffset);
		if(sRoomStrOffset < sRoomStrLen)
		{
			sDisplayNeedsUpdate = 1;
			sRoomStrOffset++;
		}

		int lines = Display_GetRemainingLines(preSkip);
		int over = 0;

		if (lines > kDisplayRoomTextHeight)
		{
			over = lines - kDisplayRoomTextHeight;
		}

		do
		{
			char const *postSkip = Display_SkipLines(lines, preSkip);

			size_t len = Display_GetIndexOfFirstNewline(postSkip);
			char const *postStrip = strndup(postSkip, len);

			tb_print(0, lines - over, 0, 0, postStrip);

			free(postStrip);
		} while (lines-- > over);
		free(preSkip);

	if(sRoomStrOffset == sRoomStrLen
	&& sOptionCount)

	{
		char const* const line = "--------------------------------------------------------------------------------" ;

		tb_print(0, kDisplayRoomTextHeight + 2, 0, 0, line);

		int i;
		for(i = 0; i <= sOptionsOnScreen; i++)
		{
			int y = kDisplayRoomTextHeight + 2 + i + 1;
			char const* const str = sOptionTexts[i];
			uintattr_t fg = 0;
			uintattr_t bg = 0;

			if( i == sSelectedIndex)
			{
				fg = TB_UNDERLINE | TB_BOLD;
				bg = TB_BLUE;
			}

			tb_print(0, y, fg, bg, str);
		}

		tb_print(0, kDisplayRoomTextHeight + 2 + (sOptionsOnScreen+1) + 1, 0, 0, line);

		if(sOptionsOnScreen < sOptionCount)
		{
			sOptionsOnScreen++;
		}

		sDisplayNeedsUpdate = 1;
	}

}

void Display_SetRoomText(char const* txt)
{
	if(!sHasBeenInited)
	{
		Display_Init();
	}

	sRoomStr = txt;
	sRoomStrLen = strlen(txt);
	sRoomStrOffset = 0;
	sRoomStrLineOffset = 0;
}

void Display_SkipToNextLine()
{
	while (sRoomStr[sRoomStrOffset] != '\n') sRoomStrOffset++;
}

void Display_SetOption(char const* optText, size_t index)
{
	if(index >= sOptionCount)
	{
		sOptionTexts = realloc((void*)sOptionTexts, sizeof(char*) * (sOptionCount+1));
		sOptionCount = index;
	}

	sOptionTexts[index] = optText;
	sOptionsOnScreen = 0;
}

size_t Display_GetOptionCount()
{
	return sOptionsOnScreen;
}

size_t Display_SetSelected(size_t i)
{
	sSelectedIndex = i;
}