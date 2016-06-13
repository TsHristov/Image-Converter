#include "Image.h"
#include "PPM.h"
#include "PGM.h"
#include <fstream>
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>

char* DetermineHeader(char* arg)
{
	char header[10];
	ifstream f(arg);
	f >> header;
	cout << header << endl;
	return header;
}

int main()
{
	{ char* fileName = "sines.ascii.ppm";
	char* header = DetermineHeader(fileName);
	Image* file = NULL;
	if (!strcmp(header, "P1") || !strcmp(header, "P4"))
	{
		cout << "No transformations are availabe for the PBM format" << endl;
		cout << "A histogram may only be provided" << endl;
	}
	else if (!strcmp(header, "P2") || !strcmp(header, "P5"))
	{
		file = new PGM(fileName);
	}
	else if (!strcmp(header, "P3") || !strcmp(header, "P6"))
	{
		file = new PPM(fileName);
	}
	if (file)
	{
		//if(command == Grayscale)
		/*{
			file->Grayscale();
			}
			else if (command == monochrome)
			{
			file->Monochrome();
			}
			else if (command == histogram)
			{
			file->Histogram();
			}*/


		file->Histogram();
		//file->Grayscale();
		//file->Monochrome();
		//file->Save();

		delete file;
	} }

	_CrtDumpMemoryLeaks();
	return 0;
}
