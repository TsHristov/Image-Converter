#include "PGM.h"
#include "BinaryWriter.h"
#include "AsciiWriter.h"
#include <fstream>
#include <string.h>

PGM::~PGM()
{
	for (int index = 0; index < height; ++index)
	{
		delete[] pixels[index];
	}
	delete[] pixels;

	cout << "PGM::~PGM()" << endl;
}

PGM& PGM::operator=(const PGM& other)
{
	if (this == &other)
	{
		return *this;
	}
	strcpy(fileName, other.fileName);
	strcpy(header, other.header);
	width = other.width;
	height = other.height;
	max_value = other.max_value;
	for (size_t row = 0; row < height; ++row)
	{
		delete[] pixels[row];
	}
	delete[] pixels;
	for (size_t row = 0; row < height; ++row)
	{
		pixels[row] = new unsigned char[height];
		for (size_t col = 0; col < help; ++col)
		{
			pixels[row][col] = other.pixels[row][col];
		}
	}
	return *this;
}


PGM::PGM(char* fileName): Image(fileName)
{
	this->fileName = fileName;
	ReadHeader();
	this->pixels = ReadPixels();
	cout << "PGM::PGM(char* fileName)" << endl;
}

streampos PGM::GetReadPosition() const
{
	return this->PositionToReadPixels;
}


unsigned char** PGM::ReadPixels()
{
	ifstream file(fileName, ios::binary);
	file.seekg(PositionToReadPixels);
	//ASCII
	if (!strcmp(header, "P2"))
	{
		help = width;
		this->pixels = new unsigned char*[height];
		for (size_t row = 0; row < height; ++row)
		{
			this->pixels[row] = new unsigned char[help];
			for (size_t col = 0; col < help; ++col)
			{
				if (!file.eof())
				{
					int number;
					file >> number;
					this->pixels[row][col] = number;
				}
				else
					break;
			}

		}
		return pixels;
	}
	//BINARY
	else if (!strcmp(header, "P5"));
	{
		help = width;
		pixels = new unsigned char*[height];
		for (size_t row = 0; row < height; ++row)
		{
			pixels[row] = new unsigned char[width];
			for (size_t col = 0; col < width; ++col)
			{
				if (!file.eof())
				{
					file.read((char*)&pixels[row][col], sizeof(pixels[row][col]));
				}
				else
					break;
			}
		}
		return pixels;
	}
}


char* PGM::GetFileName() const
{
	return this->fileName;
}


char* PGM::GetHeader()
{
	return this->header;
}


int PGM::GetWidth() const
{
	return this->width;
}

int PGM::GetHelpWidth() const
{
	return this->help;
}


int PGM::GetHeight() const
{
	return this->height;
}


int PGM::GetMaxValue() const
{
	return this->max_value;
}

unsigned char** PGM::GetPixels() const
{
	return this->pixels;
}

void PGM::Save()
{
	if (!strcmp(header, "P2"))
	{
		AsciiWriter writer;
		writer.Save(*this);
	}
	else if (!strcmp(header, "P5"))
	{
		BinaryWriter writer;
		writer.Save(*this);
	}
}
