typedef struct FontFile_st
{
	char *File;
}
FontFile_t;

FontFile_t *AddFontFile(char *fontLocalFile);
void RemoveFontFile(FontFile_t *ff);

typedef struct FontHandle_st
{
	int Handle;
	char *FontName;
	int FontSize;
	int FontThick;
	int AntiAliasing;
	int EdgeSize;
	int ItalicFlag;
}
FontHandle_t;

FontHandle_t *CreateFontHandle(char *fontName, int fontSize, int fontThick = 6, int antiAliasing = 1, int edgeSize = 0, int italicFlag = 0);
void ReleaseFontHandle(FontHandle_t *fh);

FontHandle_t *GetFontHandle(char *fontName, int fontSize, int fontThick, int antiAliasing, int edgeSize, int italicFlag);
void ReleaseAllFontHandle(void);

SubScreen_t *CreatePicFont(int chr, FontHandle_t *fh, int margin = 0, int tategakiFlag = 0, int color = GetColor(255, 255, 255), int edgeColor = GetColor(0, 0, 0));
