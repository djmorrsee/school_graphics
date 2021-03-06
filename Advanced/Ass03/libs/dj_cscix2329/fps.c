/*
 * Adopted from CSCIx2329 Library, found in ex01 on 1/21/2015 by Daniel Morrissey
 *
 *  Frames per seconds
 */
#include "../../dj.h"

static int fps=0,sec0=0,count=0;
int FramesPerSecond(void)
{
   int sec = glutGet(GLUT_ELAPSED_TIME)/1000;
   if (sec!=sec0)
   {
      sec0 = sec;
      fps = count;
      count=0;
   }
   count++;
   return fps;
}
