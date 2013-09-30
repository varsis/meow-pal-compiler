LOBJS = pal.tab.o lex.yy.o main.o
OBJS = $(addprefix $(OBJDIR)/,$(LOBJS))
CC = g++
CXX = g++
CFLAGS = -g -Wall
OBJDIR = ./obj
SRCDIR = ./src
BINDIR = ./bin
EXE = pal

pal: $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(EXE) $(OBJS)

$(OBJDIR)/pal.tab.h: $(SRCDIR)/pal.y
	cp $(SRCDIR)/Scanner.hpp $(OBJDIR)/
	cp $(SRCDIR)/Parser.hpp $(OBJDIR)/
	bison -o $@ $(SRCDIR)/pal.y 

$(OBJDIR)/pal.tab.c: $(SRCDIR)/pal.y
	cp $(SRCDIR)/Scanner.hpp $(OBJDIR)/
	cp $(SRCDIR)/Parser.hpp $(OBJDIR)/
	bison -o $@ $(SRCDIR)/pal.y

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	cp $^ $(OBJDIR)/
	$(CC) -c -o $@ $(OBJDIR)/$(<F)

$(OBJDIR)/lex.yy.o: $(OBJDIR)/lex.yy.cc $(OBJDIR)/pal.tab.h

$(OBJDIR)/lex.yy.cc: $(SRCDIR)/pal.lex
	flex -o $@ $(SRCDIR)/pal.lex

clean:
	rm -f $(OBJDIR)/* $(BINDIR)/*
