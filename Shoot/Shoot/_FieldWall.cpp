#include "all.h"

/*
	picRes: NULL == デフォルトを使用
*/
FieldWall_t *CreateFieldWall(
	int picId,
	resCluster<PicInfo_t *> *picRes,
	i2D_t speed,
	i2D_t origin,
	i2D_t tileSize,
	int life,
	double a_add,
	double a_max,
	double die_a_add
	)
{
	if(tileSize.X == -1 || tileSize.Y == -1)
	{
		SetPicRes(picRes);

		if(tileSize.X == -1) tileSize.X = Pic_W(picId);
		if(tileSize.Y == -1) tileSize.Y = Pic_H(picId);

		ResetPicRes();
	}

	// picId
	// picRes
	errorCase(!m_isRange(speed.X, -IMAX, IMAX));
	errorCase(!m_isRange(speed.Y, -IMAX, IMAX));
	errorCase(!m_isRange(origin.X, -IMAX, IMAX));
	errorCase(!m_isRange(origin.Y, -IMAX, IMAX));
	errorCase(!m_isRange(tileSize.X, 1, IMAX));
	errorCase(!m_isRange(tileSize.Y, 1, IMAX));
	errorCase(!m_isRange(life, 0, IMAX));
	m_range(a_add, 0.0, 1.0);
	m_range(a_max, 0.0, 1.0);
	m_range(die_a_add, -1.0, 0.0);

	FieldWall_t *i = nb(FieldWall_t);

	i->PicId = picId;
	i->PicRes = picRes;
	i->Origin = origin;
	i->Speed = speed;
	i->TileSize = tileSize;
	i->Life = life;
	i->AMax = a_max;
	i->AAdd = a_add;
	i->DieAAdd = die_a_add;

	i->Frame = -1; // -1 == uninited
//	i->A = 0.0;

	return i;
}
void ReleaseFieldWall(FieldWall_t *i)
{
	memFree(i);
}

// <-- cdtor

// <-- accessor

static int FieldWallEachFrame(FieldWall_t *i) // ret: ? dead
{
	if(i->Frame < i->Life)
	{
		i->A += i->AAdd;
	}
	else
	{
		i->A += i->DieAAdd;

		if(i->A < 0.0)
			return 1;
	}
	m_range(i->A, 0.0, i->AMax);

	i->Origin.X += i->Speed.X;
	i->Origin.Y += i->Speed.Y;

	int orig_x = i->Origin.X % i->TileSize.X;
	int orig_y = i->Origin.Y % i->TileSize.Y;

	if(0 < orig_x) orig_x -= i->TileSize.X;
	if(0 < orig_y) orig_y -= i->TileSize.Y;

	errorCase(!m_isRange(orig_x, -i->TileSize.X + 1, 0));
	errorCase(!m_isRange(orig_y, -i->TileSize.Y + 1, 0));

	DPE.PicRes = i->PicRes;
	DPE_SetAlpha(i->A);

	for(int x = orig_x; x < FIELD_W; x += i->TileSize.X)
	for(int y = orig_y; y < FIELD_H; y += i->TileSize.Y)
	{
		DrawRect(i->PicId, x, y, i->TileSize.X, i->TileSize.Y);
	}
	DPE_Reset();

	return 0;
}
void AllFieldWallEachFrame(void)
{
	for(int index = 0; index < GDc.FieldWallList->GetCount(); index++)
	{
		FieldWall_t *i = GDc.FieldWallList->GetElement(index);

		i->Frame++; // 0～

		if(FieldWallEachFrame(i)) // ? dead
		{
			ReleaseFieldWall(i);
			GDc.FieldWallList->SetElement(index, NULL);
		}
	}
	GDc.FieldWallList->MultiDiscard(isPointNull);
}
void AddFieldWall(FieldWall_t *i, int topMode)
{
	if(topMode)
		GDc.FieldWallList->InsertElement(0, i);
	else
		GDc.FieldWallList->AddElement(i);
}
void KillAllFieldWall(void)
{
	for(int index = 0; index < GDc.FieldWallList->GetCount(); index++)
	{
		FieldWall_t *i = GDc.FieldWallList->GetElement(index);

		if(i->Life == IMAX)
			i->Life = 0;
	}
}
