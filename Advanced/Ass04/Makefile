LIBS=-lGL -lGLU -lm -lglut -lpthread
CFLG=-O3 -Wall

.PHONY: all clean

libs/%.a:
	cd libs/$* && make all

LIB_NAMES=dj_callbacks dj_globals dj_cscix2329 dj_scene dj_resources
DJ_LIBS=$(foreach lib,$(LIB_NAMES),libs/$(lib).a)

#~ main.o:main.c dj.h
	#~ gcc -c $^ $(CFLG) $(LIBS)
#~ 
#~ main : main.o $(DJ_LIBS)
	#~ gcc dj.h $^ $(LIBS) $(CFLG) -o $@

.ccp.o:
	g++ -c $(CFLG) $<

main.o:main.cpp
	g++ -c $(CFLG) $< 

main:main.o $(DJ_LIBS)
	g++ main.o -o main $(CFLG) $(GLFWLIBS) $(DJ_LIBS) $(LIBS)

all: clean main

clean:
	find ./ -iregex '.*~' -delete
	find ./ -iregex '.*.o' -delete
	find ./libs/ -iregex '.*.a' -delete
	find ./ -iregex '.*.gch' -delete
	rm -rf main
