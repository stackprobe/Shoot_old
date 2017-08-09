typedef struct PlayerShotAtari_st
{
	PlayerShot_t *Owner;
	double X;
	double Y;
	double R;
}
PlayerShotAtari_t;

PlayerShotAtari_t *CreatePlayerShotAtari(PlayerShot_t *owner, double x, double y, double r);
void ReleasePlayerShotAtari(PlayerShotAtari_t *i);

// <-- cdtor

// <-- accessor
