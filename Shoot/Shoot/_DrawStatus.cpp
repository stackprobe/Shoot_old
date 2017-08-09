#include "all.h"

static void DrawDigit(int l, int t, int w, int h, int digcolor, int digindex)
{
	DPE.MosaicOn = 1;
	DrawRect(D_DIGITS_W_00 + digcolor * 13 + digindex | DTP, l, t, w, h);
	DPE_Reset();
}
static void DrawShotPower(void)
{
	int power = GDc.Player.Power;
	char *sPower = xcout("%d.%02d", power / 100, power % 100);
	errorCase(strlen(sPower) != 4); // 2bs

	int digcolor;

	switch(GetPlayerLevel())
	{
	case 0:
		digcolor = 0;
		break;

	case 1:
	case 2:
		digcolor = 1;
		break;

	case 3:
	case 4:
		digcolor = 2;
		break;

	case 5:
		digcolor = 3;
		break;

	default:
		error();
	}

	const int DIG_W = 16;
	const int DIG_H = 32;
	const int DIG_SPAN = 2;
	int x = 610;
	int y = 230;

	DrawDigit(x, y, DIG_W * 2, DIG_H * 2, digcolor, GetPlayerLevel());
	x += DIG_W * 2 + DIG_SPAN;
	y += DIG_H;

	DrawDigit(x, y, DIG_W, DIG_H, digcolor, 12);
	x += DIG_W + DIG_SPAN;

	DrawDigit(x, y, DIG_W, DIG_H, digcolor, GDc.Player.Power / 10 % 10);
	x += DIG_W + DIG_SPAN;

	DrawDigit(x, y, DIG_W, DIG_H, digcolor, GDc.Player.Power % 10);
}
void DrawStatus(void)
{
	SetPrint(525, 30, 20);

	PE_Border(GetColor(100, 0, 150));
	Print_x(xcout("HiSCORE %20I64d", GDc.HiScore));
	PrintRet();
	PrintRet();

	PE_Border(GetColor(110, 0, 140));
	Print_x(xcout("  SCORE %20I64d", GDc.Score));
	PrintRet();
	PrintRet();
	PrintRet();

	PE_Border(GetColor(120, 0, 130));
	Print(" PLAYER  ");
	for(int c = 0; c < GDc.Zanki; c++)
	{
		Print("š");
	}
	PrintRet();
	PrintRet();

	PE_Border(GetColor(130, 0, 120));
	Print("   BOMB  ");
	for(int c = 0; c < GDc.ZanBomb; c++)
	{
		Print("—");
	}
	PrintRet();
	PrintRet();
	PrintRet();
	PrintRet();
	PrintRet();

	PE_Border(GetColor(150, 150, 100));
	Print("  POWER");
	PE_Reset();

	DrawShotPower();
}
