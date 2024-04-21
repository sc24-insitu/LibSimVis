#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "mpi.h"
#include "include/measures.h"

struct
{
    float  **varmetric;
    float  **vardiff;
    
} simulation_metric;


int numMeasures = 9;

//Allocate memory for storing metrics for al the iterations
void allocate_memory(simulation_metric *sim, int length)
{
  sim->vardiff = (float **) malloc (length * sizeof(float *));
  sim->varmetric = (float **) malloc (length * sizeof(float *));
 
  for(int ca=0; ca < length ; ca++)
  {  
   sim->varmetric[ca] = (float *) malloc (9 * sizeof(float));
   sim->vardiff[ca] = (float *) malloc (9 * sizeof(float)); 
  }
}


// Function to calculate below statistics of two arrays (current Timestep and previous Timestep)
// a. Minimum | b. Maximum | c. Average | d. Sum of differences | e. range | f. L1 and L2

void calStatistics(float Var[], float prevVar[], int length, simulation_metric *sim, int iter)
{
  float min, max, sum=0, diffsum=0, aver=0;
  float l1=0, l2sum=0, l2=0, tempvar;
  
  min = Var[0]; max=Var[0];
  
  for(int i=1; i<length ; i++)
  {
      if(min > Var[i])
        min = Var[i];
                     
      if(max < Var[i])
       max = Var[i]; 
                       
    sum = sum + fabs(Var[i]);
    //SOD
    diffsum = diffsum + fabs(prevVar[i] - Var[i]) ;
    //L1,L2
    tempvar = Var[i] -prevVar[i];
    l1 = l1 + fabs(tempvar);
    l2sum = l2sum + tempvar * tempvar;
     
  }
   
  l2 = sqrt(l2sum);
  
  aver = sum/length;
  printf("\n%f,%f,%f,%f,%f,%0.8f,%0.8f\n",min,max,max-min,aver,diffsum,l1,l2); 
   
  //Copy the values for future comparisons   
  sim->varmetric[iter][0]=min;
  sim->varmetric[iter][1]=max;
  sim->varmetric[iter][2]=max-min;
  sim->varmetric[iter][3]=aver;
  sim->varmetric[iter][4]=diffsum;
  sim->varmetric[iter][5]=l1;
  sim->varmetric[iter][6]=l2; 
}


// Function to calculate entropy of a array
void calentropy(float Var[], int length, simulation_metric *sim, int iter)
{  
  int frequency[length];
  int visited = -1;
  float var1[length], entropy=0.0;

  //Calculate frequency of each element         
  for(int i = 0; i < length; i++){    
        int count = 1;    
        for(int j = i+1; j < length; j++){    
            if(Var[i] == Var[j]){    
                count++;    
                //To avoid counting same element again    
                frequency[j] = visited; 
            }    
        }    
        if(frequency[i] != visited)   
            frequency[i] = count;  
    }     
    
  //Calulate entropy from the frequency of each element    
  for(int i=0;i<length;i++)
   {   
        if(frequency[i] != visited) 
        {
          var1[i] = frequency[i]/(float)length;
          entropy = entropy + (var1[i] * log2(1/var1[i]));
        }  
   }  
   sim->varmetric[iter][7]=entropy;  
   printf("Entropy is %f\n", entropy);
      
}  

//Function returns the median of the array by sorting it first.
void getmedian(float Var[],int length,simulation_metric *sim,int iter)
{
   float a;   
   for (int i = 0; i < length; ++i) 
   {
       for (int j = i + 1; j < length; ++j)
       {
            if (Var[i] > Var[j]) 
            {
                a =  Var[i];
                Var[i] = Var[j];
                Var[j] = a;  
             }
        }
   }
   int middle = round(length/2);
   
   sim->varmetric[iter][8]=Var[middle];  
   printf("Median is %f\n", Var[middle]); 
                     
}

 
int analysis(float Var[], float prevVar[], simulation_metric *sim, int length, int iter, int lstupd, int level)
{  
 
  float ch=0;
  int cf=0,cm=0;
  float diff=0;
  int flag=0;
  int ret=0;

  // Initialization
  for(int t=0;t<numMeasures;t++)
   {
    sim->vardiff[iter][t]   = 0.000000001;	
    sim->varmetric[iter][t] = 0.0000000000001;
   }
   
   if(level==3)
   {
       cf=4;cm=7;	
       calStatistics(Var, prevVar, length, sim, iter);
   } 
   else if(level==2)
   { 
       cf=5;cm=9;
       calStatistics(Var, prevVar, length, sim, iter);
       calentropy(Var, length, sim, iter);
       getmedian(Var, length, sim, iter); 
   }
   else if(level==1)
   {
      cf=3;cm=7;
      calStatistics(Var, prevVar, length, sim, iter);
   } 
 
   if(iter > 0)
    { 
      flag=0;
      for(int c=0;c<cm;c++)
      { 
        diff = fabs(sim->varmetric[iter][c] - sim->varmetric[lstupd][c]);
        ch = (diff/sim->varmetric[lstupd][c]) * 100;
        sim->vardiff[iter][c] = ch;
      }       

      for(int c=0;c<cm;c++)
      {
        if(sim->vardiff[iter][c] >= 5.0)
          {  
            flag++; 
         }
      } 
   
      if(flag >=cf)
      { 
       ret=1;
      } 
   }

   return ret;
   
}


