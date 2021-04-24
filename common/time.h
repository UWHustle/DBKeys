#ifndef HUSTLE_APPS_HUSTLE_APPS_TATP_TATP_UTILS_TIME_H_
#define HUSTLE_APPS_HUSTLE_APPS_TATP_TATP_UTILS_TIME_H_

#include <time.h>
#include <sys/time.h>
#include <stdio.h>

#if GEM5
#define timerstart(stringid) start_stopwatch()
#define timerstop(stringid) end_stopwatch(stringid)
#elif EMULATED
#define timerstart(stringid) start_emulator_roi(stringid)
#define timerstop(stringid) end_emulator_roi()
#else
#define timerstart(stringid) struct timeval start = start_stopwatch()
#define timerstop(stringid) end_stopwatch(start, stringid)
#endif

#if GEM5
void start_stopwatch();
void end_stopwatch();
#else
struct timeval start_stopwatch();
unsigned long long end_stopwatch(struct timeval tm1, char *msg);
#endif

#endif