#include <malloc.h>
#include "inventory.h"

#include "string.h"

static size_t sInventorySize;
static char const** sItemNames;
static size_t* sItemCounts;

static size_t GetItemIndex(char const* itemName)
{
	size_t itemIndex = -1;

	if(itemName)
	{
		size_t i;
		for (i = 0; i < sInventorySize; i++)
		{
			if (strcmp(itemName, sItemNames[i]) == 0)
			{
				itemIndex = i;
				break;
			}
		}
	}

	return itemIndex;
}

void Inventory_AddItem(char const* itemName, size_t count)
{
	size_t itemIndex = GetItemIndex(itemName);

	// we haven't found it...
	if(itemIndex == -1)
	{ // so add it
		itemIndex = sInventorySize++;

		sItemNames = realloc(sItemNames, sizeof(*sItemNames) * sInventorySize);
		sItemCounts = realloc(sItemCounts, sizeof(*sItemCounts) * sInventorySize);
		sItemCounts[itemIndex] = 0; // start at 0
	}

	sItemNames[itemIndex] = itemName;
	sItemCounts[itemIndex] += count;
}

size_t Inventory_CheckItem(char const* itemName)
{
	size_t count = 0;

	size_t itemIndex = GetItemIndex(itemName);
	if(itemIndex != -1)
	{
		count = sItemCounts[itemIndex];
	}

	return count;
}

//
// Vars ( hidden to the player )
//

static size_t sVarsSize;
static char const** sVarNames;
static size_t* sVarCounts;

static size_t GetVarIndex(char const* varName)
{
	size_t varIndex = -1;

	if(varName)
	{
		size_t i;
		for (i = 0; i < sVarsSize; i++)
		{
			if (strcmp(varName, sVarNames[i]) == 0)
			{
				varIndex = i;
				break;
			}
		}
	}

	return varIndex;
}

void Inventory_AddVar(char const* varName, size_t val)
{
	size_t varIndex = GetVarIndex(varName);

	// we haven't found it...
	if(varIndex == -1)
	{ // so add it
		varIndex = sVarsSize++;

		sVarNames = realloc(sVarNames, sizeof(*sVarNames) * sVarsSize);
		sVarCounts = realloc(sVarCounts, sizeof(*sVarCounts) * sVarsSize);
		sVarCounts[varIndex] = 0; // start at 0
	}

	sVarNames[varIndex] = varName;
	sVarCounts[varIndex] += val;
}

size_t Inventory_CheckVar(char const* varName)
{
	size_t val = 0;

	size_t varIndex = GetVarIndex(varName);
	if(varIndex != -1)
	{
		val = sVarCounts[varIndex];
	}

	return val;
}