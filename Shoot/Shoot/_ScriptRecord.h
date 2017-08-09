typedef struct ScrRec_st
{
	int Frame;
	int EventId;
	int SubId;
	autoList<double> *Args;
	EnemyCommonData_t *EnemyCommonData;

	// <-- init @ just after ctor
}
ScrRec_t;

ScrRec_t *CreateScrRec(void);
void ReleaseScrRec(ScrRec_t *i);

// <-- cdtor

// <-- accessor
