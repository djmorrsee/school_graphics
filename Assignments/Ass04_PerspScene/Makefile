CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm

CLEAN=rm -f scene *.o *.a

all: perspscene vert dj_primitives
	gcc perspscene.o vert.o dj_primitives.o -o scene $(LIBS)

perspscene: perspscene.c
	gcc -c $<

vert:vert.c
	gcc -c $<

dj_primitives:dj_primitives.c
	gcc $(CFLG) -c $<

clean:
	$(CLEAN)
