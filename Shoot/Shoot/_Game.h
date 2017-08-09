typedef struct PlayerInput_st
{
	BOOL Dir2;
	BOOL Dir4;
	BOOL Dir6;
	BOOL Dir8;
	BOOL Slow;
	BOOL Shot;
	BOOL Bomb;
}
PlayerInput_t;

typedef struct GDc_st
{
	// Params {
	int Seed; // ステージ毎に異なる何らかの値
	int Zanki;
	int ZanBomb;
	uint64 HiScore;
	uint64 Score;

	/*
		どれか１つは有効であること。
	*/
	char *ScriptFile;
	autoList<uchar> *ScriptFileData; // bind
	autoList<ScrRec_t *> *ScrRecList; // bind
	// }

	// Return {
	// }

	int ScrRecStartPos;
	int ScrRecIndex;
	int ScrRecFrame; // スクリプト内での一時停止あり
	int GameFrame; // ポーズ時を除く経過フレーム

	rnd_t *PauseRnd;
	Random *ItemRnd;

	int GH_Laser;
	int GH_LaserBlast[3];
	int GH_LaserFire[3];

	i2D_t GSz_Laser;
	i2D_t GSz_LaserBlast[3];
	i2D_t GSz_LaserFire[3];

	SubScreen_t *FieldScreen;

	/*
		for Draw
	*/
	taskList *DE;  // DrawEnemy
	taskList *DES; // DrawEnemyShot
	taskList *DP;  // DrawPlyer
	taskList *DPS; // DrawPlyerShot
	taskList *DI;  // DrawItem
	taskList *EE;  // EffectEnemy
	taskList *EP;  // EffectPlayer

	PlayerInput_t CPI; // CurrentPlayerInput
	PlayerInput_t LPI; // LastPlayerInput

	struct
	{
		double X; // 0.0 ～ FIELD_W
		double Y; // 0.0 ～ FIELD_H
		double LastX; // 0.0 ～ FIELD_W
		double LastY; // 0.0 ～ FIELD_H
		int XMoveFrame; // <0 == 左移動中, 0 == 左右移動ナシ, 0< == 右移動中
		int YMoveFrame; // <0 == 上移動中, 0 == 上下移動ナシ, 0< == 下移動中
		double XMoveRate; // 左移動中 <-- 0.0 ～ 1.0 --> 右移動中
		double YMoveRate; // 上移動中 <-- 0.0 ～ 1.0 --> 下移動中
		int SlowFrame; // <0 == 高速移動中, 0 == uninited, 0< == 低速移動中
		int ShotFrame; // <0 == 無ショット, 0 == uninited, 0< == ショット中
		double SlowRate; // 高速移動中 <-- 0.0 ～ 1.0 --> 低速移動中
		double ShotRate; // 無ショット <-- 0.0 ～ 1.0 --> ショット中, パワーアップ時 0.0 にリセットする。
		int Power; // 0 ～ PLAYERPOWER_MAX
		int BornFrame; // zd
		int DeadFrame; // zd
		int BombingFrame; // zd
		double FollowX;
		double FollowY;
	}
	Player;

	int FieldWallPhase;
	int FieldWallPhaseFrame;

	/*
		memo: 全てリストへの追加のみ関数でラップ
	*/
	autoList<FieldWall_t *> *FieldWallList;
	autoList<PlayerAtari_t *> *PlayerAtariList;
	autoList<PlayerShot_t *> *PlayerShotList;
	autoList<PlayerShotAtari_t *> *PlayerShotAtariList;
	autoList<Enemy_t *> *EnemyList;
	autoList<EnemyAtari_t *> *EnemyAtariList;

	/*
		フレームループの先頭でゼロクリアする。
	*/
	struct
	{
		int Grazed;
	}
	FS; // FrameStatus
}
GDc_t;

extern GDc_t GDc;

void GameInit(void);
void GameFnlz(void);
