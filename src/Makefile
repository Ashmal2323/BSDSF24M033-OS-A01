# src/Makefile — does the actual compiling and linking

CC = gcc
CFLAGS = -Wall -I../include
OBJDIR = ../obj
BINDIR = ../bin
TARGET = $(BINDIR)/client

SOURCES = mystrfunctions.c myfilefunctions.c main.c
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
