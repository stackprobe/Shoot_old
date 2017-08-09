// ---- E01 ----

typedef struct E01_st
{
	int FEKind; // fairy etc kind
	int ShotType;
	double Speed;
	int XDir; // -1 == ç∂Ç÷, 1 == âEÇ÷
	double MaxY;
	double ApprRate;

	// <-- by args
}
E01_t;

Enemy_t *Make_E01(autoList<double> *args, EnemyCommonData_t *ecd);

// ---- E02 ----

typedef struct E02_st
{
	int FEKind;
	int ShotType;
	double PrmTargetX;
	double PrmTargetY;
	double ApprRate;
	double XAdd;
	double YAdd;

	// <-- by args
}
E02_t;

Enemy_t *Make_E02(autoList<double> *args, EnemyCommonData_t *ecd);

// ---- E03 ----

typedef struct E03_st
{
	int FEKind;
	int ShotType;
	double PrmTargetX;
	double PrmTargetY;
	double EvacFrame;
	double EvacXAdd;
	double EvacYAdd;

	// <-- by args
}
E03_t;

Enemy_t *Make_E03(autoList<double> *args, EnemyCommonData_t *ecd);
