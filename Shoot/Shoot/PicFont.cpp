#include "all.h"

static char *GetFontDir(void)
{
	static char *dir;

	if(!dir)
	{
		dir = "Font";

		if(!accessible(dir))
			dir = "..\\..\\res\\Font";
	}
	return dir;
}

FontFile_t *AddFontFile(char *fontLocalFile)
{
	errorCase(m_isEmpty(fontLocalFile));
	char *fontFile = xcout("%s\\%s", GetFontDir(), fontLocalFile);
	LOG("AddFontResourceEx ST %u\n", (uint)time(NULL));
	errorCase(!AddFontResourceEx(fontFile, FR_PRIVATE, NULL)); // ? Ž¸”s
	LOG("AddFontResourceEx ED %u\n", (uint)time(NULL));

	FontFile_t *ff = nb(FontFile_t);
	ff->File = fontFile;
	return ff;
}
void RemoveFontFile(FontFile_t *ff)
{
	errorCase(!ff);
	errorCase(!RemoveFontResourceEx(ff->File, FR_PRIVATE, NULL)); // ? Ž¸”s

	memFree(ff->File);
	memFree(ff);
}

/*
	fontThick: 1`9, def=6 @ SetFontThickness()
*/
FontHandle_t *CreateFontHandle(char *fontName, int fontSize, int fontThick, int antiAliasing, int edgeSize, int italicFlag)
{
	errorCase(m_isEmpty(fontName));
	errorCase(!m_isRange(fontSize, 1, IMAX));
	errorCase(!m_isRange(fontThick, 1, 9));
	// antiAliasing
	errorCase(!m_isRange(edgeSize, 0, IMAX));
	// italicFlag
	
	int h = CreateFontToHandle(
		fontName,
		fontSize,
		fontThick,
		antiAliasing ? DX_FONTTYPE_ANTIALIASING_8X8 : DX_FONTTYPE_NORMAL,
		-1,
		edgeSize
		);

	errorCase(h == -1); // ? Ž¸”s

	FontHandle_t *fh = nb(FontHandle_t);
	fh->Handle = h;
	fh->FontName = strx(fontName);
	fh->FontSize = fontSize;
	fh->FontThick = fontThick;
	fh->AntiAliasing = antiAliasing;
	fh->EdgeSize = edgeSize;
	fh->ItalicFlag = italicFlag;
	return fh;
}
void ReleaseFontHandle(FontHandle_t *fh)
{
	if(!fh)
		return;

	errorCase(DeleteFontToHandle(fh->Handle)); // ? Ž¸”s
	memFree(fh->FontName);
	memFree(fh);
}

// >>>

static oneObject(autoList<FontHandle_t *>, new autoList<FontHandle_t *>(), GetFontHandleList);

FontHandle_t *GetFontHandle(char *fontName, int fontSize, int fontThick, int antiAliasing, int edgeSize, int italicFlag)
{
	errorCase(!fontName);

	FontHandle_t *fh;

	for(int index = 0; index < GetFontHandleList()->GetCount(); index++)
	{
		fh = GetFontHandleList()->GetElement(index);

		if(
			!strcmp(fh->FontName, fontName) &&
			fh->FontSize == fontSize &&
			fh->FontThick == fontThick &&
			(fh->AntiAliasing ? antiAliasing : !antiAliasing) &&
			fh->EdgeSize == edgeSize &&
			(fh->ItalicFlag ? italicFlag : !italicFlag)
			)
		{
			goto found;
		}
	}
	fh = CreateFontHandle(fontName, fontSize, fontThick, antiAliasing, edgeSize, italicFlag);
	GetFontHandleList()->AddElement(fh);
found:
	return fh;
}
void ReleaseAllFontHandle(void)
{
	while(GetFontHandleList()->GetCount())
	{
		ReleaseFontHandle(GetFontHandleList()->UnaddElement());
	}
}

// <<<

SubScreen_t *CreatePicFont(int chr, FontHandle_t *fh, int margin, int tategakiFlag, int color, int edgeColor)
{
	errorCase(!isJChar(chr));
	errorCase(!fh);
	errorCase(!m_isRange(margin, 0, IMAX));

	int wh = fh->FontSize + fh->EdgeSize * 2 + margin * 2;

	SubScreen_t *ss = CreateSubScreen(wh, wh, 1);
	char ptn[3];

	if(chr <= 0xff)
	{
		ptn[0] = chr;
		ptn[1] = '\0';
	}
	else
	{
		ptn[0] = chr >> 8 & 0xff;
		ptn[1] = chr >> 0 & 0xff;
		ptn[2] = '\0';
	}

	ChangeDrawScreen(ss);
	DrawStringToHandle(margin, margin, ptn, color, fh->Handle, edgeColor, tategakiFlag);
	RestoreDrawScreen();

	return ss;
}
