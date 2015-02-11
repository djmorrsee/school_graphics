LIBS=-lglut -lGLU -lGL -lm
CFLG=-O3 -Wall -g

LIB_NAME=dj_cscix2329

FILENAMES = shader elapsed fatal loadtexbmp noise object
BINARIES = $(foreach name,$(FILENAMES), bin/$(name).o)

$(LIB_NAME).a:$(BINARIES)
	ar -rcs ../$@ $^ ../../dj.h

bin/%.o : %.cpp
	g++ -c $(CFLG) $< -o $@

all: $(LIB_NAME).a
