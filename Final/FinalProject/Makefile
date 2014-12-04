LIBS=-lglut -lGLU -lGL -lm
CFLG=-O3 -Wall

# Global Constants and Variables
glob_const.o	:glob_const.c glob_const.h
glob_var.o		:glob_var.c glob_var.h

dj_globals=glob_const.o glob_var.o

# GLUT Callback Files
key.o			:key.c dj.h
display.o		:display.c dj.h
reshape.o		:reshape.c dj.h
special.o		:special.c dj.h
idle.o			:idle.c dj.h
mouse_move.o	:mouse_move.c dj.h
motion.o		:motion.c motion.h dj.h

dj_callbacks=key.o display.o reshape.o special.o idle.o motion.o mouse_move.o

# Utility Files 
print.o			:print.c dj.h
projection.o	:projection.c dj.h
dj_structures.o	:dj_structures.c dj.h
dj_primitives.o	:dj_primitives.c dj.h
lighting.o		:lighting.c lighting.h dj.h


dj_utility=print.o projection.o dj_structures.o dj_primitives.o lighting.o

# Main
main.o			:main.c dj.h

dj.a: $(dj_utility) $(dj_globals) $(dj_callbacks) 
	ar -rcs $@ $^

.c.o:
	gcc -c $(CFLG) $<

main:main.o dj.a
	gcc -O3 -o $@ $^ $(LIBS)

all: clean main
clean:
	rm -f *.o
	rm -f *.a
	rm -f main
	rm -f *~
