#include "all.h"

void CommonEnemyShotEachFrame(Enemy_t *i, int shotType)
{
	if(IsOutOfField(i->X, i->Y))
		return;

	switch(shotType)
	{
	case 0: // ショット無し
		break;

	case 100: // 自機狙い_Normal_W
	case 101: // 自機狙い_Normal_R
		{
			int frm = i->OnFieldFrame;
			int cyc = 10;
			int div = frm / cyc;
			int mod = frm % cyc;

			if(!mod && m_isRange(div, 3, 12))
			{
				int color;

				switch(shotType)
				{
				case 100: color = TC_WHITE; break;
				case 101: color = TC_RED; break;

				default:
					error();
				}
				AddEnemy(Make_ES01(TK_NORMAL, color, 4.0, i->X, i->Y));
			}
		}
		break;

	case 200: // 三角形_Normal_W
		{
			int frm = i->OnFieldFrame;
			int cyc = 5;
			int div = frm / cyc;
			int mod = frm % cyc;

			div -= 10;
			div %= 15;

			if(!mod && m_isRange(div, 0, 5))
			{
				int color;

				switch(shotType)
				{
				case 200: color = TC_WHITE; break;

				default:
					error();
				}

				{
					for(int c = 0; c <= div; c++)
					{
						double angleStep = 0.1;
						double angle = c * angleStep - div * angleStep / 2.0;

						AddEnemy(Make_ES01(TK_NORMAL, color, 5.0, i->X, i->Y, angle));
					}
				}
			}
		}
		break;

	default:
		error();
	}
}
