#include "display.h"

#define TB_IMPL 1
#include "Termbox2/termbox.h"
#include "vm.h"

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
	if (!Display_GetDone())
	{
		sDisplayNeedsUpdate = 1;
		sRoomStrOffset++;
	}

	int lines = Display_GetRemainingLines(preSkip);
	int over = 0;

	int area = 24;

	if (sOptionCount)
	{
		area = kDisplayRoomTextHeight;
	}

	if (lines > area)
	{
		over = lines - area;
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

	if(Display_GetDone())
	{
		VM_NotifyDisplayDone();
		if (sOptionCount)
		{
			char const *const line = "--------------------------------------------------------------------------------";

			tb_print(0, kDisplayRoomTextHeight, 0, 0, line);

			int i;
			for (i = 0; i <= sOptionsOnScreen; i++)
			{
				int y = kDisplayRoomTextHeight + i + 1;
				char const *const str = sOptionTexts[i];

				if(str)
				{
					uintattr_t fg = 0;
					uintattr_t bg = 0;

					if (i == sSelectedIndex)
					{
						fg = TB_UNDERLINE | TB_BOLD;
						bg = TB_BLUE;
					}

					tb_print(0, y, fg, bg, str);
				}
			}

			tb_print(0, kDisplayRoomTextHeight + (sOptionsOnScreen + 1) + 1, 0, 0, line);

			if (sOptionsOnScreen < sOptionCount)
			{
				sOptionsOnScreen++;
			}

			sDisplayNeedsUpdate = 1;
		}
	}
}

void Display_SetRoomText(char const* txt)
{
	if(!sHasBeenInited)
	{
		Display_Init();
	}

	sRoomStrOffset = 0;
	sRoomStrLineOffset = 0;



	if(sRoomStr && sRoomStrLen)
	{
		size_t newLen = strlen(txt);
		size_t min = (sRoomStrLen > newLen)? newLen : sRoomStrLen;

		int i = 0;
		while (min-- && (txt[sRoomStrOffset]) == (sRoomStr[sRoomStrOffset]) )
		{
			sRoomStrOffset++;
		}
	}

	sRoomStrLen = strlen(txt);
	sRoomStr = txt;
}

int Display_GetDone()
{
	int ret = (sRoomStrOffset == sRoomStrLen);
	return ret;
}

void Display_SkipToNextLine()
{
	while (sRoomStr[sRoomStrOffset] != '\n') sRoomStrOffset++;
}

void Display_SetOption(char const* optText, size_t index)
{
	if(index >= sOptionCount)
	{
		size_t newEntries = index - sOptionCount;

		sOptionCount = index;
		sOptionTexts = realloc((void*)sOptionTexts, sizeof(char*) * (sOptionCount+1));

		while(newEntries--)
		{
			sOptionTexts[sOptionCount - newEntries] = NULL;
		}
	}

	if(sOptionTexts[index])
	{
		free((void*)sOptionTexts[index]);
	}

	sOptionTexts[index] = strdup(optText);
	sOptionsOnScreen = 0;
}

size_t Display_GetOptionCount()
{
	return sOptionsOnScreen;
}

size_t Display_SetSelected(size_t i)
{
	if(sSelectedIndex != i)
	{
		sSelectedIndex = i;
		sDisplayNeedsUpdate = 1;
	}
}

void Display_ResetOptions()
{
	size_t i;
	for(i = 0; i < sOptionCount; i++)
	{
		free((void*)sOptionTexts[i]);
	}

	free(sOptionTexts);
	sOptionTexts = NULL;
	sOptionCount = 0;
	sOptionsOnScreen = 0;
	sSelectedIndex = 0;
}