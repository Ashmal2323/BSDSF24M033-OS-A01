# src/Makefile — builds bin/client (Phase 2) and bin/client_static (Phase 3)

CC = gcc
CFLAGS = -Wall -I../include
OBJDIR = ../obj
BINDIR = ../bin
LIBDIR = ../lib

TARGET = $(BINDIR)/client
STATIC_TARGET = $(BINDIR)/client_static
STATIC_LIB = $(LIBDIR)/libmyutils.a

SOURCES = mystrfunctions.c myfilefunctions.c main.c
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

LIB_OBJECTS = $(OBJDIR)/mystrfunctions.o $(OBJDIR)/myfilefunctions.o

.PHONY: all clean static

all: $(TARGET)

static: $(STATIC_TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

$(STATIC_LIB): $(LIB_OBJECTS)
	ar rcs $(STATIC_LIB) $(LIB_OBJECTS)

$(STATIC_TARGET): $(OBJDIR)/main.o $(STATIC_LIB)
	$(CC) $(CFLAGS) $(OBJDIR)/main.o -L$(LIBDIR) -lmyutils -o $(STATIC_TARGET)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(TARGET) $(STATIC_TARGET) $(STATIC_LIB)
