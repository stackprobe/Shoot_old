#include "all.h"

void FieldWallPhaseEachFrame(void)
{
	int frm = GDc.FieldWallPhaseFrame; // 0Å`

	switch(GDc.FieldWallPhase)
	{
	case 0:
		if(!frm)
		{
			AddFieldWall(CreateFieldWall(
				P_BLUETILE_02,
				GetQuartPicRes(),
				makeI2D(0, 2),
				makeI2D(-128, 0),
				makeI2D(-1, -1),
				IMAX,
				0.01,
				1.0
				));
			AddFieldWall(CreateFieldWall(
				P_BW_PUMPKIN,
				NULL,
				makeI2D(0, 3),
				makeI2D(-100, 0),
				makeI2D(-1, -1),
				IMAX,
				0.0001,
				0.1
				));
		}
		break;

	case 1:
		if(!frm)
		{
			AddFieldWall(CreateFieldWall(
				P_BLUETILE_01,
				NULL,
				makeI2D(1, 1),
				makeI2D(0, 0),
				makeI2D(-1, -1),
				IMAX,
				0.01,
				1.0
				));
		}
		break;

	case 2:
		if(!frm)
		{
			AddFieldWall(CreateFieldWall(
				P_BLUETILE_03,
				NULL,
				makeI2D(-1, 1),
				makeI2D(0, 0),
				makeI2D(-1, -1),
				IMAX,
				0.01,
				1.0
				));
		}
		break;

	default:
		error();
	}

	GDc.FieldWallPhaseFrame++;
}
