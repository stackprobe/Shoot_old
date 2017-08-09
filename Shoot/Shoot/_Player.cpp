#include "all.h"

void ShotPlayer(void)
{
	double pl_x;
	double pl_y;

	if(GDc.Player.BornFrame)
	{
		pl_x = GDc.Player.FollowX;
		pl_y = GDc.Player.FollowY;

		if(IsOutOfField(pl_x, pl_y, 0.0)) // 画面外からは撃てない。
		{
			return;
		}
	}
	else
	{
		pl_x = GDc.Player.X;
		pl_y = GDc.Player.Y;
	}

	if(0 < GDc.Player.SlowFrame) // 低速移動
	{
		if(ActFrame % 4 == 0)
		{
			SEPlay(SE_PLAYERSHOT);

			AddPlayerShot(CreatePlayerShot(
				PSK_LASER,
				pl_x,
				pl_y - 10.0,
				0.0,
				0.0,
				GetPlayerLevel()
				));
		}
	}
	else // 高速移動
	{
		if(ActFrame % 3 == 0)
		{
			SEPlay(SE_PLAYERSHOT);
		}

		switch(GetPlayerLevel()) // 前方ショット
		{
		case 0:
		case 1:
			{
				if(ActFrame % 3 == 0)
				{
					AddPlayerShot(CreatePlayerShot(
						PSK_NORMAL,
						pl_x,
						pl_y - 5.0
						));
				}
			}
			break;

		case 2:
			{
				if(ActFrame % 3 == 0)
				{
					for(int c = -1; c <= 1; c += 2)
					{
						AddPlayerShot(CreatePlayerShot(
							PSK_NORMAL,
							pl_x + 8.0 * c,
							pl_y - 5.0
							));
					}
				}
			}
			break;

		case 3:
			{
				if(ActFrame % 3 == 0)
				{
					AddPlayerShot(CreatePlayerShot(
						PSK_STRONG,
						pl_x,
						pl_y - 5.0
						));

					for(int c = -1; c <= 1; c += 2)
					{
						AddPlayerShot(CreatePlayerShot(
							PSK_NORMAL,
							pl_x + 16.0 * c,
							pl_y - 5.0,
							0.1 * c
							));
					}
				}
			}
			break;

		case 4:
			{
				if(ActFrame % 3 == 0)
				{
					for(int c = -1; c <= 1; c += 2)
					{
						AddPlayerShot(CreatePlayerShot(
							PSK_NORMAL,
							pl_x + 8.0 * c,
							pl_y - 5.0
							));
					}
					for(int c = -1; c <= 1; c += 2)
					{
						AddPlayerShot(CreatePlayerShot(
							PSK_NORMAL,
							pl_x + 16.0 * c,
							pl_y - 5.0,
							0.1 * c
							));
					}
				}
			}
			break;

		case 5:
			{
				if(ActFrame % 3 == 0)
				{
					AddPlayerShot(CreatePlayerShot(
						PSK_STRONG,
						pl_x,
						pl_y - 5.0
						));

					for(int c = -1; c <= 1; c += 2)
					{
						AddPlayerShot(CreatePlayerShot(
							PSK_STRONG,
							pl_x + 16.0 * c,
							pl_y - 5.0,
							0.05 * c
							));

						AddPlayerShot(CreatePlayerShot(
							PSK_NORMAL,
							pl_x + 24.0 * c,
							pl_y - 5.0,
							0.1 * c
							));
					}
				}
			}
			break;

		default:
			error();
		}
		switch(GetPlayerLevel()) // サイドショット
		{
		case 0:
			break;

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			{
				if(ActFrame % 4 == 0)
				{
					for(int c = -1; c <= 1; c+= 2)
					{
						AddPlayerShot(CreatePlayerShot(
							PSK_WAVE,
							pl_x + 20.0 * c,
							pl_y - 5.0,
							0.3 * c,
							(-0.021 - 0.003 * GDc.Player.YMoveRate) * c
							));
					}
				}
			}
			break;

		default:
			error();
		}
	}
}
void ShotPlayerBomb(void)
{
	AddPlayerShot(CreatePlayerShot(
		PSK_BOMB,
		GDc.Player.X,
		GDc.Player.Y
		));
}
void PutAllPlayerAtari(void)
{
	const int DIV = 5;

	for(int c = 1; c <= DIV; c++)
	{
		double x = GDc.Player.LastX;
		double y = GDc.Player.LastY;

		m_approach(x, GDc.Player.X, (double)c / DIV);
		m_approach(y, GDc.Player.Y, (double)c / DIV);

		AddPlayerAtari(CreatePlayerAtari(x, y));
	}
}
void DrawPlayer(void)
{
	int dr_x;
	int dr_y;
	double dr_a;

	if(GDc.Player.BornFrame)
	{
		dr_x = d2i(GDc.Player.FollowX);
		dr_y = d2i(GDc.Player.FollowY);
		dr_a = 0.5;
	}
	else if(GDc.Player.BombingFrame)
	{
		dr_x = d2i(GDc.Player.X);
		dr_y = d2i(GDc.Player.Y);
		dr_a = 0.5;
	}
	else
	{
		dr_x = d2i(GDc.Player.X);
		dr_y = d2i(GDc.Player.Y);
		dr_a = 1.0;
	}

	if(-20 < GDc.Player.SlowFrame) // ? 低速移動中(余韻アリ)
	{
		double r = GDc.Player.SlowRate;
		double a = dr_a * r * 0.7;

		DPE.TL = GDc.DP;
		DPE_SetBlendAdd(a);
		DrawBegin(D_SLOWBACK | DTP, dr_x, dr_y);
		DrawRotate(ActFrame * 0.01);
		DrawZoom(1.0 + (1.0 - r) * 4.0);
		DrawEnd();
		DPE_Reset();
	}
#if 0
	if(0 < GDc.Player.SlowFrame && 0 < GDc.Player.ShotFrame) // ? 低速ショット中
	{
		double a = dr_a * 0.5;

		DPE.TL = GDc.DP;
		DPE_SetGraphicSize(GDc.GSz_LaserFire[0]);
		DPE_SetAlpha(a);
		DrawBegin(GDc.GH_LaserFire[ActFrame % 3], dr_x, dr_y - 40.0);
		DrawZoom_X(1.0 + (0.5 * GDc.Player.Level) / PLAYERLEVEL_MAX);
		DrawEnd();
		DPE_Reset();
	}
#endif
	if(-20 < GDc.Player.ShotFrame) // ? ショット中(余韻アリ)
	{
		double r = GDc.Player.ShotRate;

		if(0 < GDc.Player.SlowFrame) // 低速
		{
			int bookKoma = ActFrame / 3;
			bookKoma %= 3;

			DPE.TL = GDc.DP;
			DPE_SetAlpha(dr_a * r * 0.3);

			DrawBegin(
				D_BOOKBACK | DTP,
				dr_x,
				dr_y - 24.0 * r
				);
			DrawZoom(1.5 + 1.0 * r);
			DrawRotate(ActFrame * 0.02);
			DrawZoom_Y(0.5);
			DrawEnd();

			DPE_SetAlpha(dr_a * r * 1.0);

			for(int c = -1; c <= 1; c += 2)
			{
				DrawCenter(
					D_BOOK_00 + bookKoma | DTP,
					dr_x + 18.0 * c * r,
					dr_y - 14.0 * r
					);
			}
			DPE_Reset();
		}
		else if(1 <= GetPlayerLevel()) // 高速 && ウェーブショット有り
		{
			int bookKoma = ActFrame / 5;
			bookKoma %= 3;

			DPE.TL = GDc.DP;
			DPE_SetAlpha(dr_a * r * 0.3);

			for(int c = -1; c <= 1; c += 2)
			{
				DrawBegin(
					D_BOOKBACK | DTP,
					dr_x + 25.0 * c * r,
					dr_y - 12.0 * r
					);
				DrawZoom(0.5 + 1.0 * r);
				DrawRotate(ActFrame * 0.02);
				DrawZoom_Y(0.5);
				DrawEnd();
			}
			DPE_SetAlpha(dr_a * r * 1.0);

			for(int c = -1; c <= 1; c += 2)
			{
				DrawCenter(
					D_BOOK_00 + bookKoma | DTP,
					dr_x + 25.0 * c * r,
					dr_y
					);
			}
			DPE_Reset();
		}
	}

	int koma = ActFrame / 7;

	if(GDc.Player.XMoveFrame)
	{
		koma %= 3;
		koma += GDc.Player.XMoveFrame < 0 ? 4 : 8;
	}
	else
		koma %= 4;

	DPE.TL = GDc.DP;
	DPE_SetAlpha(dr_a);
	DrawCenter(D_KOAKUMA_00 + koma | DTP, dr_x, dr_y);
	DPE_Reset();

	if(-20 < GDc.Player.SlowFrame) // ? 低速移動中(余韻アリ)
	{
		double a = dr_a * GDc.Player.SlowRate;
		a *= 2.0;

		DPE.TL = GDc.DP;
		DPE_SetAlpha(a);
		DrawBegin(D_ATARIPOINT | DTP, dr_x, dr_y);
		DrawRotate(ActFrame * 0.02);
		DrawEnd();
		DPE_Reset();
	}
}
