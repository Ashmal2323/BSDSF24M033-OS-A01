# src/Makefile — builds client, client_static, client_dynamic, and installs

CC = gcc
CFLAGS = -Wall -I../include
OBJDIR = ../obj
BINDIR = ../bin
LIBDIR = ../lib
PREFIX = /usr/local

TARGET = $(BINDIR)/client
STATIC_TARGET = $(BINDIR)/client_static
DYNAMIC_TARGET = $(BINDIR)/client_dynamic

STATIC_LIB = $(LIBDIR)/libmyutils.a
DYNAMIC_LIB = $(LIBDIR)/libmyutils.so

SOURCES = mystrfunctions.c myfilefunctions.c main.c
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

LIB_OBJECTS = $(OBJDIR)/mystrfunctions.o $(OBJDIR)/myfilefunctions.o
PIC_OBJECTS = $(OBJDIR)/mystrfunctions_pic.o $(OBJDIR)/myfilefunctions_pic.o

.PHONY: all clean static dynamic install

all: $(TARGET)

static: $(STATIC_TARGET)

dynamic: $(DYNAMIC_TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

$(STATIC_LIB): $(LIB_OBJECTS)
	ar rcs $(STATIC_LIB) $(LIB_OBJECTS)

$(STATIC_TARGET): $(OBJDIR)/main.o $(STATIC_LIB)
	$(CC) $(CFLAGS) $(OBJDIR)/main.o $(STATIC_LIB) -o $(STATIC_TARGET)

$(DYNAMIC_LIB): $(PIC_OBJECTS)
	$(CC) --shared -o $(DYNAMIC_LIB) $(PIC_OBJECTS)

$(DYNAMIC_TARGET): $(OBJDIR)/main.o $(DYNAMIC_LIB)
	$(CC) $(CFLAGS) $(OBJDIR)/main.o -L$(LIBDIR) -lmyutils -o $(DYNAMIC_TARGET)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%_pic.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

install: $(DYNAMIC_TARGET) $(DYNAMIC_LIB)
	install -d $(PREFIX)/bin
	install -d $(PREFIX)/lib
	install -d $(PREFIX)/man/man3
	install -m 755 $(DYNAMIC_TARGET) $(PREFIX)/bin/client
	install -m 755 $(DYNAMIC_LIB) $(PREFIX)/lib
	install -m 644 ../man/man3/*.3 $(PREFIX)/man/man3
	ldconfig

clean:
	rm -f $(OBJDIR)/*.o $(TARGET) $(STATIC_TARGET) $(DYNAMIC_TARGET) $(STATIC_LIB) $(DYNAMIC_LIB)
