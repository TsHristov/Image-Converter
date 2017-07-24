#include "PPM.h"
#include "BinaryWriter.h"
#include "Manipulate.h"
#include "AsciiWriter.h"
#include <fstream>
#include <string.h>

PPM::PPM()
{
	this->width = 0;
	this->height = 0;
	this->max_value = 0;
	cout << "PPM::PPM():" << endl;
}


PPM::~PPM()
{
	for (int index = 0; index < height; ++index)
	{
		delete[] pixels[index];
	}
	delete[] pixels;

	cout << "PPM::~PPM()" << endl;
}


PPM& PPM::operator=(const PPM& other)
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
		for (size_t col = 0; col < width; ++col)
		{
			pixels[row][col] = other.pixels[row][col];
		}
	}
	return *this;
}


PPM::PPM(char* fileName) :Image(fileName)
{
	this->fileName = fileName;
	ReadHeader();
	this->pixels = ReadPixels();
	cout << "PPM::PPM(char* fileName)" << endl;
}

void PPM::ReadHeader()
{
	ifstream file(fileName);
	if (file.is_open())
	{
		int count = 0;
		while (count < 4)
		{
			if (count == 0)
			{
				char c;
				streampos position = file.tellg();
				file.get(c);
				if (c == '#')
				{
					char comment[100];
					file.getline(comment, 100, '\n');
				}
				else
				{
					file.seekg(position);
					file >> header;

				}
			}
			else if (count == 1)
			{
				char c;
				streampos position = file.tellg();
				file.get(c);
				if (c == '#' || !IsNumber(c))
				{
					char comment[100];
					file.getline(comment, 100, '\n');
					file >> width;
				}
				else
				{
					file.seekg(position);
					file >> width;
				}
			}
			else if (count == 2)
			{
				char c;
				streampos position = file.tellg();
				file.get(c);
				if (c == ' ')
				{
					position = file.tellg();
					file >> height;
				}
				if (c == '#')
				{
					char comment[100];
					file.getline(comment, 100, ' ');
					continue;
				}
			}
			else if (count == 3)
			{
				char c;
				streampos position = file.tellg();
				file.get(c);
				if (c == '#')
				{
					char comment[100];
					file.getline(comment, 100, '\n');
					file >> max_value;
					continue;
				}
				else if (!IsNumber(c))
				{
					file >> max_value;
				}
			}
			count += 1;
		}
		char a;
		file.get(a);
		PositionToReadPixels = file.tellg();
		PositionToReadPixels -= 4;
	}
}


streampos PPM::GetReadPosition() const
{
	return this->PositionToReadPixels;
}


unsigned char** PPM::ReadPixels()
{
	ifstream file(fileName, ios::binary);
	file.seekg(PositionToReadPixels);
	//ASCII
	if (!strcmp(header, "P3"))
	{
		help = 3 * width;
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
	else if (!strcmp(header, "P6"));
	{
		help = 3 * width;
		pixels = new unsigned char*[height];
		for (size_t row = 0; row < height; ++row)
		{
			pixels[row] = new unsigned char[help];
			for (size_t col = 0; col < help; ++col)
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


char* PPM::GetFileName() const
{
	return this->fileName;
}


char* PPM::GetHeader()
{
	return this->header;
}


int PPM::GetWidth() const
{
	return this->width;
}


int PPM::GetHelpWidth() const
{
	return this->help;
}


int PPM::GetHeight() const
{
	return this->height;
}


int PPM::GetMaxValue() const
{
	return this->max_value;
}

unsigned char** PPM::GetPixels() const
{
	return this->pixels;
}

void PPM::Save()
{
	if (!strcmp(header, "P3"))
	{
		AsciiWriter obj;
		obj.Save(*this);
	}
	else if (!strcmp(header, "P6"))
	{
		BinaryWriter obj;
		obj.Save(*this);
	}
}


void PPM::Histogram()
{
	Manipulate obj;
	obj.Histogram(*this);
}


void PPM::Monochrome()
{
	Manipulate obj;
	obj.Grayscale(*this);
	obj.Monochrome(*this);
}


void PPM::Grayscale()
{
	Manipulate obj;
	obj.Grayscale(*this);
}
