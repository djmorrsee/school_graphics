CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm

SCENENAME=light_scene

CLEAN=rm -f $(SCENENAME) *.o *.a

all:lightscene

lightscene:lightscene.c face vert dj_primitives
	gcc $(CFLG) $< face.o vert.o dj_primitives.o -o $(SCENENAME) $(LIBS)

dj_primitives: dj_primitives.c
	gcc -c $<

face: face.c
	gcc -c $<

vert:vert.c
	gcc -c $<

clean:
	$(CLEAN)
