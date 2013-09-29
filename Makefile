OBJS = main.o pal.lex.o pal.bison.o
CC = g++
CFLAGS = -g
OBJDIR = ./obj
SRCDIR = ./src
BINDIR = ./bin

pal: $(OBJDIR)/$(OBJS)
	$(CC) -o $(BINDIR)/pal $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c -o $@ $<

pal.lex.cpp: $(SRCDIR)/pal.lex $(SRC)/pal.b
	flex -o $(SRCDIR)/$@ $(SRCDIR)/pal.lex
	
pal.bison.cpp: $(SRCDIR)/pal.b
	bison -o $(SRCDIR)/$@ $(SRCDIR)/pal.b

clean:
	rm -f $(OBJDIR)/* $(BINDIR)/*
