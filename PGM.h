#pragma once
#include "Image.h"
class PGM :public Image
{
	friend class Manipulate;
public:
	PGM();
	PGM(char*);
	virtual ~PGM();
	PGM& operator=(const PGM&);

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

