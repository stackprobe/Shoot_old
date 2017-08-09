#include "all.h"

// ---- ES01 ----

static ES01_t *Create_ES01(autoList<double> *args)
{
	ES01_t *e = nb(ES01_t);
	int rIndex = 0;

	e->Kind = nextArg_i(args, rIndex, 0, TAMA_KIND_NUM - 1);
	e->Color = nextArg_i(args, rIndex, 0, TAMA_COLOR_NUM - 1);
	e->Speed = nextArg_d(args, rIndex, 0.1, 100.0);
	e->Angle = nextArg_d(args, rIndex, -PI, PI); // -180‹ ` 180‹

	return e;
}
static void Release_ES01(Enemy_t *i, ES01_t *e)
{
	memFree(e);
}
static int EachFrame_ES01(Enemy_t *i, ES01_t *e)
{
	if(!i->Frame) // init
	{
		e->PicId = GetTamaPicId(e->Kind, e->Color);
		
		// Set R
		{
			double r;

			switch(e->Kind)
			{
			case TK_NORMAL: r = 8.0; break;
			case TK_BIG: r = 16.0; break;

			default:
				error();
			}
			e->R = r;
		}

		MakeXYSpeed(i->X, i->Y, GDc.Player.X, GDc.Player.Y, e->Speed, e->XAdd, e->YAdd);

		rotatePos(e->Angle, e->XAdd, e->YAdd);
	}

	i->X += e->XAdd;
	i->Y += e->YAdd;

	DPE.TL = GDc.DES;
	DrawCenter(e->PicId, i->X, i->Y);
	DPE_Reset();

	AddEnemyAtari(CreateEnemyAtari(i, i->X, i->Y, e->R));

	{
		const double R_MARGIN = 5.0;
		return IsOutOfField(i->X, i->Y, e->R + R_MARGIN);
	}
}
static void Dead_ES01(Enemy_t *i, ES01_t *e)
{
	CommonEnemyDeadProc(i);
}
Enemy_t *Make_ES01(autoList<double> *args, EnemyCommonData_t *ecd)
{
	return CreateEnemy(
		EachFrame_ES01,
		Dead_ES01,
		Release_ES01,
		Create_ES01(args),
		ecd
		);
}
Enemy_t *Make_ES01(int kind, int color, double speed, double x, double y, double angle)
{
	static autoList<double> *args;

	if(!args)
		args = new autoList<double>();

	args->Clear();
	args->AddElement((double)kind);
	args->AddElement((double)color);
	args->AddElement(speed);
	args->AddElement(angle);

	return Make_ES01(args, GetECD(EK_TAMA, 0, 0, x, y, 0));
}
