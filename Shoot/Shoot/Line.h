void strz(char *&buffer, char *line);
void strz_x(char *&buffer, char *line);

char *getNullString(void);
char *getConstNullString(void);

void unctrl(char *str);
void my_strcpy(char *w, char *r);

void trimLead(char *line, int chr = ' ');
void trimTrail(char *line, int chr = ' ');
void trimEdge(char *line, int chr = ' ');
void trimSequ(char *line, int delimChr = ' ');
void trim(char *line, int chr = ' ');
