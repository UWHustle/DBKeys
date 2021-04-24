#ifndef DBKEYS_COMMON_MACROS_H_
#define DBKEYS_COMMON_MACROS_H_

#define debug_printf(...) \
            do { if (DEBUG_PRINTS_FLAG) fprintf(stdout, __VA_ARGS__); } while (0)

#endif //DBKEYS_COMMON_MACROS_H_
