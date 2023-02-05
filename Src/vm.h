#ifndef GGJ_VM_H
#define GGJ_VM_H

void initVM(void);

void VM_NotifyOption(size_t index);

void VM_NotifyDisplayDone();

int VM_LoadScript(char const* fname);

void VM_LoadRoom(char const* name);

#endif //GGJ_VM_H
