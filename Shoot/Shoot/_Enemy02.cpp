#include "all.h"

// ---- JackOLantern ----

static JackOLantern_t *Create_JackOLantern(autoList<double> *args)
{
	JackOLantern_t *e = nb_(JackOLantern_t);
	int rIndex = 0;

	e->ShotType = nextArg_i(args, rIndex, 0, IMAX);
	e->XRate = nextArg_d(args, rIndex, 0.0, FIELD_W);
	e->YAdd = nextArg_d(args, rIndex, MICRO, FIELD_H);
	e->Rot = nextArg_d(args, rIndex, 0.0, PI * 2.0);
	e->RotAdd = nextArg_d(args, rIndex, -PI * 2.0, PI * 2.0);

	return e;
}
static void Release_JackOLantern(Enemy_t *i, JackOLantern_t *e)
{
	memFree(e);
}
static int EachFrame_JackOLantern(Enemy_t *i, JackOLantern_t *e)
{
	if(!i->Frame) // init
	{
		e->AxisX = i->X;
	}

	i->X = e->AxisX + sin(e->Rot) * e->XRate;
	i->Y += e->YAdd;
	e->Rot += e->RotAdd;

	CommonEnemyShotEachFrame(i, e->ShotType);

	int koma = i->Frame / 7;
	koma %= 2;

	DPE.TL = GDc.DE;
	DPE.MosaicOn = 1;
	DrawBegin(D_PUMPKIN_00 + koma | DTP, i->X, i->Y);
	DrawZoom(2.0);
	DrawEnd();
	DPE_Reset();

	AddEnemyAtari(CreateEnemyAtari(i, i->X - 1.0, i->Y + 3.0, 30.0));

	return IsOutOfField(i->X, i->Y);
}
static void Dead_JackOLantern(Enemy_t *i, JackOLantern_t *e)
{
	CommonEnemyDeadProc(i);
}
Enemy_t *Make_JackOLantern(autoList<double> *args, EnemyCommonData_t *ecd)
{
	return CreateEnemy(
		EachFrame_JackOLantern,
		Dead_JackOLantern,
		Release_JackOLantern,
		Create_JackOLantern(args),
		ecd
		);
}

// ---- BigJackOLantern ----

static BigJackOLantern_t *Create_BigJackOLantern(autoList<double> *args)
{
	BigJackOLantern_t *e = nb_(BigJackOLantern_t);
	int rIndex = 0;

	e->ShotType = nextArg_i(args, rIndex, 0, IMAX);
	e->R = nextArg_d(args, rIndex, 0.0, FIELD_H); // ƒfƒJ‚¢•û‚ÅH
	e->RApprRate = nextArg_d(args, rIndex, 0.0, 1.0 - MICRO);
	e->Rot = nextArg_d(args, rIndex, 0.0, PI * 2.0);
	e->RotAdd = nextArg_d(args, rIndex, -PI * 2.0, PI * 2.0);
	e->XAdd = nextArg_d(args, rIndex, -FIELD_W, FIELD_W);
	e->YAdd = nextArg_d(args, rIndex, -FIELD_H, FIELD_H);

	return e;
}
static void Release_BigJackOLantern(Enemy_t *i, BigJackOLantern_t *e)
{
	memFree(e);
}
static int EachFrame_BigJackOLantern(Enemy_t *i, BigJackOLantern_t *e)
{
	if(!i->Frame) // init
	{
		e->AxisX = i->X;
		e->AxisY = i->Y;
	}

	e->AxisX += e->XAdd;
	e->AxisY += e->YAdd;
	m_approach(e->R, 0.0, e->RApprRate);
	e->Rot += e->RotAdd;

	i->X = e->AxisX + cos(e->Rot) * e->R;
	i->Y = e->AxisY + sin(e->Rot) * e->R;

	CommonEnemyShotEachFrame(i, e->ShotType);

	int koma = i->Frame / 5;
	koma %= 2;

	DPE.TL = GDc.DE;
	DPE.PicRes = GetGRBPicRes();
	DPE.MosaicOn = 1;
	DrawBegin(D_PUMPKIN_00 + koma | DTP, i->X, i->Y);
	DrawZoom(3.0);
	DrawEnd();
	DPE_Reset();

	AddEnemyAtari(CreateEnemyAtari(i, i->X, i->Y + 4.0, 45.0));

	return IsOutOfField(i->X, i->Y);
}
static void Dead_BigJackOLantern(Enemy_t *i, BigJackOLantern_t *e)
{
	CommonEnemyDeadProc(i);
}
Enemy_t *Make_BigJackOLantern(autoList<double> *args, EnemyCommonData_t *ecd)
{
	return CreateEnemy(
		EachFrame_BigJackOLantern,
		Dead_BigJackOLantern,
		Release_BigJackOLantern,
		Create_BigJackOLantern(args),
		ecd
		);
}
