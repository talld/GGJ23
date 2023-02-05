#include <sys/time.h>
#include <stdio.h>

#include "display.h"
#include "input.h"
#include "vm.h"

int main()
{

	initVM();
	VM_LoadScript("Scripts/cSide.wren");
	VM_LoadScript("Scripts/helpers.wren");
	VM_LoadRoom("Scripts/main.wren");

	struct timeval start, end;
	gettimeofday(&start, NULL);
	end = start; // start with 0 unprocessed

	size_t unprocessedTime = 0;
	size_t unprocessedDisplayTicks = 0;
	while(1)
	{
		size_t endUs = (end.tv_usec);
		size_t startUs = (start.tv_usec);

		if(startUs > endUs)
		{
			// something has gone very wrong...
			// so just zero the dt for now

			endUs = startUs;
		}

		unprocessedTime =  endUs - startUs;
		gettimeofday(&start, NULL);

		if(GetDisplayTickRate() && unprocessedDisplayTicks <= GetDisplayTickRate())
		{
			unprocessedDisplayTicks += unprocessedTime;
		}
		else
		{
			unprocessedDisplayTicks -= GetDisplayTickRate();
			Display_RoomTextTick();
		}

		Input_Process();

		Display_Update();

		gettimeofday(&end, NULL);
	}
}