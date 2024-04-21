#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "mpi.h"

//Data structure defenition to store metrics data
typedef struct
{
    float  **varmetric;
    float  **vardiff;
    
} simulation_metric;

//Allocate memory for storing metrics for al the iterations
void allocate_memory(simulation_metric *sim, int leng);

// Function to calculate below statistics of two arrays
//   a. Minimum b.Maximum c.Average d.Sum of differences and e. range f.l1 and l2
void calStatistics(float var[], float prevVar[], int leng, simulation_metric *sim, int iter);
  
// Function to calculate entropy of a array
void calentropy(float var[], int leng, simulation_metric *sim, int iter);

//Function returns the median of the array by sorting it first.
void getmedian(float var[], int leng, simulation_metric *sim, int iter);
 
int analysis(float var[], float prevVar[], simulation_metric *sim, int leng, int iter, int lstupd, int level);

