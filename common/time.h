#ifndef DBKEYS_COMMON_STRUCTS_TIME_H_
#define DBKEYS_COMMON_STRUCTS_TIME_H_

#include <time.h>
#include <sys/time.h>
#include <stdio.h>

#define timerstart(stringid) struct timeval start = start_stopwatch()
#define timerstop(stringid) end_stopwatch(start, stringid)

struct timeval start_stopwatch();
unsigned long long end_stopwatch(struct timeval tm1, char *msg);

#endif // DBKEYS_COMMON_STRUCTS_TIME_H_