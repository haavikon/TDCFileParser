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
	tree->Branch("GroupNumber", &this->groupNumber , "GroupNumber/I");
	tree->Branch("Channel", &this->channel, "Channel/I");
	tree->Branch("Time", &this->time, "Time/I");

	this->ReadFiles();
	if (this->dirExists)
	{
		const char *rootFileName = opFilename.c_str();
		//cout << rootFileName << endl; 
		//cin.get();
		hfile = TFile::Open(opFilename.c_str(), "RECREATE");
		noOfFiles = files.size();
		for each(string s in files)
		{
			progress = (fileNumber / noOfFiles)* 100.0;
			//cout <<  progress << "% \r";
			ProcessFile(s);
			fileNumber++;
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
		exit(1);
	}

	closedir(dir);
}

void Parser::ProcessFile(string _filename)
{
	string line;
	ANUFilename thisFile(_filename);
	uint16_t rawData;
	string buffer, buffer2;
	vector<TDCWord> group;
	bool LSBOrder = true;
	if (thisFile.isANUFile)
	{
		if (thisFile.isBFile)
		{
			ifstream inputFileStream(directory + "\\" + _filename); 
			cout << endl << _filename;
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
							{
								if (groupNumber != -1)
								{
									if (group.size() > 1)
									{
										for (int iCount = 0; iCount < group.size(); iCount += 2)
										{
											this->channel = group[iCount].channel;

											if (iCount < (group.size() - 1))
											{
												//Put the groupnumber, channel and time in tree;
												if (group[iCount].channel == group[iCount + 1].channel)
												{
													this->time = group[iCount].time + group[iCount + 1].time;
												}
												cout << endl << groupNumber << "\t" << channel << "\t" << time;
											}
											tree->Fill();
										}
										groupNumber++;
									}
									group.clear();
									LSBOrder = true;
								}
								else
								{
									groupNumber++;
								}
							}
							else
							{
								if (tempWord.channel > 15)
								{
									if (tempWord.isLSB != LSBOrder)
									{
										group.push_back(TDCWord(rawData));
										LSBOrder = tempWord.isLSB;
										//cout << rawData << endl;
										//cin.get();
									}
								}
							}
						}
						else
						{
							getline(ss, buffer, '\t');
						}
					}
					else
					{
						getline(ss, buffer, '\t');
					}
				}
			}

			if (group.size() > 1)
			{
				for (int iCount = 0; iCount < group.size(); iCount += 2)
				{
					this->channel = group[iCount].channel;

					if (iCount < (group.size() - 1))
					{
						//Put the groupnumber, channel and time in tree;
						if (group[iCount].channel == group[iCount + 1].channel)
						{
							this->time = group[iCount].time + group[iCount + 1].time;
						}
						cout << endl << groupNumber << "\t" << channel << "\t" << time;
					}
					tree->Fill();
				}
				groupNumber++;
			}
			group.clear();
			LSBOrder = true;
			inputFileStream.close();
		}
	}
}