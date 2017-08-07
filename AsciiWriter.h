#pragma once
#include "Image.h"
#include <fstream>

class AsciiWriter
{
public:
  void SaveImage(const Image&) const;
};
