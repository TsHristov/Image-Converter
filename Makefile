CC=g++

CFLAGS=-g -c -Wall

all: image_converter

image_converter: Project.o PPM.o PGM.o Manipulate.o Image.o BinaryWriter.o AsciiWriter.o
	$(CC) Project.o PPM.o PGM.o Manipulate.o Image.o BinaryWriter.o AsciiWriter.o -o image_converter

Project.o: Project.cpp
	$(CC) $(CFLAGS) Project.cpp

PPM.o: PPM.cpp
	$(CC) $(CFLAGS) PPM.cpp

PGM.o: PGM.cpp
	$(CC) $(CFLAGS) PGM.cpp

Manipulate.o: Manipulate.cpp
	$(CC) $(CFLAGS) Manipulate.cpp

Image.o: Image.cpp
	$(CC) $(CFLAGS) Image.cpp

BinaryWriter.o: BinaryWriter.cpp
	$(CC) $(CFLAGS) BinaryWriter.cpp

AsciiWriter.o: AsciiWriter.cpp
	$(CC) $(CFLAGS) AsciiWriter.cpp
