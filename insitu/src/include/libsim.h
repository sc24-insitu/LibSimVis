#include <stdio.h>
#include <string.h>
#include <VisItControlInterface_V2.h>
#include <VisItDataInterface_V2.h>
#include "SimulationExample.h"
#include "mpi.h"

#define SIM_STOPPED 0
#define SIM_RUNNING 1

#define VISIT_COMMAND_PROCESS 0
#define VISIT_COMMAND_SUCCESS 1
#define VISIT_COMMAND_FAILURE 2

typedef struct
{
 
    MPI_Comm par_comm;
    int     cycle;
    double  time;
    int     runMode;
    int     done;
    int     par_rank;
    int     par_size;
    int     echo;
    int     nvars; 
    int     nx;
    int     ny;
    int     nz;
    int     upd;
    int     lstupd;
    int     i_beg;
    int    *impindex;
    int     visflag;
    double  *simvar;
    double  *prevdata;
} simulation_data;

extern const char *cmd_names[];// = {"halt", "step", "run", "update"};
extern const char *var_names[];// = {"field"};
extern const char *mesh_var[];//  = {"DummySim","x","y","z"};
extern const char *mesh_labels[];// = {"X", "Y", "Z"};
extern int y_beg[];// = {0,334};

/* Data Access Function prototypes */
visit_handle SimGetMetaData(void *);
visit_handle SimGetMesh(int, const char *, void *);
visit_handle SimGetVariable(int, const char *, void *);
visit_handle SimGetDomainList(const char *, void *);

void copy_data(size_t *size, double *src, simulation_data *sim, int nranks, int myrank, int *cts);

void initilize_visit(simulation_data *sim);

void simulate_one_timestep(simulation_data *sim, int *cts);

void ControlCommandCallback(const char *cmd, const char *args, void *cbdata);

/* Called to handle case 3 from VisItDetectInput where we have console
 * input that needs to be processed in order to accomplish an action.
 */
void ProcessConsoleCommand(simulation_data *sim);

void controlloop(simulation_data *sim, int *cts);

visit_handle SimGetMetaData(void *cbdata);

//Get mesh structure
visit_handle SimGetMesh(int domain, const char *name, void *cbdata);

//Get varaible data
visit_handle SimGetVariable(int domain, const char *name, void *cbdata);

//Get the domain list
visit_handle SimGetDomainList(const char *name, void *cbdata);

