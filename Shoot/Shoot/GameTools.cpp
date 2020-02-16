#include "all.h"

static oneObject(autoList<int>, new autoList<int>(), GetSceneStack);

int sc_numer;
int sc_denom;
double sc_rate;

void sceneEnter(void)
{
	GetSceneStack()->AddElement(sc_numer);
	GetSceneStack()->AddElement(sc_denom);
}
void sceneLeave(void)
{
	sc_denom = GetSceneStack()->UnaddElement();
	sc_numer = GetSceneStack()->UnaddElement();
	sc_rate = (double)sc_numer / sc_denom;
}

// ---- Curtain ----

static oneObject(autoQueue<double>, new autoQueue<double>(), GetCurtainQueue);

double CurrCurtainWhiteLevel;
int LastCurtainFrame = -1;

void CurtainEachFrame(int oncePerFrame)
{
	if(oncePerFrame)
	{
		if(ProcFrame <= LastCurtainFrame)
			return;

		LastCurtainFrame = ProcFrame;
	}
	double wl = GetCurtainQueue()->Dequeue(CurrCurtainWhiteLevel);

	m_range(wl, -1.0, 1.0); // 2bs

	CurrCurtainWhiteLevel = wl;

	if(wl == 0.0)
		return;

	int darkMode;

	if(wl < 0.0)
	{
		wl = abs(wl);
		darkMode = 1;
	}
	else
		darkMode = 0;

	DPE_SetAlpha(wl);

	if(darkMode)
		DPE_SetBright(0.0, 0.0, 0.0);

	DrawRect(P_WHITEBOX, 0.0, 0.0, (double)SCREEN_W, (double)SCREEN_H);
	DPE_Reset();
}
void SetCurtain(int frameMax, double destWhiteLevel, double startWhiteLevel)
{
	m_range(frameMax, 0, 3600); // 0 frame - 1 min
	m_range(destWhiteLevel, -1.0, 1.0);
	m_range(startWhiteLevel, -1.0, 1.0);

	GetCurtainQueue()->Clear();

	if(!frameMax)
	{
		GetCurtainQueue()->Enqueue(destWhiteLevel);
		return;
	}
	for(int frmcnt = 0; frmcnt <= frameMax; frmcnt++)
	{
		double wl;

		if(!frmcnt)
			wl = startWhiteLevel;
		else if(frmcnt == frameMax)
			wl = destWhiteLevel;
		else
			wl = startWhiteLevel + (destWhiteLevel - startWhiteLevel) * ((double)frmcnt / frameMax);

		GetCurtainQueue()->Enqueue(wl);
	}
}

// ---- Print ----

PrintExtra_t PE;

typedef struct PrintInfo_st
{
	int X;
	int Y;
	char *Token;
	PrintExtra_t Extra;
}
PrintInfo_t;

void PE_Border(int color)
{
	PE.Border = 1;
	PE.BorderColor = color;
}
void PE_Reset(void)
{
	memset(&PE, 0x00, sizeof(PrintExtra_t));
	PE.Color = GetColor(255, 255, 255);
}

static int PrintFunc(PrintInfo_t *i)
{
	if(i->Extra.Border)
	{
		for(int xc = -1; xc <= 1; xc++)
		for(int yc = -1; yc <= 1; yc++)
		{
			DrawString(i->X + xc, i->Y + yc, i->Token, i->Extra.BorderColor);
		}
	}
	DrawString(i->X, i->Y, i->Token, i->Extra.Color);
	return 0;
}
static void ReleasePrintInfo(PrintInfo_t *i)
{
	memFree(i->Token);
	memFree(i);
}
static int P_BaseX;
static int P_BaseY;
static int P_YStep;
static int P_X;
static int P_Y;

void SetPrint(int x, int y, int yStep)
{
	errorCase(x < -IMAX || IMAX < x);
	errorCase(y < -IMAX || IMAX < y);
	errorCase(yStep < 0 || IMAX < yStep);

	P_BaseX = x;
	P_BaseY = y;
	P_YStep = yStep;
	P_X = 0;
	P_Y = 0;
}
void PrintRet(void)
{
	P_X = 0;
	P_Y += P_YStep;
}
void Print(char *token)
{
	Print_x(strx(token));
}
void Print_x(char *token)
{
	PrintInfo_t *i = nb_(PrintInfo_t);

	i->X = P_BaseX + P_X;
	i->Y = P_BaseY + P_Y;
	i->Token = token; // bind
	i->Extra = PE;

	if(!PE.TL)
	{
		PrintFunc(i);
		ReleasePrintInfo(i);
	}
	else
		AddTask(PE.TL, 0, PrintFunc, i, ReleasePrintInfo);

	int w = GetDrawStringWidth(token, strlen(token));
	errorCase(w < 0 || IMAX < w);
	P_X += w;
}

// ----

void DrawCurtain(double whiteLevel)
{
	m_range(whiteLevel, -1.0, 1.0);

	if(whiteLevel < 0.0)
	{
		DPE_SetAlpha(-whiteLevel);
		DPE_SetBright(0.0, 0.0, 0.0);
	}
	else
		DPE_SetAlpha(whiteLevel);

	DrawRect(P_WHITEBOX, 0, 0, SCREEN_W, SCREEN_H);
	DPE_Reset();
}
