CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm

CLEAN=rm -f simscene *.o *.a

simscene:simscene.c
	gcc -O3 -o $@ $^ $(LIBS)

clean:
	$(CLEAN)
