#include "all.h"

GDc_t GDc;

void GameInit(void)
{
	zeroclear(&GDc);

	GDc.PauseRnd = createRnd(GDc.Seed ^ 1100000000);
	GDc.ItemRnd = new Random(GDc.Seed ^ 1200000000);

	// GDc.GH_*, GDc.GSz_*
	{
		autoList<uchar> *fileData = GetEtcRes()->GetHandle(ETC_KOAKUMA_P1);
		int si_h = Pic_FileData2SoftImage(fileData);
		//delete fileData; // äJï˙ÇµÇøÇ·ë ñ⁄Ç∂Ç·Ç»Ç¢Ç©ÅH

		GDc.GH_Laser = MakeMirrorGrphHdl(si_h, 160, 144, 32, 56, &GDc.GSz_Laser);

		for(int c = 0; c < 3; c++)
		{
			GDc.GH_LaserBlast[c] = MakeMirrorGrphHdl(si_h, 128, 0 + 48 * c, 64, 48, GDc.GSz_LaserBlast + c);
			GDc.GH_LaserFire[c]  = MakeMirrorGrphHdl(si_h, 192, 0 + 72 * c, 48, 72, GDc.GSz_LaserFire + c);
		}
	}

	GDc.FieldScreen = CreateSubScreen(FIELD_W, FIELD_H);

	GDc.DE = new taskList();
	GDc.DES = new taskList();
	GDc.DP = new taskList();
	GDc.DPS = new taskList();
	GDc.DI = new taskList();
	GDc.EE = new taskList();
	GDc.EP = new taskList();

	GDc.FieldWallList = new autoList<FieldWall_t *>();
	GDc.PlayerAtariList = new autoList<PlayerAtari_t *>();
	GDc.PlayerShotList = new autoList<PlayerShot_t *>();
	GDc.PlayerShotAtariList = new autoList<PlayerShotAtari_t *>();
	GDc.EnemyList = new autoList<Enemy_t *>();
	GDc.EnemyAtariList = new autoList<EnemyAtari_t *>();
}
void GameFnlz(void)
{
	delete GDc.ScriptFileData;
	releaseList(GDc.ScrRecList, ReleaseScrRec);

	releaseRnd(GDc.PauseRnd);
	delete GDc.ItemRnd;

	// GDc.GH_*
	{
		Pic_ReleaseGraphicHandle(GDc.GH_Laser);

		for(int c = 0; c < 3; c++)
		{
			Pic_ReleaseGraphicHandle(GDc.GH_LaserBlast[c]);
			Pic_ReleaseGraphicHandle(GDc.GH_LaserFire[c]);
		}
	}

	ReleaseSubScreen(GDc.FieldScreen);

	delete GDc.DE;
	delete GDc.DES;
	delete GDc.DP;
	delete GDc.DPS;
	delete GDc.DI;
	delete GDc.EE;
	delete GDc.EP;

	releaseList(GDc.FieldWallList, ReleaseFieldWall);
	releaseList(GDc.PlayerAtariList, ReleasePlayerAtari);
	releaseList(GDc.PlayerShotList, ReleasePlayerShot);
	releaseList(GDc.PlayerShotAtariList, ReleasePlayerShotAtari);
	releaseList(GDc.EnemyList, ReleaseEnemy);
	releaseList(GDc.EnemyAtariList, ReleaseEnemyAtari);

	zeroclear(&GDc);
}
