LIBS=-lglut -lGLU -lGL -lm
CFLG=-O3 -Wall

LIB_NAME=dj_resources

FILENAMES = shaders textures
BINARIES = $(foreach name,$(FILENAMES), bin/$(name).o)
HEADERS = $(foreach name,$(FILENAMES), $(name).h)

$(LIB_NAME).a:$(BINARIES) $(HEADERS)
	ar -rcs ../$@ $^ ../../dj.h

bin/%.o : %.c
	gcc -c $(CFLG) $< -o $@

all: $(LIB_NAME).a
