CXX = g++
CFLAGS = -Wall -pthread #-std=c++0x -g 
DEPGEN = -MM -MD -MP -MG #-std=c++0x

OBJDIR = ./obj
SRCDIR = ./src
BINDIR = ./bin
TESTDIR = ./test
EXE = pal
BISON = bison
FLEX = flex

# If you need to override flex/bison version used, specify 
# in a file named MakefileCustomDefs
# Also, if compiler supports <unordered_map> instead of <tr1/undordered_map>, 
# set CFLAGS += -DNO_TR1 in MakefileCustomDefs
-include MakefileCustomDefs

.PHONY: test clean

################################################################################
# PAL
################################################################################

SRC=$(wildcard $(SRCDIR)/*.cpp)
ALLOBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.cpp=.o)))
OBJS = $(filter-out $(OBJDIR)/main.o, $(ALLOBJS))
DEP=$(OBJS:.o=.d)

all: $(BINDIR)/$(EXE) asc

$(BINDIR)/$(EXE): $(OBJDIR)/main.o $(OBJS)
	$(CXX) -o $@ $^

-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(DEPGEN) -o $(@:.o=.d) -c $<
	$(CXX) $(CFLAGS) -o $@ -c $<

# Lexer/Parser source generation...
FLEXSOURCE := $(SRCDIR)/pal.lex
BISONSOURCE := $(SRCDIR)/pal.y

FLEXDEP := $(FLEXSOURCE:.lex=.lex.ad)
BISONDEP := $(BISONSOURCE:.y=.y.ad)

$(FLEXDEP): %.lex.ad: %.lex
	$(FLEX) -o $(SRCDIR)/lex.yy.cpp $<;\
	if [ $$? -eq 0 ]; then\
       		touch $@;\
	else\
       		rm $(SRCDIR)/lex.yy.cpp;\
	fi

$(BISONDEP): %.y.ad: %.y
	$(BISON) -o $(SRCDIR)/pal.tab.cpp $<;\
	if [ $$? -eq 0 ]; then\
       		touch $@;\
	else\
       		rm $(SRCDIR)/pal.tab.cpp;\
	fi

ifeq (,$(filter clean,$(MAKECMDGOALS)))
-include $(FLEXDEP) $(BISONDEP)
endif

################################################################################
# ASC
################################################################################

asc: bin/asc
bin/asc: asc/asc.c
	gcc asc/asc.c -o bin/asc

################################################################################
# Tests
################################################################################

# Add new tests here. Test % must be in file $(TESTDIR)/%.cpp
TESTS = ScannerTest ParserTest ParserTestWithFiles SymbolTableTest MeowlibTest

TESTS_ = $(addprefix $(TESTDIR)/,$(TESTS))

TEST_OBJS = $(addsuffix .o, $(TESTS_))

# GTEST library, any mock objects, PAL objects
TEST_SUPPORT_OBJS = $(TESTDIR)/test-main.a\
					$(TESTDIR)/MockScanner.o\
					$(OBJS)

test: asc $(TESTDIR)/AllTests $(TEST_)
	-$(TESTDIR)/AllTests

$(TESTDIR)/AllTests: $(TEST_OBJS) $(TEST_SUPPORT_OBJS) 
	-$(CXX) $(CFLAGS) -o $@ $^

# Test utilities

$(TESTDIR)/MockScanner.o: $(TESTDIR)/MockScanner.cpp
	$(CXX) $(DEPGEN) -o $(@:.o=.d) -c $<
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

$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
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

tar: 	
	cd .. ;\
	tar czf meow-pal-compiler.tgz --exclude='.*'--exclude-vcs meow-pal-compiler;\
	cd meow-pal-compiler

doc: doc.pdf

doc.pdf: doc/pal.tex
	cd doc;\
	./makefigures.sh;\
	pdflatex ./pal.tex;\
	cd ..

clean:
	rm -f \
		$(OBJDIR)/* \
		$(BINDIR)/* \
		$(FLEXDEP) \
		$(BISONDEP) \
		$(SRCDIR)/pal.tab.cpp\
		$(SRCDIR)/pal.tab.hpp\
		$(SRCDIR)/position.hh\
		$(SRCDIR)/stack.hh\
		$(SRCDIR)/location.hh\
		$(SRCDIR)/lex.yy.cpp\
		$(TESTDIR)/*.a \
		$(TESTDIR)/*.o \
		$(TESTDIR)/*.d \
		$(TESTDIR)/AllTests \
		$(TESTDIR)/ParserTestWithFiles.cpp \
		$(addprefix $(TESTDIR)/,$(TESTS))
