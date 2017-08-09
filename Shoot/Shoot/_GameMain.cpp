#include "all.h"

static void DrawAllAtari(void) // for test
{
	DPE_SetBright(0.0, 1.0, 0);
	DPE_SetAlpha(0.5);

	for(int index = 0; index < GDc.PlayerShotAtariList->GetCount(); index++)
	{
		PlayerShotAtari_t *i = GDc.PlayerShotAtariList->GetElement(index);

		DrawBegin(P_WHITECIRCLE, i->X, i->Y);
		DrawZoom(i->R / 50.0);
		DrawEnd();
	}
	DPE_SetBright(0.0, 1.0, 1.0);

	for(int index = 0; index < GDc.EnemyAtariList->GetCount(); index++)
	{
		EnemyAtari_t *i = GDc.EnemyAtariList->GetElement(index);

		switch(i->Kind)
		{
		case EAK_CIRCLE:
			{
				DrawBegin(P_WHITECIRCLE, i->u.Circle.X, i->u.Circle.Y);
				DrawZoom(i->u.Circle.R / 50.0);
				DrawEnd();
			}
			break;

		case EAK_RECT:
			{
				DrawRect(P_WHITEBOX, i->u.Rect.L, i->u.Rect.T, i->u.Rect.W, i->u.Rect.H);
			}
			break;

		default:
			error();
		}
	}
	DPE_Reset();
}
static void DrawWall(void)
{
	DrawCurtain();

	double DENOM_X = 107.0;
	double DENOM_Y = 109.0;
//	double DENOM_X = 1009.0;
//	double DENOM_Y = 1013.0;
	double x = cos(ActFrame / DENOM_X) * 5.0;
	double y = sin(ActFrame / DENOM_Y) * 5.0;

	DPE_SetAlpha(0.3);
	DrawRect(P_WALL, x - 10.0, y - 10.0, SCREEN_W + 20.0, SCREEN_H + 20.0);
	DPE_Reset();
}
static void DrawField(void)
{
	DPE.GraphicHandleFlag = 1;
	DrawSimple(GetHandle(GDc.FieldScreen), FIELD_L, FIELD_T);
	DPE_Reset();
}
static void DrawFieldWall(void)
{
	DPE_SetBright(0, 0, 0);
	DrawRect(P_WHITEBOX, 0, 0, FIELD_W, FIELD_H);
	DPE_Reset();

	AllFieldWallEachFrame();
}

static void PauseMain(void)
{
	int pauseBtnRel = 0;

	for(; ; )
	{
		int pauseInp = GetInput(INP_PAUSE);

		if(pauseInp == -1) // ? just released
			if(pauseBtnRel)
				break;

		if(pauseInp <= 0) // ? released
			pauseBtnRel = 1;

		if(pauseInp == 0)
		{
			// todo: input
		}

		DrawWall();
		DrawField();

		DPE_SetAlpha(0.5);
		DPE_SetBright(0.0, 0.0, 0.0);
		DrawRect(P_WHITEBOX, FIELD_L, FIELD_T, FIELD_W, FIELD_H);
		DPE_Reset();

		EachFrame();
	}
}

