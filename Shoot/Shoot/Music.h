enum
{
	MUS_DUMMY,

	// app >

	MUS_TITLE,
	MUS_GAMEOVER,
	MUS_STAGE_01,
	MUS_BOSS_01,
	MUS_STAGE_02,
	MUS_BOSS_02,
	MUS_EXTRA_STAGE,
	MUS_EXTRA_BOSS,

	// < app

	MUS_MAX, // num of member
};

typedef struct MusicInfo_st
{
	int Handle;
	double Volume; // 0.0 - 1.0, def: 0.5
}
MusicInfo_t;

extern MusicInfo_t *CurrDestMusic;
extern double CurrDestMusicVolumeRate;

void MusicEachFrame(void);
void MusicPlay(int musId, int once_mode = 0, int resume_mode = 0, double volumeRate = 1.0, int fadeFrameMax = 30);
void MusicFade(int frameMax = 30, double destVRate = 0.0, double startVRate = CurrDestMusicVolumeRate);
void MusicStop(void);
void MusicTouch(int musId);
void UpdateMusicVolume(void);
