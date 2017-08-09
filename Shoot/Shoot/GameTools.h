extern int sc_numer; // 0 - sc_denom
extern int sc_denom; // 1 - *
extern double sc_rate; // 0.0 - 1.0

void sceneEnter(void);
void sceneLeave(void);

/*
ex.
	forscene(100)
	{
		// sc_numer == (0 - 100), 101 �񏈗������B
		EachFrame();
	}
	sceneLeave();

����
	forscene �u���b�N������ return ����Ƃ��� sceneLeave(); ���邱�ƁB

	ex.
		forscene(123)
		{
			...
			if(...)
			{
				sceneLeave();
				return;
			}
			...
		}
		sceneLeave();
*/
// frameMax: (1 �` *)
#define forscene(frameMax) \
	for(sceneEnter(), sc_denom = (frameMax), sc_numer = 0; sc_numer <= (frameMax) && (sc_rate = (double)sc_numer / sc_denom, 1); sc_numer++)

/*
ex.
	ifsceneBegin(60, count)
	{
		// count == (0 - 60), sc_numer == (0 - 60), 61 �񏈗������B
		EachFrame();
	}
	ifscene(90)
	{
		// count == (61 - 151), sc_numer == (0 - 90), 91 �񏈗������B
		EachFrame();
	}
	ifscene(50)
	{
		// count == (152 - 202), sc_numer == (0 - 50), 51 �񏈗������B
		EachFrame();
	}
	ifsceneEnd
	{
		// count == (203 - *), sc_numer == (0 - *)
		EachFrame();
	}
	sceneLeave();

�V�[�P���X
	ifsceneBegin (1) -> ifscene (0*) -> ifsceneEnd (0*1) -> sceneLeave (1)

����
	ifsceneBegin, ifscene, ifsceneEnd �u���b�N������ continue, break, return ����Ƃ��� sceneLeave(); ���邱�ƁB

	ex.
		...
		ifsceneEnd
		{
			sceneLeave();
			continue; // break, return
		}
		sceneLeave();
*/
// frameMax: (1 �` *), count: (0 �` *)
#define ifsceneBegin(frameMax, count) \
	if(sceneEnter(), sc_numer = (count), 0) { } ifscene((frameMax))

// frameMax: (1 �` *)
#define ifscene(frameMax) \
	else if(sc_numer <= (frameMax) ? (sc_denom = (frameMax), sc_rate = (double)sc_numer / sc_denom, 1) : (sc_numer -= (frameMax) + 1, 0))

#define ifsceneEnd \
	else

// ---- Curtain ----

extern double CurrCurtainWhiteLevel;

void CurtainEachFrame(int oncePerFrame = 1);
void SetCurtain(int frameMax = 30, double destWhiteLevel = 0.0, double startWhiteLevel = CurrCurtainWhiteLevel);

// ---- Print ----

typedef struct PrintExtra_st
{
	taskList *TL;
	int Color;

	// wrapped by PE_* -->

	int Border; // 0 == ����
	int BorderColor;
}
PrintExtra_t;

extern PrintExtra_t PE;

void PE_Border(int color = GetColor(0, 0, 0));
void PE_Reset(void);

void SetPrint(int x = 0, int y = 0, int yStep = 16);
void PrintRet(void);
void Print(char *token);
void Print_x(char *token);

// ----

void DrawCurtain(double whiteLevel = -1.0);
