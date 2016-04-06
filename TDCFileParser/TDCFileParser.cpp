// TDCFileParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ANUFilename.h"
#include "Parser.h"


int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "Useage: TDCFileParser.exe [DIRECTORY] [OPFILENAME]" << endl << "e.g." << endl << "TDCFileParser c:\Data\14-08-2015\, 1655 parsed.root" << endl;
		return 0;
	}
	else
	{
		string _directory, _filename; 
		_directory = (string)argv[1];
		_filename = (string)argv[1] + (string)argv[2];
		//Parser thisParser(_directory, _filename);
		cout << _directory << " " << _filename << endl;
		return 0;
	}
}

