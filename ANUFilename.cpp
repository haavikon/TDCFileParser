using namespace std;

#include "ANUFilename.h"

ANUFilename::ANUFilename(string _filename)
{
	vector<string> splits; 
	fileName = _filename;
	isBFile = false; 
	isANUFile = false;

	//replace all delimiters with spaces
	replace(fileName.begin(), fileName.end(), ',', ' ');
	replace(fileName.begin(), fileName.end(), '\\', ' ');
	replace(fileName.begin(), fileName.end(), '.', ' ');

	//split the string into parts and store in a vector of strings 
	string buffer;
	stringstream ss(fileName);
	while (getline(ss, buffer, ' '))
	{
		splits.push_back(buffer);
	}

	//There should be at least 7 new strings 
	if (splits.size() > 7)
	{
		if (splits[splits.size() - 3] == "Data")
		{
			isANUFile = true;
			if (splits[splits.size() - 2].find('B') != string::npos)
			{
				isBFile = true;
			}
			fileNumber = stoi(splits[splits.size() - 2]);
			fileDate = splits[splits.size() - 8];
			fileTime = splits[splits.size() - 6];

		}
	}
}