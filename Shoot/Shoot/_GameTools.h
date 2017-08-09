oneObjectProto(autoList<double>, GetEDL);

int IsOutOfField(double x, double y, double margin = FIELD_H);
int IsOutOfField_LTWH(double l, double t, double w, double h);
int IsOutOfField(PlayerAtari_t *i);
int IsOutOfField(PlayerShotAtari_t *i);
int IsOutOfField(EnemyAtari_t *i);

int GetTamaPicId(int kind, int color);
int GetFairyPicId(int color, int mode, int koma);
int GetBigFairyPicId(int color, int mode, int koma);
int GetOnibiPicId(int color, int koma);

int MakeMirrorGrphHdl(int src_si_h, int l, int t, int w, int h, i2D_t *p_size);
