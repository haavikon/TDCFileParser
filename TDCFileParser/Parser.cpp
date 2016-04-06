using namespace std;
#include "Parser.h"
#include "ANUFilename.h"
#include "TDCWord.h"

Parser::Parser(string _Directory, string _OutputFileName)
{
	TFile *hfile; 
	hfile = 0;
	//groupNumber = 0;
	this->directory = _Directory;
	this->opFilename = _OutputFileName;

	tree = make_shared<TTree>("T", "Parsed raw data from LeCroy 3377 TDC");
	tree->Branch("GroupNumber", &groupNumber , "GroupNumber/I");
	tree->Branch("Channel", &channel, "Channel/I");
	tree->Branch("Time", &time, "Time/I");

	this->ReadFiles();
	if (this->dirExists)
	{
		const char *rootFileName = opFilename.c_str();
		cout << rootFileName << endl; 
		cin.get();
		hfile = TFile::Open(opFilename.c_str(), "RECREATE");
		for each(string s in files)
		{
			ProcessFile(s);
		}
		tree->Print();
		tree->Write();
		delete hfile;
	}


}

void Parser::ReadFiles()
{
	//dirExists = false;
	//Reads in all the files in a directory using dirent.h from http://www.softagalleria.net/dirent.php 
	DIR* dir; 
	dirent* pdir;
	dir = opendir(directory.c_str());
	if (dir != NULL)
	{
		dirExists = true; 
		while (pdir = readdir(dir)) {
			files.push_back(pdir->d_name);
		}
	}
	else
	{
		cout << "Directory does not exist, exiting" << endl;
		//exit(1);
	}

	closedir(dir);
}

void Parser::ProcessFile(string _filename)
{
	string line;
	ANUFilename thisFile(_filename);
	uint16_t rawData;
	string buffer;
	if (thisFile.isANUFile)
	{
		if (!thisFile.isBFile)
		{
			ifstream inputFileStream(directory + "\\" + _filename);
			cout << _filename << endl;
			while (getline(inputFileStream, line)) {
				stringstream ss(line);
				while (getline(ss, buffer, '\t'))
				{
					rawData = (uint16_t)stoi(buffer);
					if (rawData > 0)
					{
						TDCWord tempWord(rawData);
						if (tempWord.channel > 15)
						{
							if (tempWord.isHeader)
								groupNumber++;
							else
							{
								//Put the groupnumber, channel and time in tree;
								channel = tempWord.channel;
								time = tempWord.time;
								tree->Fill();
							}
						}
					}
				}
			}
			inputFileStream.close();
		}
	}
}