static void ResetPlayer(void)
{
	GDc.Player.X = FIELD_W * 0.5;
	GDc.Player.Y = FIELD_H * 0.8;

	GDc.Player.BornFrame = 1;
	GDc.Player.DeadFrame = 0;
	GDc.Player.BombingFrame = 0;
}
void GameMain(void)
{
	if(!GDc.ScrRecList)
	{
		if(!GDc.ScriptFileData)
		{
			errorCase(!GDc.ScriptFile);

			GDc.ScriptFileData = readFile(GDc.ScriptFile);
		}

		GDc.ScrRecList = new autoList<ScrRec_t *>();
		LoadScrRecList(GDc.ScrRecList, GDc.ScriptFileData);
	}

	// 開始位置
	{
		ScrRec_t *sr = GDc.ScrRecList->GetElement(GDc.ScrRecStartPos);

		GDc.ScrRecFrame = sr->Frame;
		GDc.ScrRecIndex = GDc.ScrRecStartPos;
	}

	initRnd(GDc.Seed); // 電源パターン確保のため

	SetCurtain();
	FreezeInput();
	ActFrame = 0;

	MusicPlay(MUS_STAGE_01); // test

	ResetPlayer();

	for(; ; )
	{
		memset(&GDc.FS, 0x00, sizeof(GDc.FS));

#if LOG_ENABLED || 1
		if(GetKeyPound(KEY_INPUT_PGUP))
		{
			GDc.Player.Power += PLAYERPOWER_PER_LEVEL;
		}
		if(GetKeyPound(KEY_INPUT_PGDN))
		{
			GDc.Player.Power -= PLAYERPOWER_PER_LEVEL;
		}
		m_range(GDc.Player.Power, 0, PLAYERPOWER_MAX);
#endif

		if(1 <= GetInput(INP_PAUSE) && 10 < ActFrame)
		{
			enterRnd(GDc.PauseRnd);
			PauseMain();
			leaveRnd(GDc.PauseRnd);
		}

		// ステージ進行 >

#if 0 // わからん
		if(GDc.ScrRecIndex == GDc.ScrRecList->GetCount()) // ? 終わり -> かぼちゃでも出しとけ
		{
			static autoList<double> *args;

			if(!args)
				args = new autoList<double>();

			args->Clear();
			args->AddElement(bRnd(0, 1));
			args->AddElement(dRnd() * 5.0);
			args->AddElement(sRnd());
			args->AddElement(dRnd() * 100.0 + 300.0);
//			args->AddElement(dRnd() * 0.1 + 0.95);

			AddEnemy(Make_E01(args, GetECD(EK_ENEMY, 20, 10, -100.0, -100.0, IK_CANDY)));
		}
#endif
		if(GDc.ScrRecIndex == GDc.ScrRecList->GetCount()) // ? 終わり -> 戻っとけ
		{
			GDc.ScrRecIndex = 0;
			GDc.ScrRecFrame = 0;
		}

		while(GDc.ScrRecIndex < GDc.ScrRecList->GetCount())
		{
			ScrRec_t *sr = GDc.ScrRecList->GetElement(GDc.ScrRecIndex);

			if(GDc.ScrRecFrame < sr->Frame)
				break;

			switch(sr->EventId)
			{
				/*
					空行のため
				*/
			case 0: // noop
				break;

			case 1: // change wall phase
				{
					KillAllFieldWall();
					GDc.FieldWallPhase = d2i(sr->SubId);
					GDc.FieldWallPhaseFrame = 0;
				}
				break;

			case 2: // add enemy
				{
					AddEnemy(sr);
				}
				break;

			default:
				error();
			}

			GDc.ScrRecIndex++;
		}
		GDc.ScrRecFrame++;

		FieldWallPhaseEachFrame();

		// < ステージ進行

		GDc.LPI = GDc.CPI;

		// プレイヤー入力
		{
			GDc.CPI.Dir2 = 1 <= GetInput(INP_DIR_2);
			GDc.CPI.Dir4 = 1 <= GetInput(INP_DIR_4);
			GDc.CPI.Dir6 = 1 <= GetInput(INP_DIR_6);
			GDc.CPI.Dir8 = 1 <= GetInput(INP_DIR_8);
			GDc.CPI.Slow = 1 <= GetInput(INP_A);
			GDc.CPI.Shot = 1 <= GetInput(INP_B);
			GDc.CPI.Bomb = 1 <= GetInput(INP_C);
		}

		GDc.Player.LastX = GDc.Player.X;
		GDc.Player.LastY = GDc.Player.Y;

startBornPlayer:
		if(GDc.Player.BornFrame)
		{
			int frm = GDc.Player.BornFrame - 1;

			if(PLAYER_BORNFRAME_MAX < frm)
			{
				GDc.Player.BornFrame = 0;
				goto endBornPlayer;
			}
			GDc.Player.BornFrame++;

			// frm == 0 ～ PLAYER_BORNFRAME_MAX

//			double fRate = (double)frm / PLAYER_BORNFRAME_MAX; // 0.0 - 1.0

			if(!frm) // init
			{
				GDc.Player.FollowX = FIELD_W * 0.5;
				GDc.Player.FollowY = FIELD_H * 1.2;
			}

			double apprRate = 0.99 - 0.01 * frm;
			m_range(apprRate, 0.0, 1.0);

			m_approach(GDc.Player.FollowX, GDc.Player.X, apprRate);
			m_approach(GDc.Player.FollowY, GDc.Player.Y, apprRate);
		}
endBornPlayer:
		if(GDc.Player.DeadFrame)
		{
			int frm = GDc.Player.DeadFrame - 1;

			if(PLAYER_DEADFRAME_MAX < frm)
			{
				ResetPlayer();
				goto startBornPlayer;
			}
			GDc.Player.DeadFrame++;

			// frm == 0 ～ PLAYER_DEADFRAME_MAX

			if(!frm) // init
			{
				CEE.EndPicId = D_PLAYERDIE_00_END | DTP;
				CEE.PicIdFrmPerInc = 4;
//				CEE.BlendAddOn = 1;
				AddCommonEffect(
					GDc.EP,
					0,
					D_PLAYERDIE_00 | DTP,
					GDc.Player.X,
					GDc.Player.Y,
					0.0,
					1.0,
					0.8,
					0.0,
					-0.002,
					0.0,
					0.05
					);
				CEE_Reset();
			}
			goto endPlayerMove;
		}
		if(GDc.Player.BombingFrame)
		{
			int frm = GDc.Player.BombingFrame - 1;

			if(PLAYER_BOMBINGFRAME_MAX < frm)
			{
				GDc.Player.BombingFrame = 0;
				goto endBombingPlayer;
			}
			GDc.Player.BombingFrame++;

			// frm == 0 ～ PLAYER_BOMBINGFRMAE_MAX

			if(!frm) // at first
			{
				ShotPlayerBomb();
			}
		}
endBombingPlayer:

		// プレイヤー移動
		{
			int d2 = GDc.CPI.Dir2;
			int d4 = GDc.CPI.Dir4;
			int d6 = GDc.CPI.Dir6;
			int d8 = GDc.CPI.Dir8;

			double speed = 5.0;

			if(GDc.CPI.Slow)
				speed /= 2.0;

			double nanameSpeed = speed / R2;

			if(d2 && d4) // 左下
			{
				GDc.Player.X -= nanameSpeed;
				GDc.Player.Y += nanameSpeed;
			}
			else if(d2 && d6) // 右下
			{
				GDc.Player.X += nanameSpeed;
				GDc.Player.Y += nanameSpeed;
			}
			else if(d4 && d8) // 左上
			{
				GDc.Player.X -= nanameSpeed;
				GDc.Player.Y -= nanameSpeed;
			}
			else if(d6 && d8) // 右上
			{
				GDc.Player.X += nanameSpeed;
				GDc.Player.Y -= nanameSpeed;
			}
			else if(d2) // 下
			{
				GDc.Player.Y += speed;
			}
			else if(d4) // 左
			{
				GDc.Player.X -= speed;
			}
			else if(d6) // 右
			{
				GDc.Player.X += speed;
			}
			else if(d8) // 上
			{
				GDc.Player.Y -= speed;
			}

			m_range(GDc.Player.X, 0.0, (double)FIELD_W);
			m_range(GDc.Player.Y, 0.0, (double)FIELD_H);

			if(d4) // 左
			{
				m_minim(GDc.Player.XMoveFrame, 0);
				GDc.Player.XMoveFrame--;
			}
			else if(d6) // 右
			{
				m_maxim(GDc.Player.XMoveFrame, 0);
				GDc.Player.XMoveFrame++;
			}
			else
			{
				GDc.Player.XMoveFrame = 0;
			}

			if(d8) // 上
			{
				m_minim(GDc.Player.YMoveFrame, 0);
				GDc.Player.YMoveFrame--;
			}
			else if(d2) // 下
			{
				m_maxim(GDc.Player.YMoveFrame, 0);
				GDc.Player.YMoveFrame++;
			}
			else
			{
				GDc.Player.YMoveFrame = 0;
			}

			m_approach(
				GDc.Player.XMoveRate,
				(double)m_iSign(GDc.Player.XMoveFrame),
				0.95
				);

			m_approach(
				GDc.Player.YMoveRate,
				(double)m_iSign(GDc.Player.YMoveFrame),
				0.95
				);
		}
endPlayerMove:

		if(GDc.CPI.Slow)
		{
			m_maxim(GDc.Player.SlowFrame, 0);
			GDc.Player.SlowFrame++;
		}
		else
		{
			m_minim(GDc.Player.SlowFrame, 0);
			GDc.Player.SlowFrame--;
		}

		if(GDc.CPI.Shot)
		{
			m_maxim(GDc.Player.ShotFrame, 0);
			GDc.Player.ShotFrame++;
		}
		else
		{
			m_minim(GDc.Player.ShotFrame, 0);
			GDc.Player.ShotFrame--;
		}

		m_approach(
			GDc.Player.SlowRate,
			GDc.Player.SlowFrame < 0 ? 0.0 : 1.0,
			0.85
			);

		if(GDc.LPI.Shot && GDc.CPI.Shot && m_isRange(GDc.Player.SlowFrame, -1, 1)) // ? ショット中に低速・高速を切り替えた。
		{
			GDc.Player.ShotRate = 0.0;
		}

		m_approach(
			GDc.Player.ShotRate,
			GDc.Player.ShotFrame < 0 ? 0.0 : 1.0,
			0.8
			);

		// ----

		if(GDc.CPI.Shot && !GDc.Player.DeadFrame) // プレイヤーショット
		{
			ShotPlayer();
		}
		if(GDc.CPI.Bomb && !GDc.Player.DeadFrame && !GDc.Player.BombingFrame && GDc.ZanBomb) // ボム使用
		{
			GDc.ZanBomb--;
			GDc.Player.BombingFrame = 1;
		}

		PutAllPlayerAtari();
		AllPlayerShotEachFrame();
		AllEnemyEachFrame();
		AtariHantei();

		if(GDc.FS.Grazed)
		{
			SEPlay(SE_KASURI);
			GDc.Score++;
		}

		// Draw...

		if(!GDc.Player.DeadFrame)
		{
			DrawPlayer();
		}

		// Draw to Field
		{
			ChangeDrawScreen(GDc.FieldScreen);

			DrawFieldWall();

			GDc.DPS->ExecuteAllTask();
			GDc.DP->ExecuteAllTask();
			GDc.DE->ExecuteAllTask();
			GDc.DES->ExecuteAllTask();
			GDc.DI->ExecuteAllTask();
			GDc.EE->ExecuteAllTask();
			GDc.EP->ExecuteAllTask();

#if LOG_ENABLED
			{
				static int actv;

				if(GetKeyPound(KEY_INPUT_1))
					actv = !actv;

				if(actv)
					DrawAllAtari();
			}
#endif

			RestoreDrawScreen();
		}

		// 当たり判定のクリア {
		GDc.PlayerAtariList->Clear(ReleasePlayerAtari);
		GDc.PlayerShotAtariList->Clear(ReleasePlayerShotAtari);
		GDc.EnemyAtariList->Clear(ReleaseEnemyAtari);
		// }

		DrawWall();
		DrawField();
		DrawStatus();

		clsDx();
		printfDx("%.3f %.3f %d %d\n", GDc.Player.X, GDc.Player.Y, GDc.Player.Power, GDc.EnemyList->GetCount());
		printfDx("%d %d\n", GDc.ScrRecIndex, GDc.ScrRecFrame);

		EachFrame();

		GDc.GameFrame++;
	}
//endGameLoop:

//	FreezeInput();
	MusicFade();
	SetCurtain(30, -1.0);

	forscene(40)
	{
		DrawWall();
		DrawField();
		EachFrame();
	}
	sceneLeave();

	initRnd((int)time(NULL));
}
