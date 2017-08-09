// ---- I01 ----

typedef struct I01_st
{
	int Kind;

	double YAdd;
	double Rot;
	double RotAdd;

	int VacuumFlag; // 0 == off, 1 == on, 2 == fast
}
I01_t;

Enemy_t *Make_I01(autoList<double> *args, EnemyCommonData_t *ecd);
