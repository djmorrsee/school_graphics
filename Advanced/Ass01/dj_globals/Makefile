LIBS=-lglut -lGLU -lGL -lm
CFLG=-O3 -Wall

LIB_NAME=dj_globals

FILENAMES = glob_var glob_const
BINARIES = $(foreach name,$(FILENAMES), bin/$(name).o)
HEADERS = $(foreach name,$(FILENAMES), $(name).h)

$(LIB_NAME).a:$(BINARIES) $(HEADERS)
	ar -rcs ../lib/$@ $^

bin/%.o : %.c
	gcc -c $(CFLG) $< -o $@

all: $(LIB_NAME).a
	
clean:
	rm -rf *~
	rm -rf bin/*.o
	rm -rf ../lib/$(LIB_NAME).a
