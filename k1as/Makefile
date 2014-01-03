#!/bin/bash
#***************************************************************************************************************
# FILE: Makefile
#
# DESCRIPTION
# Make file for the K1 Assembler project.
#
# AUTHOR INFORMATION
# Kevin R. Burger [KRB]
#
# Mailing Address:
# Computer Science & Engineering
# School of Computing, Informatics, and Decision Systems Engineering
# Arizona State University
# Tempe, AZ 85287-8809
#
# Email: burgerk@asu
# Web:   http://kevin.floorsoup.com
#***************************************************************************************************************
BINARY = k1as

# -c         : Compile a .cpp file only to produce the .o file.
# -g         : Put debugging information in the .o file. Used by the GDB debugger.
# -O0        : Turn off all optimization. Necessary if you are going to debug using GDB.
# -std=c99   : The code must conform to the C99 standard.
# -Wall      : Turn on all warnings. Your code should compile with no errors or warnings.
CFLAGS = -c -g -O0 -std=c99 -Wall

# -c         : Compile a .cpp file only to produce the .o file.
# -g         : Put debugging information in the .o file. Used by the GDB debugger.
# -O0        : Turn off all optimization. Necessary if you are going to debug using GDB.
# -std=c++98 : The code must conform to the C++ 98 standard.
# -Wall      : Turn on all warnings. Your code should compile with no errors or warnings.
CPPFLAGS = -c -g -O0 -std=c++98 -Wall

SOURCES = Arg.cpp          \
          Binary.cpp       \
          DataSegment.cpp  \
          Instr.cpp        \
          InstrTypeB.cpp   \
          InstrTypeR.cpp   \
          InstrTypeRI.cpp  \
          InstrTypeRV.cpp  \
          Integer.cpp      \
          K1as.cpp         \
          Label.cpp        \
          Lex.cpp          \
          Main.cpp         \
          OBinStream.cpp   \
          Operand.cpp      \
          Register.cpp     \
          Segment.cpp      \
          TextSegment.cpp  \
          Variable.cpp

OBJECTS = $(SOURCES:.cpp=.o)

$(BINARY): $(OBJECTS)
	g++ $(OBJECTS) -o $(BINARY)

%.o: %.cpp
	g++ $(CPPFLAGS) $< -o $@

%.d: %.cpp
	rm -f $@; gcc -MM $< > $@

include $(SOURCES:.cpp=.d)

.PHONY: disas
disas: disas.o
	gcc Disas.o -o disas

disas.o: Disas.c
	gcc $(CFLAGS) Disas.c

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f *.d
	rm -f $(BINARY)
	rm -f disas
	rm -f disas.o

