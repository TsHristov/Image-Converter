#include "Image.h"
#include "PPM.h"
#include "PGM.h"
#include <fstream>
#include <iostream>
#include <string.h>
using namespace std;

char* DetermineHeader(char* file_name)
{
  static char file_header[10];
  ifstream image(file_name);
  if(image.is_open())
  {
    image >> file_header;
    cout << file_header << endl;
  }
  else
  {
    //TO-DO: Throw Exception
    cout << "Problem opening the file: " << file_name << "\n";
  }
  return file_header;
}

void PrintUsage()
{
	cout << " Options available:\n";
	cout << " --grayscale\n";
	cout << " --monochrome\n";
	cout << " --histogram\n";
}

int main(int argc, char *argv[])
{
  char* file_name = argv[1];
  char* header = DetermineHeader(file_name);
  Image* file = NULL;
  if (!strcmp(header, "P1") || !strcmp(header, "P4"))
  {
    cout << "No transformations are availabe for the PBM format" << endl;
    cout << "A histogram may only be provided" << endl;
  }
  else if (!strcmp(header, "P2") || !strcmp(header, "P5"))
  {
    file = new PGM(file_name);
  }
  else if (!strcmp(header, "P3") || !strcmp(header, "P6"))
  {
    file = new PPM(file_name);
  }
  if (file)
  {
    if(!strcmp(argv[2],"--grayscale"))
		{
			file->Grayscale();
			file->Save();
		}

    if(!strcmp(argv[2],"--monochrome"))
		{
			file->Monochrome();
			file->Save();
		}

    delete file;
  }

  return 0;
}
