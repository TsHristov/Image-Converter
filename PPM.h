#pragma once
#include "Image.h"
#include "AsciiWriter.h"
#include "BinaryWriter.h"

class PPM: public Image
{
public:
  PPM(const char * file_name);

protected:
  virtual void Save();
  unsigned char** ReadPixels();
};
