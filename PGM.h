#pragma once
#include "Image.h"
#include "AsciiWriter.h"
#include "BinaryWriter.h"
class PGM :public Image
{
public:
	PGM(): Image() {}
	PGM(char*);
	virtual ~PGM();
	PGM& operator=(const PGM&);

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
