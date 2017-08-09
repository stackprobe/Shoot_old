enum
{
	P_DUMMY,
	P_WHITEBOX,
	P_WHITECIRCLE,

	// app >

	P_KOAKUMA_P1,
	P_KOAKUMA_P3,
	ENUM_RANGE(P_KOAKUMA_TACHIE_00, 9)
	P_KOAKUMA_WALL_TEXT,
	P_KOAKUMA_WALL,
	P_ENEMYDIE,
	P_ENEMYSHOTDIE,
	P_PLAYERDIE,
	P_PUMPKIN,
	P_TAMA,
	P_BLUETILE_01,
	P_BLUETILE_02,
	P_BLUETILE_03,
	P_BLUETILE_04,
	P_BLUETILE_05,
	P_BLUETILE_06,
	P_BLUETILE_07,
	P_BLUETILE_08,
	P_BLUETILE_09,
	P_BLUETILE_10,
	P_BLUETILE_11,
	P_BLUETILE_12,
	P_BLUETILE_13,
	P_BLUETILE_14,
	P_BLUETILE_15,
	P_BW_TILE_01,
	P_BW_PUMPKIN,
	P_DIGITS_W,
	P_DIGITS_DDY,
	P_DIGITS_DY,
	P_DIGITS_Y,
	P_WALL,
	P_FAIRYETC,
	P_MAHOJIN_HAJIKE,

	// < app

	P_MAX, // num of member
};

typedef struct PicInfo_st
{
	int Handle;
	int W;
	int H;
}
PicInfo_t;

// Pic_ >

int Pic_FileData2SoftImage(autoList<uchar> *fileData);
int Pic_SoftImage2GraphicHandle(int si_h);
PicInfo_t *Pic_GraphicHandle2PicInfo(int handle);
void Pic_ReleasePicInfo(PicInfo_t *i);

void Pic_GetSoftImageSize(int si_h, int &w, int &h);
void Pic_GetGraphicHandleSize(int handle, int &w, int &h);

extern int SI_R;
extern int SI_G;
extern int SI_B;
extern int SI_A;

void Pic_GetSIPixel(int si_h, int x, int y);
void Pic_SetSIPixel(int si_h, int x, int y);

int Pic_CreateSoftImage(int w, int h);
void Pic_ReleaseSoftImage(int si_h);
void Pic_ReleaseGraphicHandle(int handle);

// < Pic_

resCluster<PicInfo_t *> *CreatePicRes(PicInfo_t *(*picLoader)(autoList<uchar> *), void (*picUnloader)(PicInfo_t *));
void UnloadAllPicResHandle(void);

void SetPicRes(resCluster<PicInfo_t *> *resclu);
resCluster<PicInfo_t *> *GetPicRes(void);
void ResetPicRes(void);

#define DTP 0x40000000

int Pic(int picId);
int Pic_W(int picId);
int Pic_H(int picId);
