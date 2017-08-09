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
	int Seed; // �X�e�[�W���ɈقȂ鉽�炩�̒l
	int Zanki;
	int ZanBomb;
	uint64 HiScore;
	uint64 Score;

	/*
		�ǂꂩ�P�͗L���ł��邱�ƁB
	*/
	char *ScriptFile;
	autoList<uchar> *ScriptFileData; // bind
	autoList<ScrRec_t *> *ScrRecList; // bind
	// }

	// Return {
	// }

	int ScrRecStartPos;
	int ScrRecIndex;
	int ScrRecFrame; // �X�N���v�g���ł̈ꎞ��~����
	int GameFrame; // �|�[�Y���������o�߃t���[��

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
		double X; // 0.0 �` FIELD_W
		double Y; // 0.0 �` FIELD_H
		double LastX; // 0.0 �` FIELD_W
		double LastY; // 0.0 �` FIELD_H
		int XMoveFrame; // <0 == ���ړ���, 0 == ���E�ړ��i�V, 0< == �E�ړ���
		int YMoveFrame; // <0 == ��ړ���, 0 == �㉺�ړ��i�V, 0< == ���ړ���
		double XMoveRate; // ���ړ��� <-- 0.0 �` 1.0 --> �E�ړ���
		double YMoveRate; // ��ړ��� <-- 0.0 �` 1.0 --> ���ړ���
		int SlowFrame; // <0 == �����ړ���, 0 == uninited, 0< == �ᑬ�ړ���
		int ShotFrame; // <0 == ���V���b�g, 0 == uninited, 0< == �V���b�g��
		double SlowRate; // �����ړ��� <-- 0.0 �` 1.0 --> �ᑬ�ړ���
		double ShotRate; // ���V���b�g <-- 0.0 �` 1.0 --> �V���b�g��, �p���[�A�b�v�� 0.0 �Ƀ��Z�b�g����B
		int Power; // 0 �` PLAYERPOWER_MAX
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
		memo: �S�ă��X�g�ւ̒ǉ��̂݊֐��Ń��b�v
	*/
	autoList<FieldWall_t *> *FieldWallList;
	autoList<PlayerAtari_t *> *PlayerAtariList;
	autoList<PlayerShot_t *> *PlayerShotList;
	autoList<PlayerShotAtari_t *> *PlayerShotAtariList;
	autoList<Enemy_t *> *EnemyList;
	autoList<EnemyAtari_t *> *EnemyAtariList;

	/*
		�t���[�����[�v�̐擪�Ń[���N���A����B
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
