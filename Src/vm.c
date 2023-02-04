#include "vm.h"
#include "stdlib.h"
#include "stdio.h"
#include "wren.h"
#include "string.h"

#include "display.h"
#include "inventory.h"

static WrenVM* vm;

void writeFn(WrenVM* vm, const char* text)
{
	printf("%s\n", text);
}

void errFn(WrenVM* vm, WrenErrorType type, const char* module, int line, const char* message)
{
	printf("%s", message);
}

static void VM_SetTextSpeed(WrenVM* _)
{
	size_t speed = wrenGetSlotDouble(_, 1);
	if(speed == 0) speed = kDefaultDisplayTickRate;

	SetDisplayTickRate(speed);
}

static void VM_SetRoomText(WrenVM* _)
{
	char const* text = wrenGetSlotString(_, 1);
	Display_SetRoomText(text);
}

static void VM_SetOption(WrenVM* _)
{
	char const* text = wrenGetSlotString(_, 1);
	size_t slot = wrenGetSlotDouble(_, 2);

	Display_SetOption(text, slot);
}

static void VM_AddItem(WrenVM* _)
{
	char const* name = wrenGetSlotString(_, 1);
	size_t count = wrenGetSlotDouble(_, 2);

}

static void VM_CheckItem(WrenVM* _)
{
	char const* name = wrenGetSlotString(_, 1);

	double count = (double) Inventory_Check(name);
	wrenSetSlotDouble(_, 0, count);
}

static void VM_GotoRoom(WrenVM* _)
{
	char const* name = wrenGetSlotString(_, 1);

	loadRoom(name);
}

WrenForeignMethodFn bindForeignMethodFn(WrenVM* _, const char* module, const char* className, bool isStatic, const char* signature)
{
	// we only support one module here
	if(strcmp(signature,"SetTextSpeed(_)") == 0)
	{
		return VM_SetTextSpeed;
	}

	if(strcmp(signature,"SetRoomText(_)") == 0)
	{
		return VM_SetRoomText;
	}

	if(strcmp(signature,"SetOption(_,_)") == 0)
	{
		return VM_SetOption;
	}

	if(strcmp(signature,"AddItem(_,_)") == 0)
	{
		return VM_AddItem;
	}

	if(strcmp(signature,"CheckItem(_)") == 0)
	{
		return VM_CheckItem;
	}

	if(strcmp(signature,"GotoRoom(_)") == 0)
	{
		return VM_GotoRoom;
	}

	return NULL;
}

void initVM(void)
{
	WrenConfiguration config;
	wrenInitConfiguration(&config);
	config.writeFn = &writeFn;
	config.errorFn = &errFn;
	config.bindForeignMethodFn =&bindForeignMethodFn;
	vm = wrenNewVM(&config);

}

void deinitVM(void)
{
	wrenFreeVM(vm);
	atexit(deinitVM);
}

int loadScript(char const* fname)
{
	int err = 0;

	FILE* file = fopen(fname, "r");

	if(file)
	{
		fseek(file, 0, SEEK_END);
		size_t fSize = ftell(file);
		fseek(file, 0, SEEK_SET);

		char* str = calloc(1, fSize+1);
		fread(str, fSize, 1, file);

		WrenInterpretResult res;
		res = wrenInterpret(vm, "main", str);

		fclose(file);
	}
	else
	{
		err = 1;
	}

}

void loadRoom(char const* name)
{
	int err = loadScript(name);
	if(!err)
	{
		wrenEnsureSlots(vm, 1);
		wrenGetVariable(vm, "main", "Room", 0);
		WrenHandle *roomCall = wrenMakeCallHandle(vm, "enter()");
		wrenCall(vm, roomCall);

	}
}