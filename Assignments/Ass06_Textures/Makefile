CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm

SCENENAME=texscene

CLEAN=rm -f $(SCENENAME) *.o *.a

all: texscene

print.o: 		print.c 			djgraphics.h
axes.o: 		axes.c 				djgraphics.h
project.o: 		project.c 			djgraphics.h
face.o: 		face.c 				djgraphics.h
vert.o: 		vert.c 				djgraphics.h
dj_primitives.o:dj_primitives.c 	djgraphics.h
loadbmptex.o:	loadbmptex.c		djgraphics.h
light.o:		light.c				djgraphics.h

djgraphics.a: print.o project.o axes.o vert.o face.o dj_primitives.o loadbmptex.o light.o
	ar -rcs $@ $^

texscene:texscene.c djgraphics.a
	gcc $(CFLG) -o $@ $^ $(LIBS)

clean:
	$(CLEAN)
