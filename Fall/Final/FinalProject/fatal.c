/*
 * fatal.c
 *
 *  Created on: Dec 7, 2014
 *      Author: djmorrsee
 */

#include "dj.h"

void Fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}
