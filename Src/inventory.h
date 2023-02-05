#ifndef GGJ_INVENTORY_H
#define GGJ_INVENTORY_H

void Inventory_AddItem(char const* itemName, size_t count);

size_t Inventory_CheckItem(char const* itemName);

void Inventory_AddVar(char const* varName, size_t val);

size_t Inventory_CheckVar(char const* varName);

#endif //GGJ_INVENTORY_H
