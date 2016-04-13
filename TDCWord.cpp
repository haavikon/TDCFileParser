using namespace std;
#include "TDCWord.h"

TDCWord::TDCWord(uint16_t _word)
{
	uint16_t mask;
	word = _word;
	isHeader = false;
	isLSB = true;
	isLeadingEdge = false;
	isLeadingEdgeRecording = false;
	isDoubleWord = false;

	mask = 32768;
	if ((word&mask) == mask)
		isHeader = true;

	mask = 256;
	if ((word&mask) == mask)
		isLSB = false;

	mask = 512;
	if ((word&mask) == 0)
		isLeadingEdge = true;

	mask = 1024;
	if ((word&mask) == 0)
		isLeadingEdgeRecording = true;

	mask = 16384;
	if ((word&mask) == mask)
		isDoubleWord = true;

	mask = 31744;
	channel = (int)((mask&word) >> 10);

	mask = 255;
	if (isLSB)
	{
		time = (int)(mask&word);
	}
	else
	{
		time = (int)((mask&word) << 8);
	}

	mask = 255;
	moduleID = (int)(mask&word);

	mask = 14336;
	eventSerial = (int)(((word&mask) >> 11) % 8);

	mask = 768;
	twoBitResolution = (int)((mask&word) >> 8);
}