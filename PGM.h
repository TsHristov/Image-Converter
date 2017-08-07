#pragma once
#include "Image.h"
#include "AsciiWriter.h"
#include "BinaryWriter.h"

class PGM: public Image
{
public:
  PGM(const char * file_name);

protected:
  virtual void Save();
  unsigned char** ReadPixels();
};
