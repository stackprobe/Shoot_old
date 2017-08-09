/*
フレーム毎のＮ対Ｍの関係
	自機 1 : * 自機当たり判定
	自弾 1 : 1 自弾当たり判定
	敵　 1 : 1 敵当たり判定
*/

#include "all.h"

// ---- 敵 x 自弾 ----

static int IsCrashed(EnemyAtari_t *ea, PlayerShotAtari_t *psa)
{
	/*
		psa != ボム -> ea != 無敵
		psa == ボム -> ea != 無敵 || ea == 無敵
	*/

	switch(ea->Kind)
	{
	case EAK_CIRCLE:
		{
			if(!isFar(
				psa->X,
				psa->Y,
				ea->u.Circle.X,
				ea->u.Circle.Y,
				psa->R + ea->u.Circle.R
				))
			{
				return 1;
			}
		}
		break;

	case EAK_RECT:
		{
			if(isCrashedRectCircle(
				ea->u.Rect.L,
				ea->u.Rect.T,
				ea->u.Rect.W,
				ea->u.Rect.H,
				psa->X,
				psa->Y,
				psa->R
				))
			{
				return 1;
			}
		}
		break;

	default:
		error();
	}
	return 0;
}
static void Crashed(EnemyAtari_t *ea, PlayerShotAtari_t *psa)
{
	/*
		psa != ボム -> ea != 無敵
		psa == ボム -> ea != 無敵 || ea == 無敵
	*/

	PlayerShot_t *ps = psa->Owner;
	Enemy_t *e = ea->Owner;

	if(e->Kind == EK_ITEM)
		return;

	if(e->DeadFlag) // ? 既に敵は死んでいる。-> 何もしない。
		return;

	/*
		エフェクトを複数出さない!!
	*/
	if(!ps->DeadFlag && psa->Owner->Kind != PSK_BOMB)
	{
		double z = psa->R / 8.0;

		CEE.EndPicId = D_BLAST_00 + 3 | DTP;
		CEE.PicIdFrmPerInc = 3;
		CEE.SlideX = 8.0;
		CEE.SlideY = -8.0;
		AddCommonEffect(
			GDc.EP,
			0,
			D_BLAST_00 | DTP,
			psa->X,
			psa->Y,
			0.0,
			z,
			0.4,
			0.0,
			-5.0
			);
		CEE_Reset();

		ps->DeadFlag = 1; // ショットは当たったら消す。
	}

	int damage = GetDamage(ps);

	e->HP -= damage;

	if(e->HP <= 0) // ? dead
	{
		e->DeadEventFunc(e, e->ExtraData);
		e->DeadFlag = 1;

		/*
			死亡エフェクトは各敵のDeadEventFuncへ移動した。
		*/
	}
}

// ---- 敵 x 自機 ----

static int IsCrashed(EnemyAtari_t *ea, PlayerAtari_t *pa) // ret: 1 == crashed, 2 == grazed
{
	if(ea->Owner->DeadFlag) // ? 既に敵は死んでいる。-> 何もしない。
		return 0;

	const double GRAZE_R = 10.0;

	switch(ea->Kind)
	{
	case EAK_CIRCLE:
		{
			if(!isFar(
				pa->X,
				pa->Y,
				ea->u.Circle.X,
				ea->u.Circle.Y,
				ea->u.Circle.R
				))
			{
				return 1; // crashed
			}

			if(!isFar(
				pa->X,
				pa->Y,
				ea->u.Circle.X,
				ea->u.Circle.Y,
				ea->u.Circle.R + GRAZE_R
				))
			{
				return 2; // grazed
			}
		}
		break;

	case EAK_RECT:
		{
			double l = ea->u.Rect.L;
			double t = ea->u.Rect.T;
			double w = ea->u.Rect.W;
			double h = ea->u.Rect.H;

			if(
				m_isRange(pa->X, l, l + w) &&
				m_isRange(pa->Y, t, t + h)
				)
			{
				return 1; // crashed
			}

			if(
				m_isRange(pa->X, l - GRAZE_R, l + w + GRAZE_R) &&
				m_isRange(pa->Y, t - GRAZE_R, t + h + GRAZE_R)
				)
			{
				return 2; // grazed
			}
		}
		break;

	default:
		error();
	}
	return 0;
}
static void Crashed(EnemyAtari_t *ea, PlayerAtari_t *pa, int grazedFlag)
{
	Enemy_t *e = ea->Owner;

	if(e->Kind == EK_ITEM) // ? アイテム
	{
		if(!grazedFlag)
		{
			e->DeadEventFunc(e, e->ExtraData);
			e->DeadFlag = 1;
		}
		return;
	}

	/*
		登場中・死亡中・ボム中は何もしない。
	*/
	if(GDc.Player.BornFrame || GDc.Player.DeadFrame || GDc.Player.BombingFrame)
	{
		return;
	}

	if(grazedFlag)
		GDc.FS.Grazed = 1;
	else
		GDc.Player.DeadFrame = 1;
}

