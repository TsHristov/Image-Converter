CC=g++

CFLAGS=-g -c -Wall

all: image_converter

image_converter: main.o PPM.o PGM.o Image.o BinaryWriter.o AsciiWriter.o
	$(CC) main.o PPM.o PGM.o Image.o BinaryWriter.o AsciiWriter.o -o image_converter

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

PPM.o: PPM.cpp
	$(CC) $(CFLAGS) PPM.cpp

PGM.o: PGM.cpp
	$(CC) $(CFLAGS) PGM.cpp

Image.o: Image.cpp
	$(CC) $(CFLAGS) Image.cpp

BinaryWriter.o: BinaryWriter.cpp
	$(CC) $(CFLAGS) BinaryWriter.cpp

AsciiWriter.o: AsciiWriter.cpp
	$(CC) $(CFLAGS) AsciiWriter.cpp
