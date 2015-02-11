LIBS=-lglut -lGLU -lGL -lm
CFLG=-O3 -Wall

LIB_NAME=dj_scene

FILENAMES = motion
BINARIES = $(foreach name,$(FILENAMES), bin/$(name).o)
HEADERS = $(foreach name,$(FILENAMES), $(name).h)

$(LIB_NAME).a:$(BINARIES) $(HEADERS)
	ar -rcs ../$@ $^ ../../dj.h

bin/%.o : %.cpp
	@g++ -c $(CFLG) $< -o $@

all: $(LIB_NAME).a
