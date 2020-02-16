#include "all.h"

PlayerShotAtari_t *CreatePlayerShotAtari(PlayerShot_t *owner, double x, double y, double r)
{
	errorCase(!owner);
	// x
	// y
	errorCase(r < 1.0);

	PlayerShotAtari_t *i = nb_(PlayerShotAtari_t);

	i->Owner = owner;
	i->X = x;
	i->Y = y;
	i->R = r;

	return i;
}
void ReleasePlayerShotAtari(PlayerShotAtari_t *i)
{
	memFree(i);
}

// <-- cdtor

// <-- accessor
