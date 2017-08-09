#include "all.h"

Enemy_t *CreateEnemy_ved(
	int (*eachFrameFunc)(Enemy_t *, void *),
	void (*deadEventFunc)(Enemy_t *, void *),
	void (*releaseExtraDataFunc)(Enemy_t *, void *),
	void *extraData,
	EnemyCommonData_st *ecd
	)
{
	errorCase(!eachFrameFunc);
	errorCase(!deadEventFunc);
	errorCase(!releaseExtraDataFunc);
	errorCase(!extraData);
	errorCase(!ecd);
	errorCase(!m_isRange(ecd->Kind, 0, EK_MAX - 1));
	errorCase(!m_isRange(ecd->HP, 0, IMAX));
	errorCase(!m_isRange(ecd->TransFrame, 0, IMAX));
	errorCase(!m_isRange(ecd->X, -IMAX, IMAX));
	errorCase(!m_isRange(ecd->Y, -IMAX, IMAX));
	errorCase(!m_isRange(ecd->DropItemType, 0, IMAX));

	Enemy_t *i = nb(Enemy_t);

	i->EachFrameFunc = eachFrameFunc;
	i->DeadEventFunc = deadEventFunc;
	i->ReleaseExtraDataFunc = releaseExtraDataFunc;
	i->ExtraData = extraData; // bind
	i->Kind = ecd->Kind;
	i->HP = ecd->HP;
	i->TransFrame = ecd->TransFrame;
	i->X = ecd->X;
	i->Y = ecd->Y;
	i->TargetX = ecd->X;
	i->TargetY = ecd->Y;
	i->DropItemType = ecd->DropItemType;

	i->Frame = -1; // -1 == uninited

	return i;
}
void ReleaseEnemy(Enemy_t *i)
{
	i->ReleaseExtraDataFunc(i, i->ExtraData);
	memFree(i);
}

// <-- cdtor

int IsTrans(Enemy_t *i)
{
	return !i->HP || i->OnFieldFrame < i->TransFrame;
}

// <-- accessor

/*
	処理
	描画 -> GDc.DE or DES or DI
	当たり判定 -> AddEnemyAtari()
*/
static int EnemyEachFrame(Enemy_t *i) // ret: dead
{
	return i->EachFrameFunc(i, i->ExtraData);
}
void AllEnemyEachFrame(void)
{
	for(int index = 0; index < GDc.EnemyList->GetCount(); index++)
	{
		Enemy_t *i = GDc.EnemyList->GetElement(index);

		i->Frame++; // 0～

		if(i->OnFieldFrame || !IsOutOfField(i->X, i->Y, 0.0))
			i->OnFieldFrame++;

		if(i->DeadFlag || EnemyEachFrame(i)) // ? dead
		{
			ReleaseEnemy(i);
			GDc.EnemyList->SetElement(index, NULL);
		}
	}
	GDc.EnemyList->MultiDiscard(isPointNull);
}
void AddEnemy(Enemy_t *i)
{
	GDc.EnemyList->AddElement(i);
}
Enemy_t *GetLastAddedEnemy(void)
{
	return GDc.EnemyList->GetTailElement();
}
double nextArg_d(autoList<double> *args, int &rIndex, double minval, double maxval)
{
	double retval = args->GetElement(rIndex++);
	m_range(retval, minval, maxval);
	return retval;
}
int nextArg_i(autoList<double> *args, int &rIndex, int minval, int maxval)
{
	return d2i(nextArg_d(args, rIndex, minval, maxval));
}
void CommonEnemyDeadProc(Enemy_t *i)
{
	switch(i->Kind)
	{
	case EK_ENEMY:
		{
			DropItem(i);

			CEE.PicRes = GetBGRPicRes();
			CEE.EndPicId = D_ENEMYDIE_00_END | DTP;
			CEE.PicIdFrmPerInc = 2;
//			CEE.BlendAddOn = 1; // 加算専用画像
			AddCommonEffect(
				GDc.EE,
				0,
				D_ENEMYDIE_00 | DTP,
				i->X,
				i->Y,
				dRnd() * PI * 2.0,
				1.0,
				0.7
				);
			CEE_Reset();
		}
		break;

	case EK_TAMA:
		{
			CEE.EndPicId = D_ENEMYSHOTDIE_00_END | DTP;
			CEE.PicIdFrmPerInc = 3;
			CEE.BlendAddOn = 1; // 加算専用画像
			AddCommonEffect(
				GDc.EE,
				0,
				D_ENEMYSHOTDIE_00 | DTP,
				i->X,
				i->Y
				);
			CEE_Reset();
		}
		break;

	case EK_ITEM:
		error(); // アイテムは独自の死亡イベントを行う。

	default:
		error();
	}
}
