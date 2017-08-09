#include "all.h"

autoTable<char *> *readCsvFile(autoList<uchar> *fileData)
{
	autoList<char> *cellBuff = new autoList<char>();
	autoTable<char *> *table = new autoTable<char *>((char *(*)(void))getZero, (void (*)(char *))memFree);
	int rIndex = 0;
	int rowidx = 0;
	int colidx = 0;
	int chr;

	while((chr = readChar(fileData, rIndex)) != EOF)
	{
		if(chr == '\"')
		{
			for(; ; )
			{
				chr = readChar(fileData, rIndex);

				if(chr == EOF) // セルの途中でファイルが終了した。-> セルとファイルの終端と見なす。
					break;

				if(chr == '\"')
				{
					chr = readChar(fileData, rIndex);

					if(chr != '\"')
						break;
				}
				cellBuff->AddElement(chr);
			}
		}
		else
		{
			for(; ; )
			{
				if(chr == ',' || chr == '\n')
					break;

				cellBuff->AddElement(chr);
				chr = readChar(fileData, rIndex);

				if(chr == EOF)
					break;
			}
		}
		cellBuff->AddElement('\0');
		table->PutCell(colidx, rowidx, cellBuff->UnbindBuffer());

		if(chr == '\n')
		{
			rowidx++;
			colidx = 0;
		}
		else
			colidx++;
	}
//	delete fileData; // 引数になったため、解放しない。
	delete cellBuff;

	// NULL -> strx("") & Trim
	{
		for(int x = 0; x < table->GetWidth(); x++)
		for(int y = 0; y < table->GetHeight(); y++)
		{
			char **p = table->CellAt(x, y);

			if(!*p)
				*p = strx("");

			unctrl(*p);
			trim(*p);
		}
		table->SetCallBack(getNullString);
	}
	// Trim
	{
		int xMax = -1;
		int yMax = -1;

#if 1
		for(int x = table->GetWidth() - 1; 0 <= x; x--)
		for(int y = 0; y < table->GetHeight(); y++)
		{
			if(*table->GetCell(x, y))
			{
				xMax = x;
				yMax = y;

				for(y = table->GetHeight() - 1; yMax < y; y--)
				for(x = 0; x <= xMax; x++)
				{
					if(*table->GetCell(x, y))
					{
						yMax = y;
						goto endTrimLoop;
					}
				}
			}
		}
endTrimLoop:
#else // SAME CODE
		for(int x = 0; x < table->GetWidth(); x++)
		for(int y = 0; y < table->GetHeight(); y++)
		{
			if(*table->GetCell(x, y))
			{
				m_maxim(xMax, x);
				m_maxim(yMax, y);
			}
		}
#endif

		table->Resize(xMax + 1, yMax + 1);
	}
	return table;
}
autoTable<char *> *readCsvFile(char *file)
{
	autoList<uchar> *fileData = readFile(file);
	autoTable<char *> *table = readCsvFile(fileData);
	delete fileData;
	return table;
}
void writeCsvFile(char *file, autoTable<char *> *table)
{
	autoList<uchar> *fileData = new autoList<uchar>();

	for(int rowidx = 0; rowidx < table->GetHeight(); rowidx++)
	{
		for(int colidx = 0; colidx < table->GetWidth(); colidx++)
		{
			char *cell = table->GetCell(colidx, rowidx);

			if(colidx)
				fileData->AddElement(',');

			if(strchr(cell, '"') || strchr(cell, ',') || strchr(cell, '\n')) // ? "" 必要
			{
				fileData->AddElement('"');

				for(char *p = cell; *p; p++)
				{
					if(*p == '"')
					{
						fileData->AddElement('"');
						fileData->AddElement('"');
					}
					else
						fileData->AddElement(*p);
				}
				fileData->AddElement('"');
			}
			else
				fileData->AddElements((uchar *)cell, strlen(cell));
		}
		fileData->AddElement('\n');
	}
	writeFile_cx(file, fileData);
}
