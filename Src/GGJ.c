#include "GGJ.pch"

static size_t sDisplayTickRate = kDefaultDisplayTickRate;

size_t GetDisplayTickRate()
{
	return sDisplayTickRate;
}

void SetDisplayTickRate(size_t rate)
{
	sDisplayTickRate = rate;
}
