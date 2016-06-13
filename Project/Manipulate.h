#pragma once
#include "Image.h"
class Manipulate
{
public:
	Manipulate();
	~Manipulate();
	//Image& Grayscale(Image&); // Image - copy, Image& - original
	void Grayscale(Image&);
	void Monochrome(Image&);
	void Histogram(Image&);
};

