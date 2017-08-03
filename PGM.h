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
  streampos GetReadPosition() const { return PositionToReadPixels; }

public:
  virtual char* GetFileName() const { return fileName; }
  virtual char* GetHeader() { return header; }
  virtual int GetWidth() const { return width; }
  virtual int GetHelpWidth() const { return help; }
  virtual int GetHeight() const { return height; }
  virtual int GetMaxValue() const { return max_value; }
  virtual unsigned char** GetPixels() const { return pixels; }
};
