#include "all.h"

static double CellToEnemyArg(char *cell)
{
	return toDouble(cell);
}

#define DATA_START_ROWIDX 2
#define DATA_START_COLIDX 0

void LoadScrRecList(autoList<ScrRec_t *> *scrRecList, autoTable<char *> *csv)
{
	int sumfrm = 0;

	for(int r = DATA_START_ROWIDX; r < csv->GetHeight(); r++)
	{
		int c = DATA_START_COLIDX;
		char *modif = csv->GetCell(c++, r);

		switch(*modif)
		{
		case '*':
			GDc.ScrRecStartPos = scrRecList->GetCount();
			break;

		case '/':
			goto endAddSrcRec;

		default:
			break;
		}

		ScrRec_t *sr = CreateScrRec();

		int frame = atoi(csv->GetCell(c++, r));
		m_range(frame, 0, IMAX);
		sumfrm += frame;
		errorCase(IMAX < sumfrm); // ŽžŠÔŒo‰ß‚µ‰ß‚¬
		sr->Frame = sumfrm;

		sr->EventId = atoi(csv->GetCell(c++, r));
		m_range(sr->EventId, 0, IMAX);

		sr->SubId = atoi(csv->GetCell(c++, r));
		m_range(sr->SubId, 0, IMAX);

		sr->EnemyCommonData = DuplexEnemyCommonData(GetECD(
			d2i(CellToEnemyArg(csv->GetCell(c + 0, r))),
			d2i(CellToEnemyArg(csv->GetCell(c + 1, r))),
			d2i(CellToEnemyArg(csv->GetCell(c + 2, r))),
			CellToEnemyArg(csv->GetCell(c + 3, r)),
			CellToEnemyArg(csv->GetCell(c + 4, r)),
			d2i(CellToEnemyArg(csv->GetCell(c + 5, r)))
			));
		c += 6;

		sr->Args = new autoList<double>();

		for(; ; )
		{
			char *cell = csv->RefCell(c++, r, "");

			if(!*cell)
				break;

			sr->Args->AddElement(CellToEnemyArg(cell));
		}
		scrRecList->AddElement(sr);
endAddSrcRec:;
	}
}
void LoadScrRecList(autoList<ScrRec_t *> *scrRecList, autoList<uchar> *fileData)
{
	autoTable<char *> *csv = readCsvFile(fileData);
	LoadScrRecList(scrRecList, csv);
	delete csv;
}
