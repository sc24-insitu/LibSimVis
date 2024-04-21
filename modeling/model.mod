param Timesteps, > 0;

set i := 1..Timesteps;

param ts, > 0;

param tt, > 0;

param imp{i in Timesteps}, >= 0;

param budget, > 0;

# Define the binary decision variable
var x{i in Timesteps} binary;

param max_time := (Timesteps * ts) * budget/100;

/* total_imp is sum of imp[i] for all i */
#param total_imp := sum{i in I} imp[i] * x[i];

/* Maximize the total importance of the time steps that are being transferred, which is the sum of imp[i] for all i */
maximize obj: sum{i in Timesteps} imp[i] * x[i]; 

# Constraints
subject to importance {i in Timesteps}: imp[i] * x[i] >= 0;

subject to budget_timestep {i in Timesteps}: sum{j in 1..i} x[j] * tt <= max_time/Timesteps * i;

subject to budget: (sum{i in Timesteps} x[i] * tt)  <= max_time;
