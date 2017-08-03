#pragma once
#include "Image.h"
#include <fstream>
using namespace std;
class BinaryWriter
{
public:
	void Save(Image&) const;
};
