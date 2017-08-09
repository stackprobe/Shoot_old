double toDouble(char *line);
int d2i(double value);
char *xcout(char *format, ...);
char *strx(char *line);
int isPound(int counter);
int atoi_x(char *line);
autoList<char *> *tokenize(char *line, char *delimiters);

template <class Var_t>
void t_swap(Var_t &a, Var_t &b)
{
	Var_t tmp = a;
	a = b;
	b = tmp;
}

int getZero(void);
uint getUIZero(void);
__int64 getI64Zero(void);
void noop(void);
void noop_i(int dummy);
void noop_ui(uint dummy);
void noop_i64(__int64 dummy);

i2D_t makeI2D(int x, int y);
d2D_t makeD2D(double x, double y);

bitList *createBitList(void);
void releaseBitList(bitList *bl);

void my_memset(void *block, int fillValue, int size);

template <class Var_t>
void zeroclear(Var_t *var, int num = 1)
{
	my_memset(var, 0x00, num * sizeof(Var_t));
}

template <class Deletable_t>
void callDelete(Deletable_t *i)
{
	delete i;
}

template <class Deletable_t>
void deleteList(autoList<Deletable_t> *list)
{
	list->CallAllElement(callDelete);
	delete list;
}

template <class Var_t>
int isPointNull(Var_t **vpp)
{
	return !*vpp;
}

int isSame(autoList<uchar> *binData1, autoList<uchar> *binData2);
int isFar(int x1, int y1, int x2, int y2, int r);
int isFar(double x1, double y1, double x2, double y2, double r);
int isCrashedRectCircle(double l, double t, double w, double h, double x, double y, double r);

double getAngle(double x, double y);
double getAngle(double x, double y, double originX, double originY);
void rotatePos(double rot, double &x, double &y);
void rotatePos(double rot, double &x, double &y, double originX, double originY);

void MakeXYSpeed(double x, double y, double targetX, double targetY, double speed, double &speedX, double &speedY);
