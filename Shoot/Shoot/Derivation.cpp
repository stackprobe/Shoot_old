#include "all.h"

static autoList<DerInfo_t *> *DerList;

static void AddDer(int parentPicId, int x, int y, int w, int h)
{
	DerInfo_t *i = nb(DerInfo_t);

	i->ParentPicId = parentPicId;
	i->X = x;
	i->Y = y;
	i->W = w;
	i->H = h;

	DerList->AddElement(i);
}
static void AddAnimation(int parentPicId, int x, int y, int w, int h, int xNum, int yNum, int xStep = -1, int yStep = -1)
{
	if(xStep == -1) xStep = w;
	if(yStep == -1) yStep = h;

	for(int yc = 0; yc < yNum; yc++)
	for(int xc = 0; xc < xNum; xc++)
	{
		AddDer(parentPicId, x + xc * xStep, y + yc * yStep, w, h);
	}
}
static void AddAnimation_XY(int parentPicId, int x, int y, int w, int h, int xNum, int yNum, int xStep = -1, int yStep = -1)
{
	if(xStep == -1) xStep = w;
	if(yStep == -1) yStep = h;

	for(int xc = 0; xc < xNum; xc++)
	for(int yc = 0; yc < yNum; yc++)
	{
		AddDer(parentPicId, x + xc * xStep, y + yc * yStep, w, h);
	}
}
static void CreateDerList(void)
{
	DerList = new autoList<DerInfo_t *>();

	AddAnimation(P_DUMMY, 0, 0, 25, 25, 2, 2);

	// app >

	// -- P1 --

	/*
		ゴミ対策 ... ゴミが入るので、周囲1dot狭める。
	*/

	AddAnimation(P_KOAKUMA_P1, 0, 0, 32, 48, 4, 3); // D_KOAKUMA_00
	AddAnimation(P_KOAKUMA_P1, 96, 48, 32, 32, 1, 4); // D_BLAST_00
	AddAnimation(P_KOAKUMA_P1, 0, 144, 24, 24, 3, 1); // D_BOOK_00
	AddDer(P_KOAKUMA_P1, 72, 144, 8, 8); // D_ATARIPOINT
	AddDer(P_KOAKUMA_P1, 80, 144, 16, 40); // D_SHOT
	AddDer(P_KOAKUMA_P1, 64, 184, 48, 32); // D_WAVESHOT
	AddDer(P_KOAKUMA_P1, 64, 216, 40, 40); // D_BOOKBACK
	AddDer(P_KOAKUMA_P1, 0 + 1, 168 + 1, 64 - 2, 64 - 2); // D_SLOWBACK, ゴミ対策
	AddDer(P_KOAKUMA_P1, 0, 232, 24, 24); // D_ITEM_HEART
	AddDer(P_KOAKUMA_P1, 24, 232, 24, 24); // D_ITEM_HEART
	AddAnimation(P_KOAKUMA_P1, 128, 0, 64, 48, 1, 3); // D_LASERBLAST_00
	AddDer(P_KOAKUMA_P1, 160, 144, 32, 56); // D_LASER
	AddAnimation(P_KOAKUMA_P1, 192, 0, 48, 72, 1, 3); // D_LASERFIRE_00

	// -- P3 --

	AddDer(P_KOAKUMA_P3, 0 + 1, 0 + 1, 208 - 2, 208 - 2); // D_DECOCIRCLE, ゴミ対策
	AddDer(P_KOAKUMA_P3, 0, 208, 168, 32); // D_LEVELUP
	AddDer(P_KOAKUMA_P3, 208 + 1, 0 + 1, 32 - 2, 24 - 2); // D_ITEM_CANDY, ゴミ対策
	AddDer(P_KOAKUMA_P3, 240, 0, 24, 24); // D_ITEM_BOMB
	AddAnimation(P_KOAKUMA_P3, 208, 24, 72, 128 / BARAN_DIV, 1, BARAN_DIV); // D_KOAKUMA_00
	AddDer(P_KOAKUMA_P3, 208, 152, 48, 104); // D_GAUGE
	AddDer(P_KOAKUMA_P3, 256, 200, 16, 1); // D_GAUGEBAR

	// --

	AddAnimation(P_ENEMYDIE, 0, 0, 192, 192, 5, 2); // D_ENEMYDIE_00
	AddAnimation(P_ENEMYSHOTDIE, 0, 0, 60, 60, 10, 1); // D_ENEMYSHOTDIE_00
	AddAnimation(P_PLAYERDIE, 0, 0, 240, 240, 10, 1); // D_PLAYERDIE_00
	AddAnimation(P_PUMPKIN, 0, 0, 32, 32, 1, 2); // D_PUMPKIN_00

	// D_TAMA_00
	{
		int y = 0;
		AddAnimation(P_TAMA, 0, y, 10, 10, TAMA_COLOR_NUM, 1); y += 10; // TK_SMALL
		AddAnimation(P_TAMA, 0, y, 24, 24, TAMA_COLOR_NUM, 1); y += 24; // TK_NORMAL
		AddAnimation(P_TAMA, 0, y, 24, 24, TAMA_COLOR_NUM, 1); y += 24; // TK_DOUBLE
		AddAnimation(P_TAMA, 0, y, 30, 30, TAMA_COLOR_NUM, 1); y += 30; // TK_BIG
		AddAnimation_XY(P_TAMA, 0, y, 64, 64, TAMA_COLOR_NUM / 2, 2); y += 128; // TK_LARGE

		y = 477;
		AddAnimation(P_TAMA, 0, y, 21, 30, TAMA_COLOR_NUM, 1); y += 30; // TK_KNIFE
		AddAnimation(P_TAMA, 0, y, 29, 29, TAMA_COLOR_NUM, 1); y += 30; // TK_ECLIPSE
		AddAnimation(P_TAMA, 0, y, 29, 29, TAMA_COLOR_NUM, 1); y += 30; // TK_ECLIPSE_DOUBLE
	}

	AddAnimation(P_DIGITS_W,   0, 0, 16, 32, 13, 1); // D_DIGITS_W_00
	AddAnimation(P_DIGITS_DDY, 0, 0, 16, 32, 13, 1); // D_DIGITS_DDY_00
	AddAnimation(P_DIGITS_DY,  0, 0, 16, 32, 13, 1); // D_DIGITS_DY_00
	AddAnimation(P_DIGITS_Y,   0, 0, 16, 32, 13, 1); // D_DIGITS_Y_00

	AddAnimation(P_FAIRYETC, 0, 64, 32, 32, 8, 8); // D_FAIRY_00
	AddAnimation(P_FAIRYETC, 256, 0, 64, 64, 4, 4); // D_BIGFAIRY_00
	AddAnimation(P_FAIRYETC, 0, 320, 64, 64, 4, 3); // D_ONIBI_00

	AddAnimation(P_MAHOJIN_HAJIKE, 0, 0, 240, 240, 14, 1); // D_MAHOJIN_HAJIKE_00

	// < app

	errorCase(DerList->GetCount() != D_MAX);
}
static autoList<DerInfo_t *> *GetDerList(void)
{
	if(!DerList)
		CreateDerList();

	return DerList;
}

