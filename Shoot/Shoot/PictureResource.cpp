#include "all.h"

static PicInfo_t *LoadPic(autoList<uchar> *fileData)
{
	return Pic_GraphicHandle2PicInfo(Pic_SoftImage2GraphicHandle(Pic_FileData2SoftImage(fileData)));
}
static void UnloadPic(PicInfo_t *i)
{
	Pic_ReleasePicInfo(i);
}
oneObject(resCluster<PicInfo_t *>, CreatePicRes(LoadPic, UnloadPic), GetStdPicRes);

static PicInfo_t *LoadTwistPic(autoList<uchar> *fileData)
{
	int si_h = Pic_FileData2SoftImage(fileData);
	int w;
	int h;

	Pic_GetSoftImageSize(si_h, w, h);

	int new_w = h;
	int new_h = w;
	int new_si_h = Pic_CreateSoftImage(new_w, new_h);

	for(int x = 0; x < w; x++)
	for(int y = 0; y < h; y++)
	{
		Pic_GetSIPixel(si_h, x, y);
		Pic_SetSIPixel(new_si_h, y, x);
	}
	Pic_ReleaseSoftImage(si_h);
	return Pic_GraphicHandle2PicInfo(Pic_SoftImage2GraphicHandle(new_si_h));
}
oneObject(resCluster<PicInfo_t *>, CreatePicRes(LoadTwistPic, UnloadPic), GetTwistPicRes);

static PicInfo_t *LoadReductPic(autoList<uchar> *fileData, int denom)
{
	errorCase(!fileData);
	errorCase(denom < 1 || IMAX < denom);

	int si_h = Pic_FileData2SoftImage(fileData);
	int w;
	int h;

	Pic_GetSoftImageSize(si_h, w, h);

	errorCase(w % denom);
	errorCase(h % denom);

	int new_w = w / denom;
	int new_h = h / denom;
	int new_si_h = Pic_CreateSoftImage(new_w, new_h);

	for(int x = 0; x < new_w; x++)
	for(int y = 0; y < new_h; y++)
	{
		int tR = 0;
		int tG = 0;
		int tB = 0;
		int tA = 0;

		for(int sx = 0; sx < denom; sx++)
		for(int sy = 0; sy < denom; sy++)
		{
			Pic_GetSIPixel(si_h, x * denom + sx, y * denom + sy);

			tR += SI_R;
			tG += SI_G;
			tB += SI_B;
			tA += SI_A;
		}
		double div = m_pow(denom);

		SI_R = d2i(tR / div);
		SI_G = d2i(tG / div);
		SI_B = d2i(tB / div);
		SI_A = d2i(tA / div);

		Pic_SetSIPixel(new_si_h, x, y);
	}
	Pic_ReleaseSoftImage(si_h);
	return Pic_GraphicHandle2PicInfo(Pic_SoftImage2GraphicHandle(new_si_h));
}
static PicInfo_t *LoadHalfPic(autoList<uchar> *fileData)
{
	return LoadReductPic(fileData, 2);
}
oneObject(resCluster<PicInfo_t *>, CreatePicRes(LoadHalfPic, UnloadPic), GetHalfPicRes);

static PicInfo_t *LoadThirdPic(autoList<uchar> *fileData)
{
	return LoadReductPic(fileData, 3);
}
oneObject(resCluster<PicInfo_t *>, CreatePicRes(LoadThirdPic, UnloadPic), GetThirdPicRes);

static PicInfo_t *LoadQuartPic(autoList<uchar> *fileData)
{
	return LoadReductPic(fileData, 4);
}
oneObject(resCluster<PicInfo_t *>, CreatePicRes(LoadQuartPic, UnloadPic), GetQuartPicRes);

static PicInfo_t *LoadRGBSwapPic(autoList<uchar> *fileData, int rSrc, int gSrc, int bSrc)
{
	int si_h = Pic_FileData2SoftImage(fileData);
	int w;
	int h;

	Pic_GetSoftImageSize(si_h, w, h);

	for(int x = 0; x < w; x++)
	for(int y = 0; y < h; y++)
	{
		Pic_GetSIPixel(si_h, x, y);

		int color[] =
		{
			SI_R,
			SI_G,
			SI_B,
		};

		SI_R = color[rSrc];
		SI_G = color[gSrc];
		SI_B = color[bSrc];

		Pic_SetSIPixel(si_h, x, y);
	}
	return Pic_GraphicHandle2PicInfo(Pic_SoftImage2GraphicHandle(si_h));
}

