#include "all.h"

/*
	引数は CreateEnemy_ved でチェックされるので、ここでチェックする必要は無い。
*/
EnemyCommonData_t *GetECD(int kind, int hp, int transFrame, double x, double y, int dit) // ret: bind
{
	static EnemyCommonData_t *ecd;

	if(!ecd)
		ecd = nb_(EnemyCommonData_t);

	ecd->Kind = kind;
	ecd->HP = hp;
	ecd->TransFrame = transFrame;
	ecd->X = x;
	ecd->Y = y;
	ecd->DropItemType = dit;

	return ecd;
}
EnemyCommonData_t *DuplexEnemyCommonData(EnemyCommonData_t *i)
{
	return (EnemyCommonData_t *)memClone(i, sizeof(EnemyCommonData_t));
}
void ReleaseEnemyCommonData(EnemyCommonData_t *i)
{
	memFree(i);
}

// <-- cdtor

// <-- accessor
