/*
 * Adopted from CSCIx2329 Library, found in ex01 on 1/21/2015 by Daniel Morrissey
 *
 *  Check for OpenGL errors
 */
#include "../../dj.h"

void ErrCheck(const char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}
