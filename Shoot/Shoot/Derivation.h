enum
{
	ENUM_RANGE(D_DUMMY_00, 4)

	// app >

	// -- P1 --

	ENUM_RANGE(D_KOAKUMA_00, 4 * 3)
	ENUM_RANGE(D_BLAST_00, 4)
	ENUM_RANGE(D_BOOK_00, 3)
	D_ATARIPOINT,
	D_SHOT,
	D_WAVESHOT,
	D_BOOKBACK,
	D_SLOWBACK,
	D_ITEM_HEART,
	D_ITEM_STAR,
	ENUM_RANGE(D_LASERBLAST_00, 3)
	D_LASER,
	ENUM_RANGE(D_LASERFIRE_00, 3)

	// -- P3 --

	D_DECOCIRCLE,
	D_LEVELUP,
	D_ITEM_CANDY,
	D_ITEM_BOMB,
	ENUM_RANGE(D_BARAN_00, BARAN_DIV)
	D_GAUGE,
	D_GAUGEBAR,

	// --

	ENUM_RANGE(D_ENEMYDIE_00, 10)
	ENUM_RANGE(D_ENEMYSHOTDIE_00, 10)
	ENUM_RANGE(D_PLAYERDIE_00, 10)
	ENUM_RANGE(D_PUMPKIN_00, 2)
	ENUM_RANGE(D_TAMA_00, TAMA_KIND_NUM * TAMA_COLOR_NUM) // �G�e

	ENUM_RANGE(D_DIGITS_W_00, 13)
	ENUM_RANGE(D_DIGITS_DDY_00, 13)
	ENUM_RANGE(D_DIGITS_DY_00, 13)
	ENUM_RANGE(D_DIGITS_Y_00, 13)

	ENUM_RANGE(D_FAIRY_00, 8 * 8)
	ENUM_RANGE(D_BIGFAIRY_00, 4 * 4)
	ENUM_RANGE(D_ONIBI_00, 3 * 4)

	ENUM_RANGE(D_MAHOJIN_HAJIKE_00, 14) // �����w�Ƃ��� _00 + 5 ���g���B

	// < app

	D_MAX, // num of member
};

typedef struct DerInfo_st
{
	int ParentPicId;
	int X;
	int Y;
	int W;
	int H;
}
DerInfo_t;

int Der(resCluster<PicInfo_t *> *resclu, int derId);
int Der_W(int derId);
int Der_H(int derId);

void UnloadAllDer(resCluster<PicInfo_t *> *resclu);
