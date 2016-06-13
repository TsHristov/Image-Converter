#include "AsciiWriter.h"

void AsciiWriter::Save(Image& image) const
{
	unsigned char** pixels = image.GetPixels();
	ofstream save_file("save.ppm");
	save_file << image.GetHeader() << '\n';
	save_file << image.GetWidth() << '\n'; //Because of file format!
	save_file << image.GetHeight() << '\n';
	save_file << image.GetMaxValue() << '\n';

	for (size_t i = 0; i < image.GetHeight(); ++i)
	{
		for (size_t j = 0; j < image.GetHelpWidth(); ++j)
		{
			save_file << (unsigned)pixels[i][j] << ' ';
		}
	}
}