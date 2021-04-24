#ifndef CASTLE_HUSTLE_APPS_SSB_UTILS_MACROS_H_
#define CASTLE_HUSTLE_APPS_SSB_UTILS_MACROS_H_

#define debug_printf(...) \
            do { if (DEBUG_PRINTS_FLAG) fprintf(stdout, __VA_ARGS__); } while (0)

#endif //CASTLE_HUSTLE_APPS_SSB_UTILS_MACROS_H_
