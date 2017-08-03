#pragma once
#include "Image.h"
#include "AsciiWriter.h"
#include "BinaryWriter.h"
class PPM :public Image
{
public:
	PPM(): Image() {}
	PPM(char*);
	virtual ~PPM();
	PPM& operator=(const PPM&);

public:
	virtual unsigned char** ReadPixels();
	virtual void Save();
	streampos GetReadPosition() const;

public:
	virtual char* GetFileName() const;
	virtual char* GetHeader();
	virtual int GetWidth() const;
	virtual int GetHelpWidth() const;
	virtual int GetHeight() const;
	virtual int GetMaxValue() const;
	virtual unsigned char** GetPixels() const;
};