static int LoadDer(PicInfo_t *parent, int x, int y, int w, int h)
{
	int der_h;

	// check rect {
	errorCase(x < 0 || IMAX < x);
	errorCase(y < 0 || IMAX < y);
	errorCase(w < 1 || IMAX - x < w);
	errorCase(h < 1 || IMAX - y < h);
	// }

	if(
		parent->W < x + w ||
		parent->H < y + h
		)
		// ? 範囲外
	{
		m_range(w, 1, 50);
		m_range(h, 1, 50);

		der_h = DerivationGraph(0, 0, w, h, GetPicRes()->GetHandle(P_DUMMY)->Handle); // ダミー画像
	}
	else
		der_h = DerivationGraph(x, y, w, h, parent->Handle);

	errorCase(der_h == -1); // ? 失敗
	return der_h;
}
static void UnloadDer(int h)
{
	if(h == -1) // ? 未オープン
		return;

	errorCase(DeleteGraph(h)); // ? 失敗
}

int Der(resCluster<PicInfo_t *> *resclu, int derId)
{
	errorCase(derId < 0 || D_MAX <= derId);

	int h = resclu->GetDerHandleList()->RefElement(derId, -1);

	if(h == -1)
	{
		DerInfo_t *i = GetDerList()->GetElement(derId);

		h = LoadDer(
			resclu->GetHandle(i->ParentPicId),
			i->X,
			i->Y,
			i->W,
			i->H
			);

		resclu->GetDerHandleList()->PutElement(derId, h, -1);
	}
	return h;
}
int Der_W(int derId)
{
	return GetDerList()->GetElement(derId)->W;
}
int Der_H(int derId)
{
	return GetDerList()->GetElement(derId)->H;
}

void UnloadAllDer(resCluster<PicInfo_t *> *resclu)
{
	for(int derId = 0; derId < resclu->GetDerHandleList()->GetCount(); derId++)
	{
		UnloadDer(resclu->GetDerHandleList()->GetElement(derId));
	}
	resclu->GetDerHandleList()->Clear();
}
