#include "all.h"

oneObject(autoList<double>, new autoList<double>(), GetEDL); // Empty Double List

int IsOutOfField(double x, double y, double margin)
{
	return
		x < -margin || (double)FIELD_W + margin < x ||
		y < -margin || (double)FIELD_H + margin < y;
}
int IsOutOfField_LTWH(double l, double t, double w, double h)
{
	return
		l + w < 0.0 || (double)FIELD_W < l ||
		t + h < 0.0 || (double)FIELD_H < t;
}
int IsOutOfField(PlayerAtari_t *i)
{
	return IsOutOfField(i->X, i->Y, 0.0);
}
int IsOutOfField(PlayerShotAtari_t *i)
{
	return IsOutOfField(i->X, i->Y, i->R);
}
int IsOutOfField(EnemyAtari_t *i)
{
	switch(i->Kind)
	{
	case EAK_CIRCLE:
		return IsOutOfField(i->u.Circle.X, i->u.Circle.Y, i->u.Circle.R);

	case EAK_RECT:
		return IsOutOfField_LTWH(i->u.Rect.L, i->u.Rect.T, i->u.Rect.W, i->u.Rect.H);

	default:
		error();
	}
}

int GetTamaPicId(int kind, int color)
{
	errorCase(kind < 0 || TAMA_KIND_NUM <= kind);
	errorCase(color < 0 || TAMA_COLOR_NUM <= color);

	return D_TAMA_00 + kind * TAMA_COLOR_NUM + color | DTP;
}
int GetFairyPicId(int color, int mode, int koma)
{
	errorCase(!m_isRange(color, 0, FAIRY_COLOR_NUM - 1));
	errorCase(!m_isRange(mode, -1, 1)); // -1, 0, 1: 左移動, 左右移動ナシ, 右移動
	errorCase(!m_isRange(koma, 0, 3));
	errorCase(!mode && koma == 3); // mode == 0 のとき koma == 3 は無い

	int komaTop;

	if(mode == -1)
		komaTop = 8;
	else if(mode == 1)
		komaTop = 12;
	else
		komaTop = 0;

	return D_FAIRY_00 + color * 16 + komaTop + koma | DTP;
}
int GetBigFairyPicId(int color, int mode, int koma)
{
	errorCase(!m_isRange(color, 0, BIGFAIRY_COLOR_NUM - 1));
	errorCase(!m_isRange(mode, -1, 1)); // -1, 0, 1: 左移動, 左右移動ナシ, 右移動
	errorCase(!m_isRange(koma, 0, 2));
	errorCase(mode && koma == 2); // mode != 0 のとき koma == 2 は無い

	int relKoma;

	if(mode == -1)
		relKoma = 7 - koma;
	else if(mode == 1)
		relKoma = 4 + koma;
	else
		relKoma = 0;

	return D_BIGFAIRY_00 + color * 8 + relKoma | DTP;
}
int GetOnibiPicId(int color, int koma)
{
	errorCase(!m_isRange(color, 0, ONIBI_COLOR_NUM - 1));
	errorCase(!m_isRange(koma, 0, 3));

	return D_ONIBI_00 + color * 4 + koma | DTP;
}

int MakeMirrorGrphHdl(int src_si_h, int l, int t, int w, int h, i2D_t *p_size)
{
	int si_h = Pic_CreateSoftImage(w * 2, h);

	for(int x = 0; x < w; x++)
	for(int y = 0; y < h; y++)
	{
		Pic_GetSIPixel(src_si_h, l + x, t + y);
		Pic_SetSIPixel(si_h, x, y);
		Pic_SetSIPixel(si_h, w * 2 - 1 - x, y);
	}
	int gh = Pic_SoftImage2GraphicHandle(si_h);

	p_size->X = w * 2;
	p_size->Y = h;

	return gh;
}
