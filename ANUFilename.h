using namespace std;

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

//Class to parse old TDC Data directories and turn it into something useful...
class ANUFilename {
public:
	ANUFilename(string _Filename);
	string fileName;
	string fileTime; 
	string fileDate; 
	int fileNumber;
	bool isANUFile;
	bool isBFile;
};