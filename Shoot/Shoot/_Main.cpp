#include "all.h"

void ProcMain(void)
{
#if 1 // test
	GameInit();

	GDc.Zanki = 3;
	GDc.ZanBomb = 2;
//	GDc.ScriptFile = "..\\..\\res\\Script\\0001.csv";
	GDc.ScriptFileData = GetEtcRes()->GetHandle(ETC_SCRIPT_0001);

	GameMain();
	GameFnlz();
#elif 0 // test
	error(); // HACK
#else
	error(); // HACK
#endif
}
