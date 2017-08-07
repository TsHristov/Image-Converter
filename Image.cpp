#include "Image.h"
#include <fstream>

Image::~Image()
{
  for (int i = 0; i < height; ++i)
  {
    delete[] pixels[i];
  }
  delete[] pixels;
}

void Image::ReadHeader()
{
  ifstream file(file_name);
  if (file.is_open())
  {
    int counter = 0;
    while (counter < 4)
    {
      if (counter == 0)
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
      else if (counter == 1)
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
      else if (counter == 2)
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
      else if (counter == 3)
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
      counter += 1;
    }
    char a;
    file.get(a);
    read_position = file.tellg();
    read_position -= 4;
  }
}

void Image::Grayscale()
{
  for (int row = 0; row < height; ++row)
  {
    // The counter marks the RGB colors:
    // 1: Red, 2: Green, 3: Blue
    int counter = 0;
    unsigned char red, green, blue;
    size_t red_index, green_index, blue_index;
    for (int col = 0; col < help_width; ++col)
    {
      counter += 1;
      // Color red
      if (counter == 1)
      {
        red_index = col;
        red = pixels[row][col];
      }
      // Color green
      else if (counter == 2)
      {
        green_index = col;
        green = pixels[row][col];
      }
      // Color blue
      else if (counter == 3)
      {
        blue_index = col;
        blue = pixels[row][col];
        // Algorithm for grayscale conversion used from:
        // http://www.tannerhelland.com/3643/grayscale-image-algorithm-vb6/
        unsigned char gray = red * 0.3 + green * 0.59 + blue * 0.11;
        pixels[row][red_index]   = gray;
        pixels[row][green_index] = gray;
        pixels[row][blue_index]  = gray;
        // The RGB triplet is constructed,
        // go to the next one
        counter = 0;
      }
    }
  }
  this->Save();
}

void Image::Monochrome()
{
  for (int i = 0; i < this->height; ++i)
  {
    for (int j = 0; j < this->help_width; ++j)
    {
      // this->pixels[i][j] = (unsigned)this->pixels[i][j];
      if((unsigned)this->pixels[i][j] > this->max_value / 2)
      {
        this->pixels[i][j] = (unsigned char)this->max_value;
      }
      else
      {
        this->pixels[i][j] = 0;
      }
    }
  }
  this->Save();
}

// Currently works for green channel
void Image::Histogram()
{
  cout << "width="  << width  << "\n";
  cout << "height=" << height << "\n";
  const int SIZE = 256;
  int histogram[SIZE] = { 0, };
  for (int row = 0; row < height; ++row)
  {
    // The counter marks the RGB colors
    int counter = 1;
    int red, green, blue;
    for (int col = 0; col < width; ++col)
    {
      if (counter == 1) { red = col; }
      else if (counter == 2) { green = col; }
      else if (counter == 3)
      {
        blue = col;
        int color = pixels[row][green];
        ++histogram[color];
        counter = 0;
      }
      counter += 1;
    }
  }
  // Calculates the percents per concrete colour
  double percents[SIZE];
  double count_of_pixels = height * width;
  cout << "Count of pixels: " << count_of_pixels << "\n";
  for (int i = 0; i < SIZE; ++i)
  {
    percents[i] = (histogram[i] * 100) / count_of_pixels;
    percents[i] = (int)percents[i];
  }
  // Saves the histogram in a file - P3 ASCII PPM
  const char * HEADER = "P3";
  const int HEIGHT    = 100;
  const int WIDTH     = 256;
  const int MAX_VALUE = 255;

  int arr[HEIGHT][WIDTH];

  ofstream hist("histogram.ppm");
  hist << HEADER << '\n';
  hist << 255 << '\n';
  hist << HEIGHT << '\n';
  hist << MAX_VALUE << '\n';

  int red, green, blue, counter;
  int temp;
  for (int row = 0; row < height; ++row)
  {
    counter = 1;
    // 99 - row
    temp = row;
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
          hist << arr[temp][red]   << ' ';
          hist << arr[temp][green] << ' ';
          hist << arr[temp][blue]  << ' ';
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
          hist << arr[temp][red]   << ' ';
          hist << arr[temp][green] << ' ';
          hist << arr[temp][blue]  << ' ';
          counter = 0;
        }
      }
      counter += 1;
    }
  }
  hist.close();
}