// ----

void AtariHantei(void)
{
	for(int eaIndex = 0; eaIndex < GDc.EnemyAtariList->GetCount(); eaIndex++) // 敵 x 自弾(非ボム)
	{
		EnemyAtari_t *ea = GDc.EnemyAtariList->GetElement(eaIndex);

		if(IsTrans(ea)) // ? 無敵 -> 当たらない。
			continue;

		for(int psaIndex = 0; psaIndex < GDc.PlayerShotAtariList->GetCount(); psaIndex++)
		{
			PlayerShotAtari_t *psa = GDc.PlayerShotAtariList->GetElement(psaIndex);

			if(psa->Owner->Kind == PSK_BOMB) // ボムは除外
				continue;

			if(IsCrashed(ea, psa))
			{
				Crashed(ea, psa);
			}
		}
	}
	for(int psaIndex = 0; psaIndex < GDc.PlayerShotAtariList->GetCount(); psaIndex++) // 自弾(ボムのみ) x 敵
	{
		PlayerShotAtari_t *psa = GDc.PlayerShotAtariList->GetElement(psaIndex);

		if(psa->Owner->Kind != PSK_BOMB) // ボム以外は除外
			continue;

		for(int eaIndex = 0; eaIndex < GDc.EnemyAtariList->GetCount(); eaIndex++)
		{
			EnemyAtari_t *ea = GDc.EnemyAtariList->GetElement(eaIndex);

			if(IsCrashed(ea, psa))
			{
				Crashed(ea, psa);
			}
		}
	}
	for(int eaIndex = 0; eaIndex < GDc.EnemyAtariList->GetCount(); eaIndex++) // 敵 x 自機
	{
		EnemyAtari_t *ea = GDc.EnemyAtariList->GetElement(eaIndex);

		for(int paIndex = 0; paIndex < GDc.PlayerAtariList->GetCount(); paIndex++)
		{
			PlayerAtari_t *pa = GDc.PlayerAtariList->GetElement(paIndex);

			switch(IsCrashed(ea, pa))
			{
			case 0:
				break;

			case 1: // crashed
				Crashed(ea, pa, 0);
				break;

			case 2: // grazed
				Crashed(ea, pa, 1);
				break;

			default:
				error();
			}
		}
	}
}

void AddPlayerAtari(PlayerAtari_t *i)
{
	/*
		プレイヤーが画面外に出ることはない。
		むしろ、際で誤差って無敵になられると困る。
	*/
#if 0
	if(IsOutOfField(i)) // ? 画面外
	{
		ReleasePlayerAtari(i);
		return;
	}
#endif

	GDc.PlayerAtariList->AddElement(i);
}
void AddPlayerShotAtari(PlayerShotAtari_t *i) // i: bind
{
	if(IsOutOfField(i)) // ? 画面外
	{
		ReleasePlayerShotAtari(i);
		return;
	}

	GDc.PlayerShotAtariList->AddElement(i);
}
void AddEnemyAtari(EnemyAtari_t *i) // i: bind
{
	if(IsOutOfField(i)) // ? 画面外
	{
		ReleaseEnemyAtari(i);
		return;
	}

	GDc.EnemyAtariList->AddElement(i);
}
