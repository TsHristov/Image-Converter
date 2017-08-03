#include "Image.h"
#include "PPM.h"
#include "PGM.h"
#include <fstream>
#include <iostream>
#include <string.h>

char * DetermineHeader(char * file_name)
{
  static char file_header[10];
  ifstream image(file_name);
  if(image.is_open())
  {
    image >> file_header;
    std::cout << file_header << "\n";
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
  std::cout << " Options available:\n";
  std::cout << " --grayscale\n";
  std::cout << " --monochrome\n";
  std::cout << " --histogram\n";
}

int main(int argc, char *argv[])
{
  PrintUsage();
  char* image_name = argv[1];
  char* header = DetermineHeader(image_name);
  Image * image = NULL;
  if (!strcmp(header, "P1") || !strcmp(header, "P4"))
  {
    std::cout << "No transformations are availabe for the PBM format\n";
    std::cout << "A histogram may only be provided\n";
  }
  else if (!strcmp(header, "P2") || !strcmp(header, "P5"))
  {
    image = new PGM(image_name);
  }
  else if (!strcmp(header, "P3") || !strcmp(header, "P6"))
  {
    image = new PPM(image_name);
  }
  if (image)
  {
    if(!strcmp(argv[2], "--grayscale"))
    {
      image->Grayscale();
      image->Save();
    }

    if(!strcmp(argv[2], "--monochrome"))
    {
      image->Monochrome();
      image->Save();
    }

    if(!strcmp(argv[2], "--histogram"))
    {
      image->Histogram();
      image->Save();
    }

    delete image;
  }

  return 0;
}
