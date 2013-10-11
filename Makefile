LOBJS = pal.tab.o lex.yy.o error.o errormanager.o
OBJS = $(addprefix $(OBJDIR)/,$(LOBJS))
CC = g++
CXX = g++
CFLAGS = -g -Wall -pthread
OBJDIR = ./obj
SRCDIR = ./src
BINDIR = ./bin
TESTDIR = ./test
EXE = pal
BISON = bison
FLEX = flex

# If you need to override flex/bison version used, specify 
# in a file named MakefileCustomDefs
-include MakefileCustomDefs

.PHONY: test clean

################################################################################
# PAL
################################################################################

all: pal test

pal: $(OBJDIR)/main.o $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(EXE) $^

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/Scanner.hpp $(SRCDIR)/pal.tab.h
	$(CC) -c -o $@ $<

$(OBJDIR)/error.o: $(SRCDIR)/error.cpp $(SRCDIR)/error.hpp
	$(CC) -c -o $@ $<

$(OBJDIR)/errormanager.o: 	$(SRCDIR)/errormanager.cpp 	\
							$(SRCDIR)/errormanager.hpp 	\
							$(SRCDIR)/error.hpp 		\
							$(SRCDIR)/error.cpp 
	$(CC) -c -o $@ $<

$(OBJDIR)/pal.tab.o: $(SRCDIR)/pal.tab.c $(SRCDIR)/pal.tab.h $(SRCDIR)/Parser.hpp
	$(CC) -c -o $@ $<

$(OBJDIR)/lex.yy.o: $(SRCDIR)/lex.yy.cc 
	$(CC) -c -o $@ $<

$(SRCDIR)/lex.yy.cc: $(SRCDIR)/pal.lex $(SRCDIR)/Scanner.hpp
	$(FLEX) -o $@ $(SRCDIR)/pal.lex

$(SRCDIR)/pal.tab.h: $(SRCDIR)/pal.y $(SRCDIR)/Parser.hpp
	$(BISON) -o $@ $(SRCDIR)/pal.y 

$(SRCDIR)/pal.tab.c: $(SRCDIR)/pal.y $(SRCDIR)/Parser.hpp
	$(BISON) -o $@ $(SRCDIR)/pal.y

################################################################################
# Tests
################################################################################

TESTS = ScannerTest ParserTest

test: $(TESTDIR)/AllTests $(addprefix $(TESTDIR)/,$(TESTS))
	$(TESTDIR)/AllTests

# Link all tests together into one big super test executable
$(TESTDIR)/AllTests: $(TESTDIR)/ParserTest.o 		\
						$(TESTDIR)/ScannerTest.o	\
						$(TESTDIR)/MockScanner.o	\
						$(OBJS)						\
						$(TESTDIR)/test-main.a
	$(CXX) $(CFLAGS) -o $@ $^

	

# Parser Test
ParserTest: $(TESTDIR)/ParserTest
	$^

$(TESTDIR)/ParserTest: $(TESTDIR)/ParserTest.o 		\
						$(TESTDIR)/MockScanner.o	\
						$(OBJS)						\
						$(TESTDIR)/test-main.a
	$(CXX) $(CFLAGS) -o $@ $^
	
$(TESTDIR)/ParserTest.o: $(TESTDIR)/ParserTest.cpp $(SRCDIR)/pal.lex $(SRCDIR)/pal.y
	$(CXX) $(CFLAGS) -c -o $@ $<

# Scanner Test
ScannerTest: $(TESTDIR)/ScannerTest
	$^

$(TESTDIR)/ScannerTest: 	$(TESTDIR)/ScannerTest.o 	\
							$(OBJS)						\
							$(TESTDIR)/test-main.a
	$(CXX) $(CFLAGS) -o $@ $^

$(TESTDIR)/ScannerTest.o: $(TESTDIR)/ScannerTest.cpp $(SRCDIR)/pal.lex $(SRCDIR)/Scanner.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<

# Test utilities

$(TESTDIR)/MockScanner.o: $(TESTDIR)/MockScanner.cpp $(SRCDIR)/pal.lex $(SRCDIR)/Scanner.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TESTDIR)/test-main.a : $(TESTDIR)/gmock-gtest-all.o $(TESTDIR)/gmock_main.o
	$(AR) $(ARFLAGS) $@ $^

$(TESTDIR)/gmock-gtest-all.o: $(TESTDIR)/gmock-gtest-all.cc
	$(CXX) $(CFLAGS) -o $@ -c $^

$(TESTDIR)/gmock-main.o: $(TESTDIR)/gmock_main.cc
	$(CXX) $(CFLAGS) -o $@ -c $^

################################################################################

clean:
	rm -f \
		$(OBJDIR)/* \
		$(BINDIR)/* \
		$(SRCDIR)/pal.tab.c\
		$(SRCDIR)/pal.tab.h\
		$(SRCDIR)/position.hh\
		$(SRCDIR)/stack.hh\
		$(SRCDIR)/location.hh\
		$(SRCDIR)/lex.yy.cc\
		$(TESTDIR)/*.a \
		$(TESTDIR)/*.o \
		$(addprefix $(TESTDIR)/,$(TESTS))
