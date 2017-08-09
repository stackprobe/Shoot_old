enum // EnemyAtariKind
{
	EAK_CIRCLE,
	EAK_RECT,

	EAK_MAX, // num of member
};

typedef struct EnemyAtari_st
{
	int Kind; // EAK_*
	Enemy_t *Owner;

	union
	{
		struct
		{
			double X;
			double Y;
			double R;
		}
		Circle;

		struct
		{
			double L;
			double T;
			double W;
			double H;
		}
		Rect;
	}
	u;
}
EnemyAtari_t;

EnemyAtari_t *CreateEnemyAtari(Enemy_t *owner, double x, double y, double r);
EnemyAtari_t *CreateEnemyAtari_Rect(Enemy_t *owner, double l, double t, double w, double h);
void ReleaseEnemyAtari(EnemyAtari_t *i);

// <-- cdtor

int IsTrans(EnemyAtari_t *i);

// <-- accessor
