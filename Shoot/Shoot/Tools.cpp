#include "all.h"

double toDouble(char *line)
{
	int numer = 0;
	int denom = 0;
	int minus = 0;

	for(char *p = line; *p; p++)
	{
		if('0' <= *p && *p <= '9')
		{
			if(
				IMAX / 10 < numer ||
				IMAX / 10 < denom
				)
				break; // overflow -> 打ち切り

			numer *= 10;
			numer += *p - '0';
			denom *= 10;
		}
		else if(*p == '.')
		{
			denom = 1;
		}
		else if(*p == '-')
		{
			minus = 1;
		}
	}
	if(!denom)
		denom = 1;

	return (double)numer / denom * (minus ? -1 : 1);
}
int d2i(double value)
{
	return (int)(value + (value < 0.0 ? -0.5 : 0.5));
}
char *xcout(char *format, ...)
{
	char *buffer;
	va_list marker;

	va_start(marker, format);

	for(int size = strlen(format) + 128; ; size *= 2)
	{
		errorCase(IMAX < size);

		buffer = (char *)memAlloc(size + 20);
		int retval = _vsnprintf(buffer, size + 10, format, marker);
		buffer[size + 10] = '\0';

		if(0 <= retval && retval <= size)
			break;

		memFree(buffer);
	}
	va_end(marker);

	return buffer;
}
char *strx(char *line)
{
	return (char *)memClone(line, strlen(line) + 1);
}

#define POUND_FIRST_DELAY 17
#define POUND_DELAY 4

int isPound(int counter)
{
	return (counter) == 1 || POUND_FIRST_DELAY < (counter) && ((counter) - POUND_FIRST_DELAY) % POUND_DELAY == 1;
}
int atoi_x(char *line)
{
	int value = atoi(line);
	memFree(line);
	return value;
}
autoList<char *> *tokenize(char *line, char *delimiters)
{
	autoList<char *> *tokens = new autoList<char *>();
	autoList<char> *token = new autoList<char>();

	for(char *p = line; *p; p++)
	{
		char *d;

		for(d = delimiters; *d; d++)
			if(*d == *p)
				break;

		if(*d)
		{
			token->AddElement('\0');
			tokens->AddElement(token->UnbindBuffer());
		}
		else
			token->AddElement(*p);
	}
	token->AddElement('\0');
	tokens->AddElement(token->UnbindBuffer());

	delete token;
	return tokens;
}

int getZero(void)
{
	return 0;
}
uint getUIZero(void)
{
	return 0;
}
__int64 getI64Zero(void)
{
	return 0;
}
void noop(void)
{
	1; // noop
}
void noop_i(int dummy)
{
	1; // noop
}
void noop_ui(uint dummy)
{
	1; // noop
}
void noop_i64(__int64 dummy)
{
	1; // noop
}

i2D_t makeI2D(int x, int y)
{
	i2D_t pos;

	pos.X = x;
	pos.Y = y;

	return pos;
}
d2D_t makeD2D(double x, double y)
{
	d2D_t pos;

	pos.X = x;
	pos.Y = y;

	return pos;
}

bitList *createBitList(void)
{
	return new bitList();
}
void releaseBitList(bitList *bl)
{
	delete bl;
}

void my_memset(void *block, int fillValue, int size)
{
	for(int index = 0; index < size; index++)
	{
		((uchar *)block)[index] = fillValue;
	}
}

int isSame(autoList<uchar> *binData1, autoList<uchar> *binData2)
{
	if(binData1->GetCount() != binData2->GetCount())
		return 0;

	for(int index = 0; index < binData1->GetCount(); index++)
		if(binData1->GetElement(index) != binData2->GetElement(index))
			return 0;

	return 1;
}
int isFar(int x1, int y1, int x2, int y2, int r)
{
	return m_pow((__int64)r) < m_pow((__int64)x1 - x2) + m_pow((__int64)y1 - y2);
}
int isFar(double x1, double y1, double x2, double y2, double r)
{
	return m_pow(r) < m_pow(x1 - x2) + m_pow(y1 - y2);
}
/*
	ret: ? 矩形(l, t, w, h), 円(x, y, r) は接触している。
*/
int isCrashedRectCircle(double l, double t, double w, double h, double x, double y, double r)
{
	if(
		m_isRange(x, l - r, l + w + r) &&
		m_isRange(y, t - r, t + h + r)
		)
	{
		if(
			m_isRange(x, l, l + w) ||
			m_isRange(y, t, t + h)
			)
		{
			return 1;
		}

		double edgeX;
		double edgeY;

		if(x < l + w / 2.0) // 左
		{
			edgeX = l;
		}
		else // 右
		{
			edgeX = l + w;
		}
		if(y < t + h / 2.0) // 上
		{
			edgeY = t;
		}
		else // 下
		{
			edgeY = t + h;
		}
		if(!isFar(
			x,
			y,
			edgeX,
			edgeY,
			r
			))
		{
			return 1;
		}
	}
	return 0;
}

double getAngle(double x, double y)
{
	if(y < 0.0) return PI * 2.0 - getAngle( x, -y);
	if(x < 0.0) return PI * 1.0 - getAngle(-x,  y);

	if(x == 0.0) return PI / 2.0;
	if(y == 0.0) return 0.0;

	double r1 = 0.0;
	double r2 = 0.5 * PI;
	double rm;
	double t = y / x;

	for(int count = 10; ; count--) // 10回で、およそ 0.000767 以下の誤差になる。
	{
		rm = (r1 + r2) / 2.0;

		if(!count)
			break;

		if(t < tan(rm))
			r2 = rm;
		else
			r1 = rm;
	}
	return rm;
}
double getAngle(double x, double y, double originX, double originY)
{
	return getAngle(x - originX, y - originY);
}
void rotatePos(double rot, double &x, double &y)
{
	double w;

	w = x * cos(rot) - y * sin(rot);
	y = x * sin(rot) + y * cos(rot);
	x = w;
}
void rotatePos(double rot, double &x, double &y, double originX, double originY)
{
	x -= originX;
	y -= originY;

	rotatePos(rot, x, y);

	x += originX;
	y += originY;
}

void MakeXYSpeed(double x, double y, double targetX, double targetY, double speed, double &speedX, double &speedY)
{
	speedX = targetX - x;
	speedY = targetY - y;

	double distance = m_hypot(speedX, speedY);
	
	if(distance < MICRO)
	{
		speedX = speed;
		speedY = 0.0;
	}
	else
	{
		double rate = speed / distance;

		speedX *= rate;
		speedY *= rate;
	}
}
