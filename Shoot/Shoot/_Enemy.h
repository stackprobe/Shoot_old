typedef struct Enemy_st
{
	int (*EachFrameFunc)(struct Enemy_st *, void *); // ret: ? dead
	/*
		�������ɔj�󂳂ꂽ�ꍇ�������ꂽ�ꍇ�̂ݎ��s����B
		��ʊO�ɏo��Ȃ� EachFrameFunc() �� 1 ��Ԃ����ꍇ�͌Ă΂�Ȃ����Ƃɒ��ӁI
	*/
	void (*DeadEventFunc)(struct Enemy_st *, void *);
	void (*ReleaseExtraDataFunc)(struct Enemy_st *, void *);
	void *ExtraData;
	int Kind; // EK_*
	int HP; // 0 == ���G
	int TransFrame; // OnFieldFrame < TransFrame �Ȃ�΁A���G
	double X;
	double Y;
	double TargetX;
	double TargetY;
	int DropItemType;

	// <-- init @ ctor

	// <-- init @ just after ctor

	int Frame;
	int OnFieldFrame; // �t�B�[���h�ɓ����Ă�����Z, �t�B�[���h���o�Ă����Z�������邱�Ƃɒ��ӁI
	int DeadFlag;

	union
	{
		struct
		{
			double LastX;
			int XMoveCount; // <0 == ������, 0 == ���ʌ���, 0< == �E����
			double UntransRate;
		}
		Fairy; // Fairy + BigFairy
	}
	u;
}
Enemy_t;

Enemy_t *CreateEnemy_ved(
	int (*eachFrameFunc)(Enemy_t *, void *),
	void (*deadEventFunc)(Enemy_t *, void *),
	void (*releaseExtraDataFunc)(Enemy_t *, void *),
	void *extraData,
	EnemyCommonData_st *ecd
	);
void ReleaseEnemy(Enemy_t *i);

template <class ExtraData_t>
Enemy_t *CreateEnemy(
	int (*eachFrameFunc)(Enemy_t *, ExtraData_t *),
	void (*deadEventFunc)(Enemy_t *, ExtraData_t *),
	void (*releaseExtraDataFunc)(Enemy_t *, ExtraData_t *),
	ExtraData_t *extraData,
	EnemyCommonData_st *ecd
	)
{
	if(!extraData)
		extraData = nb(ExtraData_t);

	return CreateEnemy_ved(
		(int (*)(Enemy_t *, void *))eachFrameFunc,
		(void (*)(Enemy_t *, void *))deadEventFunc,
		(void (*)(Enemy_t *, void *))releaseExtraDataFunc,
		(void *)extraData,
		ecd
		);
}

// <-- cdtor

int IsTrans(Enemy_t *i);

// <-- accessor

void AllEnemyEachFrame(void);
void AddEnemy(Enemy_t *i);
Enemy_t *GetLastAddedEnemy(void);
double nextArg_d(autoList<double> *args, int &rIndex, double minval, double maxval);
int nextArg_i(autoList<double> *args, int &rIndex, int minval, int maxval);
void CommonEnemyDeadProc(Enemy_t *i);
