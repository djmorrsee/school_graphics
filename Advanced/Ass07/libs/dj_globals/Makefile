LIBS=-lglut -lGLU -lGL -lm
CFLG=-O3 -Wall

LIB_NAME=dj_globals

FILENAMES = glob_var glob_const
BINARIES = bin/glob_var.o
HEADERS = $(foreach name,$(FILENAMES), $(name).h)

$(LIB_NAME).a:$(BINARIES) $(HEADERS)
	ar -rcs ../$@ $^ 

bin/%.o : %.cpp
	g++ -c $(CFLG) $< -o $@

all: $(LIB_NAME).a
