#include "Image.h"
#include "PPM.h"
#include "PGM.h"
#include <fstream>
#include <iostream>
#include <string.h>

void DetermineHeader(const char * file_name, char * file_header)
{
  ifstream image(file_name);
  if(image.is_open())
  {
    image >> file_header;
    std::cout << file_header << "\n";
  }
  else
  {
    cout << "Problem opening the file: " << file_name << "\n";
  }
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
  // Sample usage:
  // Image image(image_name);
  // image.Grayscale();
  // image.Histogram();
  const char * image_name = argv[1];
  char header[10] = "";
  DetermineHeader(image_name, header);
  Image * image = NULL;
  // Image image(image_name, header);
  // image->Grayscale();

  // Determine the proper format:
  if (!strcmp(header, "P1") || !strcmp(header, "P4"))
  {
    std::cout << "No transformations are availabe for the PBM format\n";
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
    }

    if(!strcmp(argv[2], "--monochrome"))
    {
      image->Monochrome();
    }

    if(!strcmp(argv[2], "--histogram"))
    {
      image->Histogram();
    }

    delete image;
  }
  return 0;
}
