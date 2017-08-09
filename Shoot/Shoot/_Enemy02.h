// ---- JackOLantern ----

typedef struct JackOLantern_st
{
	int ShotType;
	double XRate;
	double YAdd;
	double Rot;
	double RotAdd;

	// <-- by args

	double AxisX;
}
JackOLantern_t;

Enemy_t *Make_JackOLantern(autoList<double> *args, EnemyCommonData_t *ecd);

// ---- BigJackOLantern ----

typedef struct BigJackOLantern_st
{
	int ShotType;
	double R;
	double RApprRate;
	double Rot;
	double RotAdd;
	double XAdd;
	double YAdd;

	// <-- by args

	double AxisX;
	double AxisY;
}
BigJackOLantern_t;

Enemy_t *Make_BigJackOLantern(autoList<double> *args, EnemyCommonData_t *ecd);
