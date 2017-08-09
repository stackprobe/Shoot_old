#include "all.h"

EnemyAtari_t *CreateEnemyAtari(Enemy_t *owner, double x, double y, double r)
{
	errorCase(!owner);
	// x
	// y
	errorCase(r < 1.0);

	EnemyAtari_t *i = nb(EnemyAtari_t);

	i->Kind = EAK_CIRCLE;
	i->Owner = owner;
	i->u.Circle.X = x;
	i->u.Circle.Y = y;
	i->u.Circle.R = r;

	return i;
}
EnemyAtari_t *CreateEnemyAtari_Rect(Enemy_t *owner, double l, double t, double w, double h)
{
	errorCase(!owner);
	// l
	// t
	errorCase(w < 1.0);
	errorCase(h < 1.0);

	EnemyAtari_t *i = nb(EnemyAtari_t);

	i->Kind = EAK_RECT;
	i->Owner = owner;
	i->u.Rect.L = l;
	i->u.Rect.T = t;
	i->u.Rect.W = w;
	i->u.Rect.H = h;
}
void ReleaseEnemyAtari(EnemyAtari_t *i)
{
	memFree(i);
}

// <-- cdtor

int IsTrans(EnemyAtari_t *i)
{
	return IsTrans(i->Owner);
}

// <-- accessor
