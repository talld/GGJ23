#include "input.h"
#include "Termbox2/termbox.h"

#include "display.h"
#include "vm.h"

static size_t sSelected;

void Input_Reset()
{
	sSelected = 0;
}

void Input_Process()
{
	if(!Display_GetDone()) return;

	struct tb_event ev;
	tb_peek_event(&ev, 1);

	int optionCount = Display_GetOptionCount();
	if(optionCount)
	{
		if (ev.type == TB_EVENT_KEY)
		{
			switch (ev.key)
			{
				case TB_KEY_ENTER:
					VM_NotifyOption(sSelected);
					break;

				case TB_KEY_ARROW_DOWN:
					if (sSelected < Display_GetOptionCount() - 1)
						sSelected++;
					break;

				case TB_KEY_ARROW_UP:
					if (sSelected > 0)
					{
						sSelected--;
					}
			}
		}
		Display_SetSelected(sSelected);
	}
	else // if we dont have have any options
	{
		VM_NotifyOption(0);
	}
}