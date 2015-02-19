LIBS=-lglut -lGLU -lGL -lm
CFLG=-O3 -Wall 

libs/%.a:
	cd libs/$* && make all

LIB_NAMES=dj_callbacks dj_resources dj_globals dj_scene dj_cscix2329 
DJ_LIBS=$(foreach lib,$(LIB_NAMES),libs/$(lib).a)

main.o:main.c dj.h
	gcc -c $^ $(CFLG) $(LIBS)

main : main.o $(DJ_LIBS)
	gcc dj.h $^ $(LIBS) $(CFLG) -o $@

all: clean main

clean:
	find ./ -iregex '.*~' -delete
	find ./ -iregex '.*.o' -delete
	find ./ -iregex '.*.a' -delete
	find ./ -iregex '.*.gch' -delete
	rm -rf main
