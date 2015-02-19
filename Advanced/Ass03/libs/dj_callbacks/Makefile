LIBS=-lglut -lGLU -lGL -lm
CFLG=-O3 -Wall

LIB_NAME=dj_callbacks

FILENAMES = display key mouse_move reshape special projection
BINARIES = $(foreach name,$(FILENAMES), bin/$(name).o)

$(LIB_NAME).a:$(BINARIES)
	ar -rcs ../$@ $^ ../../dj.h

bin/%.o : %.c
	@gcc -c $(CFLG) $< -o $@

all: $(LIB_NAME).a
