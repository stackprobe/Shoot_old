#include "all.h"

PlayerAtari_t *CreatePlayerAtari(double x, double y)
{
	PlayerAtari_t *i = nb(PlayerAtari_t);

	i->X = x;
	i->Y = y;

	return i;
}
void ReleasePlayerAtari(PlayerAtari_t *i)
{
	memFree(i);
}

// <-- cdtor

// <-- accessor
