#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <Windows.h>
#include "dirent.h"
#include <algorithm>
#include <memory>

#include <TFile.h>
#include <TTree.h>

using namespace std;
//Class to parse old TDC Data directories and turn it into something useful...
class Parser {
public:
	shared_ptr<TTree> tree;
	Parser(string _Directory, string OutputFileName);
	string directory;
	string opFilename;
private:
	bool dirExists = false;
	void ReadFiles();
	vector<string> files;
	void ProcessFile(string _filename);
	ofstream outputFileStream; 
	int groupNumber = 0;
	int channel; 
	int time; 
	FILE *fp;
};
