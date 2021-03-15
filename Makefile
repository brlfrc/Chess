# Chess Makefile based on
# https://www.softwaretestinghelp.com/cpp-makefile-tutorial/
 
# *****************************************************
# Variables to control Makefile operation

# Compiler 
CC = g++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS = -Wall -g

# The build target 
TARGET = chess

# ****************************************************
# Targets needed to bring the executable up to date
all:
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp my_board.h my_chess.h my_piece.h

clean:
	rm $(TARGET)
 
