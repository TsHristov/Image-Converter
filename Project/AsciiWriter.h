#pragma once
#include "Image.h"
#include <fstream>
using namespace std;
class AsciiWriter
{
public:
	void Save(Image&) const;
};