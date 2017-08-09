#include "all.h"

#define SHOT_A 0.3

PlayerShot_t *CreatePlayerShot(int kind, double x, double y, double r, double ra, int level)
{
	errorCase(kind < 0 || PSK_MAX <= kind);
	// x
	// y
	// r
	// ra
	errorCase(level < 0 || PLAYERLEVEL_MAX < level);

	PlayerShot_t *i = nb(PlayerShot_t);

	i->Kind = kind;
	i->Level = level;
	i->X = x;
	i->Y = y;
	i->R = r;
	i->RAdd = ra;

	i->Frame = -1; // -1 == uninited

	return i;
}
void ReleasePlayerShot(PlayerShot_t *i)
{
	memFree(i);
}

// <-- cdtor

// <-- accessor

#define BOMBCIRCLE_NUM 3

typedef struct BombCircleInfo_st
{
	double ATarget;
	double A;
	double ZTarget;
	double Z;
	double R;
	double RAdd;
}
BombCircleInfo_t;

BombCircleInfo_t BombCircleInfos[BOMBCIRCLE_NUM];

/*
	ˆ—
	•`‰æ -> GDc.DPS
	“–‚½‚è”»’è‚Ì’Ç‰Á -> AddPlayerShotAtari()
*/
static int PlayerShotEachFrame(PlayerShot_t *i) // ret: ? dead
{
	i->Frame++; // 0`

	switch(i->Kind)
	{
	case PSK_NORMAL:
		{
			/*
			ignore:
				i->Level
				i->RAdd
			*/

			double ax = 0.0;
			double ay = -20.0;

			rotatePos(i->R, ax, ay);

			i->X += ax;
			i->Y += ay;

			if(IsOutOfField(i->X, i->Y))
				return 1;

//			i->R += i->RAdd; // “]i‚µ‚È‚¢B

			DPE.TL = GDc.DPS;
			DPE_SetAlpha(SHOT_A);
			DrawBegin(D_SHOT | DTP, i->X, i->Y);
			DrawRotate(i->R);
			DrawEnd();
			DPE_Reset();

			AddPlayerShotAtari(CreatePlayerShotAtari(i, i->X, i->Y, 12.0));
		}
		break;

	case PSK_STRONG:
		{
			/*
			ignore:
				i->Level
				i->RAdd
			*/

			double ax = 0.0;
			double ay = -20.0;

			rotatePos(i->R, ax, ay);

			i->X += ax;
			i->Y += ay;

			if(IsOutOfField(i->X, i->Y))
				return 1;

//			i->R += i->RAdd; // “]i‚µ‚È‚¢B

			DPE.TL = GDc.DPS;
			DPE_SetAlpha(SHOT_A);
			DrawBegin(D_SHOT | DTP, i->X, i->Y);
			DrawZoom(1.2);
			DrawRotate(i->R);
			DrawEnd();
			DPE_Reset();

			AddPlayerShotAtari(CreatePlayerShotAtari(i, i->X, i->Y, 14.4));
		}
		break;

	case PSK_WAVE:
		{
			/*
			ignore:
				i->Level
			*/

			double ax = 0.0;
			double ay = -15.0;

			rotatePos(i->R, ax, ay);

			i->X += ax;
			i->Y += ay;

			if(IsOutOfField(i->X, i->Y))
				return 1;

			i->R += i->RAdd;

			DPE.TL = GDc.DPS;
			DPE_SetAlpha(SHOT_A);
			DrawBegin(D_WAVESHOT | DTP, i->X, i->Y);
			DrawRotate(i->R);
			DrawEnd();
			DPE_Reset();

			AddPlayerShotAtari(CreatePlayerShotAtari(i, i->X, i->Y, 24.0));
		}
		break;

	case PSK_LASER:
		{
			/*
			ignore:
				i->R
				i->RAdd
			*/

			double ay = -18.0;

			i->Y += ay;

			if(IsOutOfField(i->X, i->Y))
				return 1;

			DPE.TL = GDc.DPS;
			DPE_SetGraphicSize(GDc.GSz_Laser);
			DPE_SetAlpha(SHOT_A);
			DrawBegin(GDc.GH_Laser, i->X, i->Y);
			DrawZoom(1.0 + (0.5 * i->Level) / PLAYERLEVEL_MAX);
			DrawEnd();
			DPE_Reset();

			AddPlayerShotAtari(CreatePlayerShotAtari(
				i,
				i->X,
				i->Y,
				32.0 + (16.0 * i->Level) / PLAYERLEVEL_MAX
				));
		}
		break;

	case PSK_BOMB:
		{
			int frm = i->Frame;
			BombCircleInfo_t *bcis = BombCircleInfos;
			double dc_r = Pic_W(D_DECOCIRCLE | DTP) / 2.0;
			double dc_z = BOMB_R / dc_r;

			if(!frm)
			{
				memset(bcis, 0x00, sizeof(BombCircleInfos));

				int c = 0;
				bcis[c].ATarget = 0.75;
				bcis[c].ZTarget = dc_z;
				bcis[c].Z = 0.1;
				bcis[c].RAdd = 0.05;
				c++;

				bcis[c].ATarget = 0.25;
				bcis[c].ZTarget = dc_z * 0.75;
				bcis[c].Z = dc_z * 2.0;
				bcis[c].RAdd = 0.01;
				c++;

				bcis[c].ATarget = 0.5;
				bcis[c].ZTarget = dc_z * 0.5;
				bcis[c].Z = 0.1;
				bcis[c].RAdd = -0.02;
				c++;

				errorCase(c != BOMBCIRCLE_NUM);
			}
			else if(frm == PLAYER_BOMBINGFRAME_MAX)
			{
				int c = 0;
				bcis[c].ATarget = 0.0;
				c++;

				bcis[c].ATarget = 0.0;
				c++;

				bcis[c].ATarget = 0.0;
				c++;

				errorCase(c != BOMBCIRCLE_NUM);
			}
			else if(frm == PLAYER_BOMBINGFRAME_MAX + 60)
			{
				return 1;
			}

			i->Y -= 0.0 + frm / 60.0;

			for(int c = 0; c < BOMBCIRCLE_NUM; c++)
			{
				m_approach(bcis[c].A, bcis[c].ATarget, 0.9);
				m_approach(bcis[c].Z, bcis[c].ZTarget, 0.9);
				bcis[c].R += bcis[c].RAdd;

				DPE.TL = GDc.DPS;
				DPE_SetAlpha(bcis[c].A);
				DrawBegin(D_DECOCIRCLE | DTP, i->X, i->Y);
				DrawZoom(bcis[c].Z);
				DrawRotate(bcis[c].R);
				DrawEnd();
				DPE_Reset();
			}

			AddPlayerShotAtari(CreatePlayerShotAtari(
				i,
				i->X,
				i->Y,
				BOMB_R
				));
		}
		break;

	default:
		error();
	}
	return 0;
}
void AllPlayerShotEachFrame(void)
{
	for(int index = 0; index < GDc.PlayerShotList->GetCount(); index++)
	{
		PlayerShot_t *i = GDc.PlayerShotList->GetElement(index);

		if(i->DeadFlag || PlayerShotEachFrame(i)) // ? dead
		{
			ReleasePlayerShot(i);
			GDc.PlayerShotList->SetElement(index, NULL);
		}
	}
	GDc.PlayerShotList->MultiDiscard(isPointNull);
}
void AddPlayerShot(PlayerShot_t *i)
{
	GDc.PlayerShotList->AddElement(i);
}

static int DamageTable[PSK_MAX][PLAYERLEVEL_MAX + 1] =
{
	/*
		Lv0: N = 2        + 1 = 3
		Lv1: WNW = 4      + 2 = 6
		Lv2: WNNW = 5     + 3 = 7
		Lv3: WNSNW = 9    + 4 = 13
		Lv4: WNNNNW = 10  + 5 = 15
		Lv5: WNSSSNW = 15 + 6 = 21
	*/
	{ 2, -1, -1, -1, -1, -1 }, // PSK_NORMAL
	{ 3, -1, -1, -1, -1, -1 }, // PSK_STRONG
	{ 1, -1, -1, -1, -1, -1 }, // PSK_WAVE
	{ 3,  6,  7, 13, 15, 21 }, // PSK_LASER
	{ 1, -1, -1, -1, -1, -1 }, // PSK_BOMB
};

int GetDamage(PlayerShot_t *i)
{
	errorCase(i->Kind < 0 || PSK_MAX <= i->Kind);
	errorCase(i->Level < 0 || PLAYERLEVEL_MAX < i->Level);

	int damage = DamageTable[i->Kind][i->Level];

	errorCase(damage < 1 || IMAX < damage); // 2bs

	return damage;
}
