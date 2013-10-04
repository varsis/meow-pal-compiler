LOBJS = pal.tab.o lex.yy.o main.o
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
# If using custum bison / flex version...
BISON = ~/bin/bison
FLEX = /usr/local/Cellar/flex/2.5.37/bin/flex

.PHONY: test clean

################################################################################
# PAL
################################################################################

all: pal test

pal: $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(EXE) $(OBJS)

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/Scanner.hpp
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

TESTS = ScannerTest

test: $(addprefix $(TESTDIR)/,$(TESTS))
	$(addprefix $(TESTDIR)/./, $(TESTS))

$(TESTDIR)/ScannerTest: $(TESTDIR)/ScannerTest.o $(OBJDIR)/lex.yy.o $(TESTDIR)/test-main.a
	$(CXX) $(CFLAGS) -o $@ $^

$(TESTDIR)/ScannerTest.o: $(TESTDIR)/ScannerTest.cc $(SRCDIR)/pal.lex $(SRCDIR)/Scanner.hpp
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
