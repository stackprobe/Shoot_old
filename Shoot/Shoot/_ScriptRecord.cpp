#include "all.h"

ScrRec_t *CreateScrRec(void)
{
	ScrRec_t *i = nb(ScrRec_t);

	return i;
}
void ReleaseScrRec(ScrRec_t *i)
{
	delete i->Args;
	ReleaseEnemyCommonData(i->EnemyCommonData);

	memFree(i);
}

// <-- cdtor

// <-- accessor
