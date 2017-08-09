// ---- ES01 ----

typedef struct ES01_st
{
	int Kind;
	int Color;
	double Speed;
	double Angle;

	int PicId;
	double R;
	double XAdd;
	double YAdd;
}
ES01_t;

Enemy_t *Make_ES01(autoList<double> *args, EnemyCommonData_t *ecd);
Enemy_t *Make_ES01(int kind, int color, double speed, double x, double y, double angle = 0.0);
