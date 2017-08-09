#include "all.h"

// ---- E01 ----

static E01_t *Create_E01(autoList<double> *args)
{
	E01_t *e = nb(E01_t);
	int rIndex = 0;

	e->FEKind = nextArg_i(args, rIndex, 0, FAIRYETC_KIND_NUM - 1);
	e->ShotType = nextArg_i(args, rIndex, 0, IMAX);
	e->Speed = nextArg_d(args, rIndex, MICRO, FIELD_H);
	e->XDir = nextArg_i(args, rIndex, 0, 1) ? 1 : -1;
	e->MaxY = nextArg_d(args, rIndex, 0.0, FIELD_H);
	e->ApprRate = nextArg_d(args, rIndex, 0.0, 1.0 - MICRO);

	return e;
}
static void Release_E01(Enemy_t *i, E01_t *e)
{
	memFree(e);
}
static int EachFrame_E01(Enemy_t *i, E01_t *e)
{
	if(i->TargetY < e->MaxY)
	{
		i->TargetY += e->Speed;
	}
	else
	{
		i->TargetX += e->Speed * e->XDir;
	}

	m_approach(i->X, i->TargetX, e->ApprRate);
	m_approach(i->Y, i->TargetY, e->ApprRate);

	CommonEnemyShotEachFrame(i, e->ShotType);

	return FairyEtcEachFrame(i, e->FEKind);
}
static void Dead_E01(Enemy_t *i, E01_t *e)
{
	CommonEnemyDeadProc(i);
}
Enemy_t *Make_E01(autoList<double> *args, EnemyCommonData_t *ecd)
{
	return CreateEnemy(
		EachFrame_E01,
		Dead_E01,
		Release_E01,
		Create_E01(args),
		ecd
		);
}

// ---- E02 ----

static E02_t *Create_E02(autoList<double> *args)
{
	E02_t *e = nb(E02_t);
	int rIndex = 0;

	e->FEKind = nextArg_i(args, rIndex, 0, FAIRYETC_KIND_NUM - 1);
	e->ShotType = nextArg_i(args, rIndex, 0, IMAX);
	e->PrmTargetX = nextArg_d(args, rIndex, 0, FIELD_W);
	e->PrmTargetY = nextArg_d(args, rIndex, 0, FIELD_H);
	e->ApprRate = nextArg_d(args, rIndex, 0.0, 1.0 - MICRO);
	e->XAdd = nextArg_d(args, rIndex, -FIELD_W, FIELD_W);
	e->YAdd = nextArg_d(args, rIndex, -FIELD_H, FIELD_H);

	return e;
}
static void Release_E02(Enemy_t *i, E02_t *e)
{
	memFree(e);
}
static int EachFrame_E02(Enemy_t *i, E02_t *e)
{
	if(!i->Frame) // init
	{
		i->TargetX = e->PrmTargetX;
		i->TargetY = e->PrmTargetY;
	}

	i->TargetX += e->XAdd;
	i->TargetY += e->YAdd;

	m_approach(i->X, i->TargetX, e->ApprRate);
	m_approach(i->Y, i->TargetY, e->ApprRate);

	CommonEnemyShotEachFrame(i, e->ShotType);

	return FairyEtcEachFrame(i, e->FEKind);
}
static void Dead_E02(Enemy_t *i, E02_t *e)
{
	CommonEnemyDeadProc(i);
}
Enemy_t *Make_E02(autoList<double> *args, EnemyCommonData_t *ecd)
{
	return CreateEnemy(
		EachFrame_E02,
		Dead_E02,
		Release_E02,
		Create_E02(args),
		ecd
		);
}

// ---- E03 ----

static E03_t *Create_E03(autoList<double> *args)
{
	E03_t *e = nb(E03_t);
	int rIndex = 0;

	e->FEKind = nextArg_i(args, rIndex, 0, FAIRYETC_KIND_NUM - 1);
	e->ShotType = nextArg_i(args, rIndex, 0, IMAX);
	e->PrmTargetX = nextArg_d(args, rIndex, 0, FIELD_W);
	e->PrmTargetY = nextArg_d(args, rIndex, 0, FIELD_H);
	e->EvacFrame = nextArg_i(args, rIndex, 0, IMAX);
	e->EvacXAdd = nextArg_d(args, rIndex, -IMAX, IMAX);
	e->EvacYAdd = nextArg_d(args, rIndex, -IMAX, IMAX);

	return e;
}
static void Release_E03(Enemy_t *i, E03_t *e)
{
	memFree(e);
}
static int EachFrame_E03(Enemy_t *i, E03_t *e)
{
	if(!i->Frame) // init
	{
		i->TargetX = e->PrmTargetX;
		i->TargetY = e->PrmTargetY;
	}

	const double APPR_RATE = 0.99;
	const double EVAC_RATE = 1.01;

	if(i->Frame < e->EvacFrame)
	{
		m_approach(i->X, i->TargetX, APPR_RATE);
		m_approach(i->Y, i->TargetY, APPR_RATE);
	}
	else
	{
		i->X += e->EvacXAdd;
		i->Y += e->EvacYAdd;

		e->EvacXAdd *= EVAC_RATE;
		e->EvacYAdd *= EVAC_RATE;
	}

	CommonEnemyShotEachFrame(i, e->ShotType);

	return FairyEtcEachFrame(i, e->FEKind);
}
static void Dead_E03(Enemy_t *i, E03_t *e)
{
	CommonEnemyDeadProc(i);
}
Enemy_t *Make_E03(autoList<double> *args, EnemyCommonData_t *ecd)
{
	return CreateEnemy(
		EachFrame_E03,
		Dead_E03,
		Release_E03,
		Create_E03(args),
		ecd
		);
}
