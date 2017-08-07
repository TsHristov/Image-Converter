#pragma once
#include "Image.h"
#include <string.h>
#include <fstream>
using namespace std;
class BinaryWriter
{
public:
  void SaveImage(const Image& image) const;
};
