using namespace std;

#ifndef TDCWord_HEADER
#define TDCWord_HEADER

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


//Class to parse old TDC Data directories and turn it into something useful...
class TDCWord {
public:
	TDCWord(uint16_t _word);
	string TOSTRING();
	bool isHeader;
	bool isLSB;
	int channel;
	int time;
	bool isLeadingEdge;
	bool isLeadingEdgeRecording;
	int moduleID;
	int eventSerial;
	bool isDoubleWord;
	int twoBitResolution; 
	uint16_t word;
};

#endif
