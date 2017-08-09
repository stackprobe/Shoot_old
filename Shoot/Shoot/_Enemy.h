typedef struct Enemy_st
{
	int (*EachFrameFunc)(struct Enemy_st *, void *); // ret: ? dead
	/*
		小悪魔に破壊された場合や回収された場合のみ実行する。
		画面外に出るなど EachFrameFunc() が 1 を返した場合は呼ばれないことに注意！
	*/
	void (*DeadEventFunc)(struct Enemy_st *, void *);
	void (*ReleaseExtraDataFunc)(struct Enemy_st *, void *);
	void *ExtraData;
	int Kind; // EK_*
	int HP; // 0 == 無敵
	int TransFrame; // OnFieldFrame < TransFrame ならば、無敵
	double X;
	double Y;
	double TargetX;
	double TargetY;
	int DropItemType;

	// <-- init @ ctor

	// <-- init @ just after ctor

	int Frame;
	int OnFieldFrame; // フィールドに入ってから加算, フィールドを出ても加算し続けることに注意！
	int DeadFlag;

	union
	{
		struct
		{
			double LastX;
			int XMoveCount; // <0 == 左向く, 0 == 正面向く, 0< == 右向く
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
