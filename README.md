LibSimVis (Data-aware In situ Visualization with LibSim)

Description
-----------

This code was developed and used in the paper (under submission) [1].

There are several components of this code:

I. Simulation

In our paper, we used two simulation codes - LAMMPS and WRF.

LAMMPS (Large-scale Atomic/Molecular Massively Parallel Simulator) [2,3] is a classical large-scale molecular dynamics simulation code designed to run efficiently on parallel computers. 

Weather Research and Forecast model (WRF) [4,5] 

II. In situ analysis and visualization

We developed a library to extract important time steps automatically from a running simulation and visualize with VisIt. For this, we perused LibSim library function calls and created our own library. The source code for this may be found in 'insitu' directory.

III. Mixed Integer Linear Program

We have written the formulations (described in [1]) in AMPL [7]. More details can be found in 'modeling' directory.

Workflow
--------

1. Download and install LAMMPS [2,3] and WRF [4,5], and VisIt [6].
2. Install our library, NetCDF paths need to be set properly. This will create a library lib/stage_manager.so.
3. Link lib/stage_manager.so using LD_PRELOAD or while building at step 1.
4. Run the application. (mpirun -np P ./exe to run simulation on P processes)
5. Launch visit GUI and connect to the file from .visit/simulation. 
6. The write function calls from the simulation will be redirected to our library and transferred to VisIt GUI via LibSim based on the analysis.


Plots
-----

Some of the plots of the paper (scripts and data) are in the directory 'plots'.

References
----------

[1] "Data-aware Adaptive Remote In Situ Visualization", under submission to ACM/IEEE Supercomputing Conference (SC24).

[2] http://lammps.sandia.gov

[3] https://github.com/lammps/lammps

[4] https://www.mmm.ucar.edu/models/wrf

[5] https://github.com/wrf-model/WRF

[6] https://visit-dav.github.io/visit-website/releases-as-tables/#latest

[7] http://ampl.com

