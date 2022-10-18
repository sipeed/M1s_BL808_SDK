#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

#include "FreeRTOS_POSIX.h"
#include <time.h>
#include <sys/_timeval.h>

struct timezone {
  int tz_minuteswest; /* Minutes west of GMT.  */
  int tz_dsttime;     /* Nonzero if DST is ever in effect.  */
};

int gettimeofday(struct timeval *tv, struct timezone *tz);

#endif
