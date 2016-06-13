#include "Manipulate.h"
#include <fstream>

Manipulate::Manipulate()
{
}


Manipulate::~Manipulate()
{
}


void Manipulate::Grayscale(Image& image)
{
	for (size_t row = 0; row < image.height; ++row)
	{
		int counter = 1;
		unsigned char Red, Green, Blue;
		size_t red, green, blue;
		for (size_t col = 0; col < image.help; ++col)
		{
			
			if (counter == 1)
			{
				red = col;
				Red = image.pixels[row][col];
			}
			else if (counter == 2)
			{
				green = col;
				Green = image.pixels[row][col];
			}
			else if (counter == 3)
			{
				blue = col;
				Blue = image.pixels[row][col];
				unsigned char Gray = Red * 0.3 + Green * 0.59 + Blue * 0.11;
				image.pixels[row][red] = Gray;
				image.pixels[row][green] = Gray;
				image.pixels[row][blue] = Gray;

				counter = 0;
			}
				counter += 1;
		}
	}
}


void Manipulate::Monochrome(Image& image)
{
	for (size_t i = 0; i < image.height; ++i)
	{
		for (size_t j = 0; j < image.help; ++j) //help
		{
			image.pixels[i][j] = (unsigned)image.pixels[i][j];
			if (image.pixels[i][j] > image.max_value / 2)
			{
				image.pixels[i][j] = image.max_value;
			}
			else
			{
				image.pixels[i][j] = 0;
			}
		}
	}
}


void Manipulate::Histogram(Image& image)
{
	//WORKS FOR GREEN!
	/*
	* colour pixel value from 0 to 255
	*/
	cout << "width=" << image.width << endl;
	cout << "height=" << image.height << endl;
	const int size = 256;
	int histogram[size] = { 0, };
	for (int row = 0; row < image.height; ++row)
	{
		int counter = 1;
		int red, green, blue;

		for (int col = 0; col < image.width; ++col)
		{

			if (counter == 1)
			{
				red = col;
			}
			else if (counter == 2)
			{
				green = col;
			}
			else if (counter == 3)
			{
				blue = col;
				int color = image.pixels[row][green]; // change here for color
				++histogram[color];
				counter = 0;
			}
			counter += 1;
		}
	}

	/*
	*	Calculates the percents per concrete colour
	*/
	double percents[size];
	double count_of_pixels = image.height*image.width;
	cout << "Count of pixels:" << count_of_pixels << endl;
	
	for (size_t index = 0; index < size; ++index)
	{
		percents[index] = (histogram[index] * 100) / count_of_pixels;
		percents[index] = (int)percents[index];
	}

	/*
	*	Saves the histogram in a file - P3 ASCII PPM
	*/
	const char* header = "P3";
	const int height = 100;
	const int width = 256;
	const int max_value = 255;
	
	int arr[height][width];
	
	ofstream hist("histogram.ppm");
	hist << header << '\n';
	hist << 255 << '\n';
	hist << height << '\n';
	hist << max_value << '\n';

	int red, green, blue, counter;
	int temp;
	for (int row = 0; row < height; ++row)
	{
		counter = 1;
		temp = row;//99 - row;

		for (int col = 0; col < width; ++col)
		{
			if (temp <= percents[col])
			{
				if (counter == 1)
				{
					red = col;
					arr[temp][col] = 0;
				}
				else if (counter == 2)
				{
					green = col;
					arr[temp][col] = 255;
				}
				else if (counter == 3)
				{
					blue = col;
					arr[temp][col] = 0;

					hist << arr[temp][red] << ' ';
					hist << arr[temp][green] << ' ';
					hist << arr[temp][blue] << ' ';
					
					counter = 0;
				}
			}
			else
			{
				if (counter == 1)
				{
					red = col;
					arr[temp][red] = 255;
				}
				else if (counter == 2)
				{
					green = col;
					arr[temp][green] = 255;
				}
				else if (counter == 3)
				{
					blue = col;
					arr[temp][blue] = 255;

					hist << arr[temp][red] << ' ';
					hist << arr[temp][green] << ' ';
					hist << arr[temp][blue] << ' ';

					counter = 0;
				}
			}
			counter += 1;
		}
	}
	hist.close();
}