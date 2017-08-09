typedef struct PlayerAtari_st
{
	double X;
	double Y;
}
PlayerAtari_t;

PlayerAtari_t *CreatePlayerAtari(double x, double y);
void ReleasePlayerAtari(PlayerAtari_t *i);

// <-- cdtor

// <-- accessor
