#include "all.h"

// ---- I01 ----

static I01_t *Create_I01(autoList<double> *args)
{
	I01_t *e = nb_(I01_t);
	int rIndex = 0;

	e->Kind = nextArg_i(args, rIndex, 0, ITEM_KIND_NUM - 1);

	return e;
}
static void Release_I01(Enemy_t *i, I01_t *e)
{
	memFree(e);
}
static int EachFrame_I01(Enemy_t *i, I01_t *e)
{
	if(!i->Frame)
	{
		e->YAdd = -4.0;
		e->RotAdd = eRnd() * 0.01;
	}

	if(!e->VacuumFlag)
	{
		if(GDc.CPI.Slow && m_hypot(i->X - GDc.Player.X, i->Y - GDc.Player.Y) < 100.0) // ? ’á‘¬’†‚ÉÚ‹ß‚µ‚½B
		{
			e->VacuumFlag = 1;
		}
		else if(GDc.Player.Y < ITEM_GET_BORDER_Y && i->Y < ITEM_GET_MAX_Y)
		{
			e->VacuumFlag = 2;
		}
	}
	if(!e->VacuumFlag)
	{
		i->Y += e->YAdd;
		e->YAdd += 0.1;

		if(i->X < 0)
			i->X += 1.0;
		else if(FIELD_W < i->X)
			i->X -= 1.0;
	}
	else
	{
		double speed;

		if(e->VacuumFlag == 2)
			speed = 12.0;
		else
			speed = 6.0;

		double targetX;
		double targetY;

		if(GDc.Player.BornFrame)
		{
			targetX = GDc.Player.FollowX;
			targetY = GDc.Player.FollowY;
		}
		else
		{
			targetX = GDc.Player.X;
			targetY = GDc.Player.Y;
		}
		double xa;
		double ya;

		MakeXYSpeed(i->X, i->Y, targetX, targetY, speed, xa, ya);

		i->X += xa;
		i->Y += ya;
	}
	e->Rot += e->RotAdd;

	if(0.0 < e->YAdd)
		e->YAdd *= 0.97;

	int picId;

	switch(e->Kind)
	{
	case IK_HEART: picId = D_ITEM_HEART | DTP; break;
	case IK_STAR:  picId = D_ITEM_STAR  | DTP; break;
	case IK_CANDY: picId = D_ITEM_CANDY | DTP; break;
	case IK_BOMB:  picId = D_ITEM_BOMB  | DTP; break;

	default:
		error();
	}

	DPE.TL = GDc.DI;
	DrawBegin(picId, i->X, i->Y);
	DrawRotate(e->Rot);
	DrawEnd();
	DPE_Reset();

	AddEnemyAtari(CreateEnemyAtari(i, i->X, i->Y, 16.0));

	return IsOutOfField(i->X, i->Y);
}
static void Dead_I01(Enemy_t *i, I01_t *e)
{
	switch(i->Kind)
	{
	case IK_STAR:
		GDc.Score += 100;
		break;

	case IK_CANDY:
		GDc.Player.Power++;
		break;

	case IK_HEART:
		GDc.Zanki++;
		break;

	case IK_BOMB:
		GDc.ZanBomb++;
		break;

	default:
		error();
	}
}
Enemy_t *Make_I01(autoList<double> *args, EnemyCommonData_t *ecd)
{
	return CreateEnemy(
		EachFrame_I01,
		Dead_I01,
		Release_I01,
		Create_I01(args),
		ecd
		);
}
