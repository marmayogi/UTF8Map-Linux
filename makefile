# --------------------------------------------------------------------
#
# This makefile for Linux was written on Nov 4, 2022 by Marmayogi, Astrologer and Palmist, Sri Mahakali Jothida Nilayam, Coimbatore, India.
#
# Usage-1:
#	Invocation of make from terminal: without any command line arguments or with one argument "all" as follows:
#
#	$ make
#	or
#	$ make all
#		
# 	The above commands will create "utf8map" which is an executable binary file.
#
# Usage-2:
#	Invocation of make from terminal, with a command line argument "clean", as follows:
#
#	$ make clean
#		
# 	This will delete the following:
#		- utf8map executable binary
#		- main.o
#
# --------------------------------------------------------------------

objects = main.o
CC = g++
CFLAGS  = -g -Wall

all: UTF8Map

UTF8Map:  $(objects)
	$(CC) $(CFLAGS) -o utf8map $(objects)

main.o: main.cpp mapunicode.h
	$(CC) $(CFLAGS) -c main.cpp

clean:
	@rm utf8map $(objects)
