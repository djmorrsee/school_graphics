LIBS=-lGL -lGLU -lm
CFLG=-O3 -Wall
GLFWLIBS=-lX11 -lXxf86vm -lXrandr -lpthread -lXi -lXinerama -lXcursor

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
	g++ main.o -o main GLFW/libglfw3.a $(CFLG) $(GLFWLIBS) $(DJ_LIBS) $(LIBS) GLFW/glfw3.h 

all: clean main

clean:
	find ./ -iregex '.*~' -delete
	find ./ -iregex '.*.o' -delete
	find ./libs/ -iregex '.*.a' -delete
	find ./ -iregex '.*.gch' -delete
	rm -rf main
