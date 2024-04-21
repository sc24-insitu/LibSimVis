#include <dlfcn.h>
#include <limits.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#include "mpi.h"

// Macro Definitions

#ifndef RUN_STANDALONE

    #define stage_open                 nc_open
    #define stage_put_vara_double      nc_put_vara_double
    #define stage_close                nc_close

#endif

#define STAGEDIOLOG "/home/user/Build_WRF/WRF/test/em_real/StageIOLog_%d"
#define WRITELOG "/home/user/Build_WRF/WRF/test/em_real/writeDataLog_%d"

// Global variables
extern int global_key;
extern int shm_id_key;

// User defined structures

typedef struct dimension_data
{
    int ndims;
    int shm_dimlen_id;
    size_t *dim_len;
} Dimdata;

extern FILE *stagedIOLog, *writeDataLog;

int stage_open(const char *fname, unsigned int flags, int *ncid);
int stage_put_vara_double(int , int, size_t *, size_t *, double *);
int GetVarIndex(char *varname);

