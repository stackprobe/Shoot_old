#include "all.h"

static void AddItem(double x, double y, int kind)
{
	static autoList<double> *args;

	if(!args)
		args = new autoList<double>();

	args->Clear();
	args->AddElement((double)kind);

	AddEnemy(Make_I01(args, GetECD(EK_ITEM, 0, 0, x, y, 0)));
}
static void DropItem(Enemy_t *i, int kind, int num = 1, double rMin = 0.0, double rBnd = 0.0)
{
	if(num == 1)
	{
		AddItem(i->X, i->Y, kind);
	}
	else
	{
		Enemy_t **addedItems = (Enemy_t **)memAlloc_NC(sizeof(Enemy_t *) * num);

		for(int c = 0; c < num; c++)
		{
			double rot = GDc.ItemRnd->DRnd() * PI * 2.0;
			double r = rMin + GDc.ItemRnd->DRnd() * rBnd;

			AddItem(
				i->X + cos(rot) * r,
				i->Y + sin(rot) * r,
				kind
				);

			addedItems[c] = GetLastAddedEnemy();
		}

		/*
			重なっているアイテムを離す。
		*/
		for(int c = 0; c < 3; c++)
		for(int i = 1; i < num; i++)
		for(int j = 0; j < i; j++)
		{
			Enemy_t *iai = addedItems[i];
			Enemy_t *jai = addedItems[j];

			if(!isFar(
				iai->X,
				iai->Y,
				jai->X,
				jai->Y,
				10.0
				))
			{
				double jax;
				double jay;

				MakeXYSpeed(iai->X, iai->Y, jai->X, jai->Y, 5.0, jax, jay);

				iai->X -= jax;
				iai->Y -= jay;
				jai->X += jax;
				jai->Y += jay;
			}
		}

		memFree(addedItems);
	}
}
void DropItem(Enemy_t *i)
{
	switch(i->DropItemType)
	{
	case 0:
		break;

	case 1:
		DropItem(i, IK_STAR);
		break;

	case 2:
		DropItem(i, IK_CANDY);
		break;

	case 3:
		DropItem(i, IK_HEART);
		break;

	case 4:
		DropItem(i, IK_BOMB);
		break;

	case 11:
		DropItem(i, IK_STAR, 10, 20.0, 80.0);
		break;

	case 12:
		DropItem(i, IK_CANDY, 10, 20.0, 80.0);
		break;

	case 21:
		DropItem(i, IK_STAR, 20, 20.0, 110.0);
		break;

	case 22:
		DropItem(i, IK_CANDY, 20, 20.0, 110.0);
		break;

	default:
		error();
	}
}
