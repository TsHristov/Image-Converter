#pragma once
#include "Image.h"
class PPM :public Image
{
	friend class Manipulate;
public:
	PPM();
	PPM(char*);
	virtual ~PPM();
	PPM& operator=(const PPM&);

public:
	virtual void ReadHeader();
	virtual unsigned char** ReadPixels();
	virtual void Histogram();
	virtual void Grayscale();
	virtual void Monochrome();
	virtual void Save();
	streampos GetReadPosition() const;

public:
	char* GetFileName() const;
	char* GetHeader();
	int GetWidth() const;
	int GetHelpWidth() const;
	int GetHeight() const;
	int GetMaxValue() const;
	unsigned char** GetPixels() const;
};

