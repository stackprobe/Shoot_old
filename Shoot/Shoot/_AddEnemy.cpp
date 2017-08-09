#include "all.h"

void AddEnemy(ScrRec_t *sr)
{
	autoList<double> *args = sr->Args;
	EnemyCommonData_t *ecd = sr->EnemyCommonData;
	Enemy_t *e;

	switch(sr->SubId)
	{
	case 0: e = Make_JackOLantern(args, ecd); break;
	case 1: e = Make_BigJackOLantern(args, ecd); break;
	case 2: e = Make_E01(args, ecd); break;
	case 3: e = Make_E02(args, ecd); break;
	case 4: e = Make_E03(args, ecd); break;

	default:
		error();
	}

	AddEnemy(e);
}
