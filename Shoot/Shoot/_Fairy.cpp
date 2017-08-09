/*
	*EachFrameでやること
		描画
		AddEnemyAtari()
		return IsOutOfField()
*/

#include "all.h"

int FairyEachFrame(Enemy_t *i, int color)
{
	if(!i->Frame) // init
	{
		i->u.Fairy.LastX = i->X;
	}
	double xDiff = i->X - i->u.Fairy.LastX;
	i->u.Fairy.LastX = i->X;

	if(i->Frame % 7 == 0)
	{
		if(abs(xDiff) < MICRO) // ? 左右に動いてない。
		{
			m_countDown(i->u.Fairy.XMoveCount);
			m_range(i->u.Fairy.XMoveCount, -2, 2);
		}
		else if(xDiff < 0.0) // ? 左に動いてる。
		{
			i->u.Fairy.XMoveCount--;
			m_minim(i->u.Fairy.XMoveCount, 2);
		}
		else // ? 右に動いてる。
		{
			i->u.Fairy.XMoveCount++;
			m_maxim(i->u.Fairy.XMoveCount, -2);
		}
	}
	int mode = m_iSign(i->u.Fairy.XMoveCount);
	int koma;
	
	if(mode)
	{
		koma = abs(i->u.Fairy.XMoveCount) - 1;

		if(4 <= koma)
			koma = 2 + koma % 2;
	}
	else
		koma = (i->Frame / 7) % 3;

	if(!IsTrans(i))
		m_approach(i->u.Fairy.UntransRate, 1.0, 0.91);

	DPE.TL = GDc.DE;
	DPE_SetAlpha(i->u.Fairy.UntransRate * 0.5);
	DrawBegin(D_MAHOJIN_HAJIKE_00 + 5 | DTP, i->X, i->Y);
	DrawRotate(i->Frame / 20.0);
	DrawZoom(0.4);
	DrawEnd();
	DPE_Reset();

	DPE.TL = GDc.DE;
	DPE.PicRes = GetDeepestBlackToTransPicRes();
	DrawCenter(GetFairyPicId(color, mode, koma), i->X, i->Y);
	DPE_Reset();

	AddEnemyAtari(CreateEnemyAtari(i, i->X, i->Y, 13.0));

	return IsOutOfField(i->X, i->Y);
}
int BigFairyEachFrame(Enemy_t *i, int color)
{
	if(!i->Frame) // init
	{
		i->u.Fairy.LastX = i->X;
	}
	double xDiff = i->X - i->u.Fairy.LastX;
	i->u.Fairy.LastX = i->X;

	if(i->Frame % 7 == 0)
	{
		if(abs(xDiff) < MICRO) // ? 左右に動いてない。
		{
			m_countDown(i->u.Fairy.XMoveCount);
		}
		else if(xDiff < 0.0) // ? 左に動いてる。
		{
			i->u.Fairy.XMoveCount--;
		}
		else // ? 右に動いてる。
		{
			i->u.Fairy.XMoveCount++;
		}
		m_range(i->u.Fairy.XMoveCount, -2, 2);
	}
	int mode = m_iSign(i->u.Fairy.XMoveCount);
	int koma;
	
	if(mode)
		koma = abs(i->u.Fairy.XMoveCount) - 1;
	else
		koma = (i->Frame / 7) % 3;

	if(!IsTrans(i))
		m_approach(i->u.Fairy.UntransRate, 1.0, 0.92);

	DPE.TL = GDc.DE;
	DPE_SetAlpha(i->u.Fairy.UntransRate * 0.5);
	DrawBegin(D_MAHOJIN_HAJIKE_00 + 5 | DTP, i->X, i->Y);
	DrawRotate(i->Frame / 20.0);
	DrawZoom(0.4);
	DrawEnd();
	DPE_Reset();

	DPE.TL = GDc.DE;
	DPE.PicRes = GetDeepestBlackToTransPicRes();
	DrawCenter(GetBigFairyPicId(color, mode, koma), i->X, i->Y);
	DPE_Reset();

	AddEnemyAtari(CreateEnemyAtari(i, i->X, i->Y, 30.0));

	return IsOutOfField(i->X, i->Y);
}
int OnibiEachFrame(Enemy_t *i, int color)
{
	int koma = (i->Frame / 4) % 4;

	DPE.TL = GDc.DE;
	DPE.PicRes = GetDeepestBlackToTransPicRes();
	DrawBegin(GetOnibiPicId(color, koma), i->X, i->Y);
	DrawZoom(2.0);
	DrawEnd();
	DPE_Reset();

	AddEnemyAtari(CreateEnemyAtari(i, i->X, i->Y, 30.0));

	return IsOutOfField(i->X, i->Y);
}

int FairyEtcEachFrame(Enemy_t *i, int kind)
{
	errorCase(!m_isRange(kind, 0, FAIRYETC_KIND_NUM - 1));

	if(kind < FAIRY_COLOR_NUM)
		return FairyEachFrame(i, kind);

	kind -= FAIRY_COLOR_NUM;

	if(kind < BIGFAIRY_COLOR_NUM)
		return BigFairyEachFrame(i, kind);

	kind -= BIGFAIRY_COLOR_NUM;
	return OnibiEachFrame(i, kind);
}
