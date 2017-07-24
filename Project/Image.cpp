#include "Image.h"
#include <fstream>

Image::Image()
{
	cout << "Image::Image():" << endl;
}


Image::~Image()
{
	cout << "Image::~Image()" << endl;
}


Image::Image(char* fileName)
{
	cout << "Image::Image(char* fileName)" << endl;
}