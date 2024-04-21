#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/libsim.h"
#include "include/measures.h"
#include "include/data_stager.h"

int  comm_size = 0;
char open_file[255] = "";
int  cts=0;
simulation_data sim;

int GetVarIndex(char *varname)
{

    if(strcmp(varname,"field") == 0)
        return 1;
    else
        return -1;

}

int stage_open(const char *fname, unsigned int flags, int *ncid)
{
    printf("DS:Function: %s\n", __func__);
    strcpy(open_file, fname);
    printf("DS:File name passed = %s, mode = %d\n", fname, flags);
   
    int (*orig_nc_open)(const char *, unsigned int, int *) = dlsym(RTLD_NEXT, "nc_open");
    return orig_nc_open(fname, flags, ncid);
}

int stage_put_vara_double(int ncid, int var_id, size_t *begin, size_t *size, double *src)
{

    printf("DS:Function: %s\n", __func__);
    char varname[255];
    int ndims=0;
    
    int nranks,myrank;
    
    MPI_Comm_size(MPI_COMM_WORLD, &nranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
          
    // Dlsym Function pointers
    int (*orig_nc_inq_varndims)(int, int, int*) = dlsym(RTLD_NEXT, "nc_inq_varndims");
    int (*orig_nc_inq_varname)(int, int, char*) = dlsym(RTLD_NEXT, "nc_inq_varname");
    int (*orig_nc_inq_dimlen)(int, int, int*) = dlsym(RTLD_NEXT, "nc_inq_dimlen");
    int (*orig_nc_put_vara_double)(int, int, size_t *, size_t *, double *) = dlsym(RTLD_NEXT, "nc_put_vara_double");
    int (*orig_nc_inq_var)(int, int, char*, int*, int*, int*, int*) = dlsym(RTLD_NEXT, "nc_inq_var");

    orig_nc_inq_varndims(ncid, var_id, &ndims);
    orig_nc_inq_varname(ncid, var_id, varname);

    int var_index = GetVarIndex(varname);
    if(var_index == 1)
    {
      if(cts==0)
      initilize_visit(&sim); 

      int *dimids = (int *) malloc(ndims * sizeof(int));
      orig_nc_inq_var(ncid, var_id, NULL, NULL, NULL, dimids, NULL);
      int *dimlens = (int *) malloc(ndims * sizeof(int));
      int i = 0;

      while(i < ndims)
      {
        orig_nc_inq_dimlen(ncid, dimids[i], &dimlens[i]);
        printf("DS:Length %d %d begin %zu size is %zu rank %d\n", i, dimlens[i], begin[i], size[i], myrank); //debug
        i++;
      }
    
      printf("DS:ncid = %d, var_id = %d, varname = %s,varindex = %d\n", ncid, var_id, varname,var_index); // debug
      copy_data(size, src, &sim, nranks, myrank, &cts);
      controlloop(&sim,&cts);
    }
   
    return orig_nc_put_vara_double(ncid, var_id, begin, size, src);
}


