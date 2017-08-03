#include "PPM.h"
#include "BinaryWriter.h"
#include "AsciiWriter.h"
#include <fstream>
#include <string.h>

PPM::~PPM()
{
  for (int index = 0; index < height; ++index)
  {
    delete[] pixels[index];
  }
  delete[] pixels;

  cout << "PPM::~PPM()" << endl;
}


PPM& PPM::operator=(const PPM& other)
{
  if (this == &other)
  {
    return *this;
  }
  strcpy(fileName, other.fileName);
  strcpy(header, other.header);
  width = other.width;
  height = other.height;
  max_value = other.max_value;
  for (size_t row = 0; row < height; ++row)
  {
    delete[] pixels[row];
  }
  delete[] pixels;
  for (size_t row = 0; row < height; ++row)
  {
    pixels[row] = new unsigned char[height];
    for (size_t col = 0; col < width; ++col)
    {
      pixels[row][col] = other.pixels[row][col];
    }
  }
  return *this;
}


PPM::PPM(char* fileName) :Image(fileName)
{
  this->fileName = fileName;
  ReadHeader();
  this->pixels = ReadPixels();
  cout << "PPM::PPM(char* fileName)" << endl;
}

unsigned char** PPM::ReadPixels()
{
  ifstream file(fileName, ios::binary);
  file.seekg(PositionToReadPixels);
  //ASCII
  if (!strcmp(header, "P3"))
  {
    help = 3 * width;
    this->pixels = new unsigned char*[height];
    for (size_t row = 0; row < height; ++row)
    {
      this->pixels[row] = new unsigned char[help];
      for (size_t col = 0; col < help; ++col)
      {
        if (!file.eof())
        {
          int number;
          file >> number;
          this->pixels[row][col] = number;
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
    help = 3 * width;
    pixels = new unsigned char*[height];
    for (size_t row = 0; row < height; ++row)
    {
      pixels[row] = new unsigned char[help];
      for (size_t col = 0; col < help; ++col)
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
    writer.Save(*this);
  }
  else if (!strcmp(header, "P6"))
  {
    BinaryWriter writer;
    writer.Save(*this);
  }
}
