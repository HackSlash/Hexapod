#Compiles to vision file from ../cpp/ & coppies it to this directory
#very simple Makefile created by HackSlash
CC=g++
CFLAGS=-g -Wall

IFILE=../cpp/test.cpp
OFILE=Vision

vision:
	$(CC) $(CFLAGS) -o $(OFILE) $(IFILE)

.PHONY: clean

clean:
	rm -f Vision