#define Dfn_RGBPicRes(rgbPtn, rSrc, gSrc, bSrc) \
	static PicInfo_t *Load ## rgbPtn ## Pic(autoList<uchar> *fileData) { \
		return LoadRGBSwapPic(fileData, rSrc, gSrc, bSrc); \
	} \
	oneObject(resCluster<PicInfo_t *>, CreatePicRes(Load ## rgbPtn ## Pic, UnloadPic), Get ## rgbPtn ## PicRes)

Dfn_RGBPicRes(RRR, 0, 0, 0);
Dfn_RGBPicRes(RRG, 0, 0, 1);
Dfn_RGBPicRes(RRB, 0, 0, 2);
Dfn_RGBPicRes(RGR, 0, 1, 0);
Dfn_RGBPicRes(RGG, 0, 1, 1);
//Dfn_RGBPicRes(RGB, 0, 1, 2); // == StdPicRes
Dfn_RGBPicRes(RBR, 0, 2, 0);
Dfn_RGBPicRes(RBG, 0, 2, 1);
Dfn_RGBPicRes(RBB, 0, 2, 2);
Dfn_RGBPicRes(GRR, 1, 0, 0);
Dfn_RGBPicRes(GRG, 1, 0, 1);
Dfn_RGBPicRes(GRB, 1, 0, 2);
Dfn_RGBPicRes(GGR, 1, 1, 0);
Dfn_RGBPicRes(GGG, 1, 1, 1);
Dfn_RGBPicRes(GGB, 1, 1, 2);
Dfn_RGBPicRes(GBR, 1, 2, 0);
Dfn_RGBPicRes(GBG, 1, 2, 1);
Dfn_RGBPicRes(GBB, 1, 2, 2);
Dfn_RGBPicRes(BRR, 2, 0, 0);
Dfn_RGBPicRes(BRG, 2, 0, 1);
Dfn_RGBPicRes(BRB, 2, 0, 2);
Dfn_RGBPicRes(BGR, 2, 1, 0);
Dfn_RGBPicRes(BGG, 2, 1, 1);
Dfn_RGBPicRes(BGB, 2, 1, 2);
Dfn_RGBPicRes(BBR, 2, 2, 0);
Dfn_RGBPicRes(BBG, 2, 2, 1);
Dfn_RGBPicRes(BBB, 2, 2, 2);

#undef Dfn_RGBPicRes

static PicInfo_t *LoadDeepestBlackToTransPic(autoList<uchar> *fileData)
{
	int si_h = Pic_FileData2SoftImage(fileData);
	int w;
	int h;

	Pic_GetSoftImageSize(si_h, w, h);

	for(int x = 0; x < w; x++)
	for(int y = 0; y < h; y++)
	{
		Pic_GetSIPixel(si_h, x, y);

		if(
			SI_R == 0 &&
			SI_G == 0 &&
			SI_B == 0
			)
			SI_A = 0;

		Pic_SetSIPixel(si_h, x, y);
	}
	return Pic_GraphicHandle2PicInfo(Pic_SoftImage2GraphicHandle(si_h));
}
oneObject(resCluster<PicInfo_t *>, CreatePicRes(LoadDeepestBlackToTransPic, UnloadPic), GetDeepestBlackToTransPicRes);

static PicInfo_t *LoadBlackToTransPic(autoList<uchar> *fileData)
{
	int si_h = Pic_FileData2SoftImage(fileData);
	int w;
	int h;

	Pic_GetSoftImageSize(si_h, w, h);

	for(int x = 0; x < w; x++)
	for(int y = 0; y < h; y++)
	{
		Pic_GetSIPixel(si_h, x, y);

		SI_A = SI_R;
		m_minim(SI_A, SI_G);
		m_minim(SI_A, SI_B);

		Pic_SetSIPixel(si_h, x, y);
	}
	return Pic_GraphicHandle2PicInfo(Pic_SoftImage2GraphicHandle(si_h));
}
oneObject(resCluster<PicInfo_t *>, CreatePicRes(LoadBlackToTransPic, UnloadPic), GetBlackToTransPicRes);
