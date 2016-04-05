OUT    := lib/libtiled
CC     := g++
CFLAGS := -std=c++11 -Wall -fpic -O3
ODIR   := obj
LDIR   := lib
SDIR   := src/tiled
INC    := -Iinclude/tiled -Iinclude

SOURCES = $(shell find ./$(SDIR) -name '*.cpp')
OBJS = $(patsubst $(SDIR)/%,$(ODIR)/%,$(SOURCES:./%.cpp=%.o))

all: static shared

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c $(INC) -o $@ $< $(CFLAGS)

$(ODIR)/miniz.o: include/miniz/miniz.c
	$(CC) -c -o $(ODIR)/miniz.o include/miniz/miniz.c $(CFLAGS)

static: $(ODIR)/miniz.o $(OBJS)
	ar rvs $(OUT).a $^

shared: $(ODIR)/miniz.o $(OBJS)
	$(CC) -o $(OUT).so $(ODIR)/*.o $(CFLAGS) -shared $(INC)

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o $(OUT).a $(OUT).so
