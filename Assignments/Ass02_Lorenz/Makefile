CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm

CLEAN=rm -f lorenz *.o *.a

lorenz:lorenz_gl.c
	gcc -O3 -o $@ $^ $(LIBS)

clean:
	$(CLEAN)
