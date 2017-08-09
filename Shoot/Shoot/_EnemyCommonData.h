typedef struct EnemyCommonData_st
{
	/*
		Enemy_t に対応するフィールドがあるので、コメントはそちらに...
	*/

	int Kind;
	int HP;
	int TransFrame;
	double X;
	double Y;
	int DropItemType;
}
EnemyCommonData_t;

EnemyCommonData_t *GetECD(int kind, int hp, int transFrame, double x, double y, int dit);
EnemyCommonData_t *DuplexEnemyCommonData(EnemyCommonData_t *i);
void ReleaseEnemyCommonData(EnemyCommonData_t *i);

// <-- cdtor

// <-- accessor
