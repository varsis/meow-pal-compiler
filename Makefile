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

# List all object files to be generated and linked here
# Must match name of source CPP for automatic rule to catch
LOBJS = pal.tab.o\
	lex.yy.o\
	Error.o\
	ErrorManager.o\
	Compiler.o\
	Parser.o

OBJS = $(addprefix $(OBJDIR)/,$(LOBJS))

# For simplicity, just make (almost) everything depend on everything in the source folder

SRCDEPS = $(SRCDIR)/* \
		  $(SRCDIR)/lex.yy.cc \
		  $(SRCDIR)/pal.tab.h \
		  $(SRCDIR)/pal.tab.c

all: pal

pal: $(OBJDIR)/main.o $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(EXE) $^

$(OBJDIR)/pal.tab.o: $(SRCDIR)/pal.tab.c $(SRCDEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/lex.yy.o: $(SRCDIR)/lex.yy.cc  $(SRCDEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Lexer/Parser source generation...

$(SRCDIR)/lex.yy.cc: $(SRCDIR)/pal.lex $(SRCDIR)/Scanner.hpp $(SRCDIR)/pal.tab.h
	$(FLEX) -o $@ $(SRCDIR)/pal.lex

$(SRCDIR)/pal.tab.h: $(SRCDIR)/pal.y $(SRCDIR)/Parser.hpp
	$(BISON) -o $@ $(SRCDIR)/pal.y 

$(SRCDIR)/pal.tab.c: $(SRCDIR)/pal.y $(SRCDIR)/Parser.hpp
	$(BISON) -o $@ $(SRCDIR)/pal.y

################################################################################
# Tests
################################################################################

# Add new tests here. Test % must be in file $(TESTDIR)/%.cpp
TESTS = ScannerTest ParserTest ParserTestWithFiles Checkpoint1Tests

TESTS_ = $(addprefix $(TESTDIR)/,$(TESTS))

TEST_OBJS = $(addsuffix .o, $(TESTS_))

# GTEST library, any mock objects, PAL objects
TEST_SUPPORT_OBJS = $(TESTDIR)/test-main.a\
					$(TESTDIR)/MockScanner.o\
					$(OBJS)

TEST_SUPPORT_SRCS = $(TESTDIR)/MockScanner.cpp\
					$(TESTDIR)/MockScanner.h

test: $(TESTDIR)/AllTests $(TEST_)
	-$(TESTDIR)/AllTests

$(TESTDIR)/AllTests: $(TEST_OBJS) $(TEST_SUPPORT_OBJS) 
	-$(CXX) $(CFLAGS) -o $@ $^

# Test utilities

$(TESTDIR)/MockScanner.o: $(TESTDIR)/MockScanner.cpp $(SRCDEPS)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TESTDIR)/test-main.a : $(TESTDIR)/gmock-gtest-all.o $(TESTDIR)/gmock_main.o
	$(AR) $(ARFLAGS) $@ $^

$(TESTDIR)/gmock-gtest-all.o: $(TESTDIR)/gmock-gtest-all.cc
	$(CXX) $(CFLAGS) -o $@ -c $^

$(TESTDIR)/gmock-main.o: $(TESTDIR)/gmock_main.cc
	$(CXX) $(CFLAGS) -o $@ -c $^

# Individual tests:

$(TESTS): % : $(TESTDIR)/%
	-$^

$(TESTDIR)/%.o: $(TESTDIR)/%.cpp $(SRCDEPS) $(TEST_SUPPORT_SRCS)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TESTDIR)/%: $(TESTDIR)/%.o $(TEST_SUPPORT_OBJS)
	$(CXX) $(CFLAGS) -o $@ $^

# Generated tests:
$(TESTDIR)/ParserTestWithFiles.cpp: $(TESTDIR)/test_cases/*.pal $(TESTDIR)/scripts/test_gen
	cd ./test/scripts && ./test_gen && cd ../../

################################################################################
# Documentation
################################################################################

man:
	nroff -man doc/pal.1 | less


zip: 	
	cd .. ;\
	tar czf meow-pal-compiler.tgz --exclude='.*'--exclude-vcs meow-pal-compiler;\
	cd meow-pal-compiler

doc: doc.pdf
doc.pdf: doc/pal.tex
	cd doc;\
	epstopdf *.eps;\
	pdflatex ./pal.tex;\
	cd ..

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
		$(TESTDIR)/AllTests \
		$(TESTDIR)/ParserTestWithFiles.cpp \
		$(addprefix $(TESTDIR)/,$(TESTS))
