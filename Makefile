CC=g++

CFLAGS=-g -c -Wall

all: image_converter

image_converter: main.o PPM.o PGM.o Image.o BinaryWriter.o AsciiWriter.o
	$(CC) main.o PPM.o PGM.o Image.o BinaryWriter.o AsciiWriter.o -o image_converter

main.o: main.cpp Image.o PPM.o PGM.o BinaryWriter.o AsciiWriter.o
	$(CC) $(CFLAGS) main.cpp

PPM.o: PPM.cpp PPM.h
	$(CC) $(CFLAGS) PPM.cpp

PGM.o: PGM.cpp PGM.h
	$(CC) $(CFLAGS) PGM.cpp

Image.o: Image.cpp Image.h
	$(CC) $(CFLAGS) Image.cpp

BinaryWriter.o: BinaryWriter.cpp BinaryWriter.h
	$(CC) $(CFLAGS) BinaryWriter.cpp

AsciiWriter.o: AsciiWriter.cpp AsciiWriter.h
	$(CC) $(CFLAGS) AsciiWriter.cpp

clean:
	\rm *.o
