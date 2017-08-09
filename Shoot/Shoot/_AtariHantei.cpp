/*
�t���[�����̂m�΂l�̊֌W
	���@ 1 : * ���@�����蔻��
	���e 1 : 1 ���e�����蔻��
	�G�@ 1 : 1 �G�����蔻��
*/

#include "all.h"

// ---- �G x ���e ----

static int IsCrashed(EnemyAtari_t *ea, PlayerShotAtari_t *psa)
{
	/*
		psa != �{�� -> ea != ���G
		psa == �{�� -> ea != ���G || ea == ���G
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
		psa != �{�� -> ea != ���G
		psa == �{�� -> ea != ���G || ea == ���G
	*/

	PlayerShot_t *ps = psa->Owner;
	Enemy_t *e = ea->Owner;

	if(e->Kind == EK_ITEM)
		return;

	if(e->DeadFlag) // ? ���ɓG�͎���ł���B-> �������Ȃ��B
		return;

	/*
		�G�t�F�N�g�𕡐��o���Ȃ�!!
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

		ps->DeadFlag = 1; // �V���b�g�͓�������������B
	}

	int damage = GetDamage(ps);

	e->HP -= damage;

	if(e->HP <= 0) // ? dead
	{
		e->DeadEventFunc(e, e->ExtraData);
		e->DeadFlag = 1;

		/*
			���S�G�t�F�N�g�͊e�G��DeadEventFunc�ֈړ������B
		*/
	}
}

// ---- �G x ���@ ----

static int IsCrashed(EnemyAtari_t *ea, PlayerAtari_t *pa) // ret: 1 == crashed, 2 == grazed
{
	if(ea->Owner->DeadFlag) // ? ���ɓG�͎���ł���B-> �������Ȃ��B
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

	if(e->Kind == EK_ITEM) // ? �A�C�e��
	{
		if(!grazedFlag)
		{
			e->DeadEventFunc(e, e->ExtraData);
			e->DeadFlag = 1;
		}
		return;
	}

	/*
		�o�ꒆ�E���S���E�{�����͉������Ȃ��B
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
	for(int eaIndex = 0; eaIndex < GDc.EnemyAtariList->GetCount(); eaIndex++) // �G x ���e(��{��)
	{
		EnemyAtari_t *ea = GDc.EnemyAtariList->GetElement(eaIndex);

		if(IsTrans(ea)) // ? ���G -> ������Ȃ��B
			continue;

		for(int psaIndex = 0; psaIndex < GDc.PlayerShotAtariList->GetCount(); psaIndex++)
		{
			PlayerShotAtari_t *psa = GDc.PlayerShotAtariList->GetElement(psaIndex);

			if(psa->Owner->Kind == PSK_BOMB) // �{���͏��O
				continue;

			if(IsCrashed(ea, psa))
			{
				Crashed(ea, psa);
			}
		}
	}
	for(int psaIndex = 0; psaIndex < GDc.PlayerShotAtariList->GetCount(); psaIndex++) // ���e(�{���̂�) x �G
	{
		PlayerShotAtari_t *psa = GDc.PlayerShotAtariList->GetElement(psaIndex);

		if(psa->Owner->Kind != PSK_BOMB) // �{���ȊO�͏��O
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
	for(int eaIndex = 0; eaIndex < GDc.EnemyAtariList->GetCount(); eaIndex++) // �G x ���@
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
		�v���C���[����ʊO�ɏo�邱�Ƃ͂Ȃ��B
		�ނ���A�ۂŌ덷���Ė��G�ɂȂ���ƍ���B
	*/
#if 0
	if(IsOutOfField(i)) // ? ��ʊO
	{
		ReleasePlayerAtari(i);
		return;
	}
#endif

	GDc.PlayerAtariList->AddElement(i);
}
void AddPlayerShotAtari(PlayerShotAtari_t *i) // i: bind
{
	if(IsOutOfField(i)) // ? ��ʊO
	{
		ReleasePlayerShotAtari(i);
		return;
	}

	GDc.PlayerShotAtariList->AddElement(i);
}
void AddEnemyAtari(EnemyAtari_t *i) // i: bind
{
	if(IsOutOfField(i)) // ? ��ʊO
	{
		ReleaseEnemyAtari(i);
		return;
	}

	GDc.EnemyAtariList->AddElement(i);
}
