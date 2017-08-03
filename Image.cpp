#include "Image.h"
#include <fstream>

Image::~Image()
{
  cout << "Image::~Image()" << endl;
}

Image::Image(char* fileName)
{
  cout << "Image::Image(char* fileName)" << endl;
}

void Image::ReadHeader()
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

void Image::Grayscale()
{
  for (size_t row = 0; row < this->height; ++row)
  {
    int counter = 1;
    unsigned char Red, Green, Blue;
    size_t red, green, blue;
    for (size_t col = 0; col < this->help; ++col)
    {
      if (counter == 1)
      {
        red = col;
        Red = this->pixels[row][col];
      }
      else if (counter == 2)
      {
        green = col;
        Green = this->pixels[row][col];
      }
      else if (counter == 3)
      {
        blue = col;
        Blue = this->pixels[row][col];
        unsigned char Gray = Red * 0.3 + Green * 0.59 + Blue * 0.11;
        this->pixels[row][red]   = Gray;
        this->pixels[row][green] = Gray;
        this->pixels[row][blue]  = Gray;
        counter = 0;
      }
      counter += 1;
    }
  }
}

void Image::Monochrome()
{
  for (size_t i = 0; i < this->height; ++i)
  {
    for (size_t j = 0; j < this->help; ++j)
    {
      this->pixels[i][j] = (unsigned)this->pixels[i][j];
      if (this->pixels[i][j] > this->max_value / 2)
      {
        this->pixels[i][j] = this->max_value;
      }
      else
      {
        this->pixels[i][j] = 0;
      }
    }
  }
}

void Image::Histogram()
{
  //WORKS FOR GREEN!
  /*
  * colour pixel value from 0 to 255
  */
  cout << "width=" << width << endl;
  cout << "height=" << height << endl;
  const int size = 256;
  int histogram[size] = { 0, };
  for (int row = 0; row < height; ++row)
  {
    int counter = 1;
    int red, green, blue;
    for (int col = 0; col < width; ++col)
    {
      if (counter == 1) { red = col; }
      else if (counter == 2) { green = col; }
      else if (counter == 3)
      {
        blue = col;
        int color = pixels[row][green]; // change here for color
        ++histogram[color];
        counter = 0;
      }
      counter += 1;
    }
  }

  /*
  *  Calculates the percents per concrete colour
  */
  double percents[size];
  double count_of_pixels = height * width;
  cout << "Count of pixels:" << count_of_pixels << endl;
  for (size_t index = 0; index < size; ++index)
  {
    percents[index] = (histogram[index] * 100) / count_of_pixels;
    percents[index] = (int)percents[index];
  }

  /*
  *  Saves the histogram in a file - P3 ASCII PPM
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
