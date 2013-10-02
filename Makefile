LOBJS = pal.tab.o lex.yy.o main.o
OBJS = $(addprefix $(OBJDIR)/,$(LOBJS))
CC = g++
CXX = g++
CFLAGS = -g -Wall
OBJDIR = ./obj
SRCDIR = ./src
BINDIR = ./bin
TESTDIR = ./test
EXE = pal
BISON = bison
FLEX = flex
# If using Homebrew ...
#BISON = /usr/local/Cellar/bison/3.0/bin/bison
#FLEX = /usr/local/Cellar/flex/2.5.37/bin/flex

.PHONY: test clean

################################################################################
# PAL
################################################################################

all: pal test

pal: $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(EXE) $(OBJS)

$(OBJDIR)/pal.tab.h: $(SRCDIR)/pal.y
	cp $(SRCDIR)/Scanner.hpp $(OBJDIR)/
	cp $(SRCDIR)/Parser.hpp $(OBJDIR)/
	$(BISON) -o $@ $(SRCDIR)/pal.y 

$(OBJDIR)/pal.tab.c: $(SRCDIR)/pal.y
	cp $(SRCDIR)/Scanner.hpp $(OBJDIR)/
	cp $(SRCDIR)/Parser.hpp $(OBJDIR)/
	$(BISON) -o $@ $(SRCDIR)/pal.y

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	cp $^ $(OBJDIR)/
	$(CC) -c -o $@ $(OBJDIR)/$(<F)

$(OBJDIR)/lex.yy.o: $(OBJDIR)/lex.yy.cc $(OBJDIR)/pal.tab.h $(SRCDIR)/Scanner.hpp

$(OBJDIR)/lex.yy.cc: $(SRCDIR)/pal.lex
	$(FLEX) -o $@ $(SRCDIR)/pal.lex

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
		$(TESTDIR)/*.a \
		$(TESTDIR)/*.o \
		$(addprefix $(TESTDIR)/,$(TESTS))
