typedef struct FieldWall_st
{
	int PicId;
	resCluster<PicInfo_t *> *PicRes;
	i2D_t Origin;
	i2D_t Speed;
	i2D_t TileSize;
	int Life;
	double AAdd; // ç≈èâÇ©ÇÁ A == AMax Ç…Ç∑ÇÈÇ…ÇÕ AMax Ç∆ìØÇ∂ílÇ…Ç∑ÇÈÅB
	double AMax;
	double DieAAdd;

	int Frame;
	double A;
}
FieldWall_t;

FieldWall_t *CreateFieldWall(
	int picId,
	resCluster<PicInfo_t *> *picRes = NULL,
	i2D_t speed = makeI2D(0, 1),
	i2D_t origin = makeI2D(0, 0),
	i2D_t tileSize = makeI2D(-1, -1),
	int life = IMAX,
	double a_add = 0.01,
	double a_max = 1.0,
	double die_a_add = -0.01
	);
void ReleaseFieldWall(FieldWall_t *i);

// <-- cdtor

// <-- accessor

void AllFieldWallEachFrame(void);
void AddFieldWall(FieldWall_t *i, int topMode = 0);
void KillAllFieldWall(void);
