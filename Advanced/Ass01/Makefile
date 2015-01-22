LIBS=-lglut -lGLU -lGL -lm
CFLG=-O3 -Wall 

lib/%.a:
	cd $* && make all

lib_names = dj_callbacks dj_cscix2329 dj_resources dj_globals dj_scene
libraries = $(foreach lib,$(lib_names),lib/$(lib).a)

# Main
main.o			:main.c dj.h

.c.o:
	gcc -c $(CFLG) $<

main:main.o $(libraries)
	gcc -O3 -o $@ $^ $(LIBS) $(CFLG) 

all: clean main
clean:
	cd dj_callbacks && make clean
	cd dj_cscix2329 && make clean
	cd dj_resources && make clean
	cd dj_globals && make clean
	cd dj_scene && make clean
	rm -rf *.o
	rm -rf *.a
	rm -rf main
	rm -rf *~
	rm -rf *.gch
