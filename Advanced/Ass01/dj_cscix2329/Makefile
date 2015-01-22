LIBS=-lglut -lGLU -lGL -lm
CFLG=-O3 -Wall

LIB_NAME=dj_cscix2329

FILENAMES = elapsed errcheck fatal loadtexbmp noise object print project shader
BINARIES = $(foreach name,$(FILENAMES), bin/$(name).o)

$(LIB_NAME).a:$(BINARIES)
	ar -rcs ../lib/$@ $^

bin/%.o : %.c
	gcc -c $(CFLG) $< -o $@

all: $(LIB_NAME).a
	
clean:
	rm -rf *~
	rm -rf bin/*.o
	rm -rf ../lib/$(LIB_NAME).a
