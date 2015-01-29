LIBS=-lglut -lGLU -lGL -lm
CFLG=-O3 -Wall -g

LIB_NAME=dj_cscix2329

FILENAMES = shader elapsed errcheck fatal loadtexbmp noise object print project
BINARIES = $(foreach name,$(FILENAMES), bin/$(name).o)

$(LIB_NAME).a:$(BINARIES)
	ar -rcs ../$@ $^ ../../dj.h

bin/%.o : %.c
	gcc -c $(CFLG) $< -o $@

all: $(LIB_NAME).a
