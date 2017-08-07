#pragma once
#include <iostream>
using namespace std;

class Image
{
protected:
  const char * file_name;
  char header[10];
  int width;
  int help_width;
  int height;
  int max_value;
  unsigned char** pixels;
  streampos read_position; // Position to read pixels

public:
  Image(const char* name):
    file_name(name),
    width(0),
    help_width(0),
    height(0),
    max_value(0),
    pixels(NULL) {}
  virtual ~Image();

public:
  void Grayscale();
  void Monochrome();
  void Histogram();

public:
  virtual const char* GetFileName() const { return file_name; }
  virtual const char* GetHeader() const { return header; }
  virtual int GetWidth() const { return width; }
  virtual int GetHelpWidth() const { return help_width; }
  virtual int GetHeight() const { return height; }
  virtual int GetMaxValue() const { return max_value; }
  virtual unsigned char** GetPixels() const { return pixels; }
  virtual streampos GetReadPosition() const { return read_position; }

public:
  static bool IsNumber(char c) { return (c >= '0' && c <= '9'); }

protected:
  virtual void Save() = 0;
  void ReadHeader();
};
