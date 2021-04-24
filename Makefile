SHELL := '/bin/bash'

CC=gcc
CXX=g++

#### FLAGS #################################################################

all: dbkeys

#############################################################################

CHEADERS=common/structs.h \
		 common/time.h \
		 c_kernels/c_kernels.h

CSOURCES=common/time.c \
		 common/structs.c \
         c_kernels/aggregation_kernel.c


#############################################################################

.PHONY: all clean dbkeys

clean:
	rm -rf ./*.o dbkeys

#############################################################################

CFLAGS = -Wall $(ARCH) -O3 $(LDFLAGS) -I./
DEBUG_PRINTS_FLAG_VALUE=1
#############################################################################

dbkeys: CFLAGS+= -D DEBUG_PRINTS_FLAG=$(DEBUG_PRINTS_FLAG_VALUE)
dbkeys: $(CHEADERS) $(CSOURCES) main.c
	 $(CC) -o$@ $(CFLAGS) $(CSOURCES) main.c -lm
