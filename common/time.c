#include <stdint.h>
#include <inttypes.h>

#include "time.h"
#include "macros.h"

#if GEM5
#define STATS_CSR 0x7C1
#define CPK_CSR 0x800

inline void ckp_set(uint64_t val) {
  __asm__ __volatile__(
  "csrrw %[val], %[stats], %[val] \n\t"
  : [val] "+r"(val)
  : [stats] "i"(CPK_CSR)
  );
}

inline uint64_t cycles() {
  uint64_t ctr;

  __asm__ __volatile__(
  "rdcycle %[ctr] \n\t"
  : [ctr] "=r"(ctr)
  :
  );

  return ctr;
}

inline void stats_set(uint64_t val) {
  __asm__ __volatile__(
  "csrrw %[val], %[stats], %[val] \n\t"
  : [val] "+r"(val)
  : [stats] "i"(STATS_CSR)
  );
}

inline void roi_start() {
  stats_set(1);
}

inline void roi_end() {
  stats_set(0);
}
void start_stopwatch() {
  debug_printf("GEM5 time: ");
  roi_start();
}

void end_stopwatch() {
  debug_printf("GEM5 time:");
  roi_end();
}
#else
struct timeval start_stopwatch() {
  debug_printf("Timer start\n");
  struct timeval start;
  gettimeofday(&start, NULL);
//  printf("start %ld\n", start.tv_sec);
  return start;
}

unsigned long long end_stopwatch(struct timeval tm1, char *msg) {
  debug_printf("Timer stop\n");
  struct timeval tm2;
  gettimeofday(&tm2, NULL);
  unsigned long long t =
      1000 * (tm2.tv_sec - tm1.tv_sec) + (tm2.tv_usec - tm1.tv_usec) / 1000;
  printf("Time taken for %s, %llu ms\n", msg, t);
  return t;
}

#endif
