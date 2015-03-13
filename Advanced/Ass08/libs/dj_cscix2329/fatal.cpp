/*
 * Adopted from CSCIx2329 Library, found in ex01 on 1/21/2015 by Daniel Morrissey
 *
 *  Print message to stderr and exit
 */
#include "../../dj.h"

void Fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}
