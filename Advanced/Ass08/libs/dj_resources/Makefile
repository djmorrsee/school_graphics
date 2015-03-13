LIBS=-lglut -lGLU -lGL -lm
CFLG=-O3 -Wall

LIB_NAME=dj_resources

FILENAMES = objects shaders textures
BINARIES = $(foreach name,$(FILENAMES), bin/$(name).o)
HEADERS = $(foreach name,$(FILENAMES), $(name).h)

$(LIB_NAME).a:$(BINARIES)
	ar -rcs ../$@ $^ $(HEADERS) ../../dj.h

bin/%.o : %.cpp
	gcc -c $(CFLG) $< -o $@

all: $(LIB_NAME).a
