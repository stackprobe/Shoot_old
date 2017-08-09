enum // PlayerShotKind
{
	PSK_NORMAL,
	PSK_STRONG,
	PSK_WAVE,
	PSK_LASER,
	PSK_BOMB,

	PSK_MAX, // num of member
};

typedef struct PlayerShot_st
{
	int Kind; // PSK_*
	int Level; // 0 Å` PLAYERLEVEL_MAX
	double X;
	double Y;
	double R;
	double RAdd;

	int Frame;
	int DeadFlag;
}
PlayerShot_t;

PlayerShot_t *CreatePlayerShot(int kind, double x, double y, double r = 0.0, double ra = 0.0, int level = 0);
void ReleasePlayerShot(PlayerShot_t *i);

// <-- cdtor

// <-- accessor

void AllPlayerShotEachFrame(void);
void AddPlayerShot(PlayerShot_t *i);
int GetDamage(PlayerShot_t *i);
