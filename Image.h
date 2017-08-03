#pragma once
#include <iostream>
using namespace std;
// An abstract base class,
// representing an Image
class Image
{
protected:
	char* fileName;
	char header[100];
	int width;
	int help;
	int height;
	int max_value;
	unsigned char** pixels;
	streampos PositionToReadPixels;

public:
	Image(): width(0), height(0), max_value(0) {}
	Image(char*);
	virtual ~Image();
	bool IsNumber(char c) {return (c >= '0' && c <= '9');}

public:
	void ReadHeader();
	virtual unsigned char** ReadPixels() = 0;
	virtual void Save() = 0;

public:
	virtual char* GetFileName() const = 0;
	virtual char* GetHeader() = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHelpWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual int GetMaxValue() const = 0;
	virtual unsigned char** GetPixels() const = 0;

public:
	void Histogram();
	void Grayscale();
	void Monochrome();
};
