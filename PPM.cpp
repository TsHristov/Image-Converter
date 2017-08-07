#include "PPM.h"
#include "BinaryWriter.h"
#include "AsciiWriter.h"
#include <fstream>
#include <string.h>

PPM::PPM(const char* file_name): Image(file_name)
{
  ReadHeader();
  pixels = ReadPixels();
}

unsigned char** PPM::ReadPixels()
{
  ifstream file(file_name, ios::binary);
  file.seekg(read_position);
  //ASCII
  if (!strcmp(header, "P3"))
  {
    help_width = 3 * width;
    pixels = new unsigned char*[height];
    for (size_t row = 0; row < height; ++row)
    {
      pixels[row] = new unsigned char[help_width];
      for (size_t col = 0; col < help_width; ++col)
      {
        if (!file.eof())
        {
          int number;
          file >> number;
          pixels[row][col] = number;
        }
        else
          break;
      }
    }
    return pixels;
  }
  //BINARY
  else if (!strcmp(header, "P6"));
  {
    help_width = 3 * width;
    pixels = new unsigned char*[height];
    for (size_t row = 0; row < height; ++row)
    {
      pixels[row] = new unsigned char[help_width];
      for (size_t col = 0; col < help_width; ++col)
      {
        if (!file.eof())
        {
          file.read((char*)&pixels[row][col], sizeof(pixels[row][col]));
        }
        else
          break;
      }
    }
    return pixels;
  }
}

void PPM::Save()
{
  if (!strcmp(header, "P3"))
  {
    AsciiWriter writer;
    writer.SaveImage(*this);
  }
  else if (!strcmp(header, "P6"))
  {
    BinaryWriter writer;
    writer.SaveImage(*this);
  }
}
