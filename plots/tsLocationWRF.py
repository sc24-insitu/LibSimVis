import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

# Load the CSV file into a pandas DataFrame
#df = pd.read_csv('Nestloctimeseriesdatacyclone2023.csv')
df = pd.read_csv(sys.argv[1])

# Extract TimeStep, GD, and DP columns
time_steps = df['TimeStep']
da_values = df['DA']
na_values = df['NA']  #4
gd_values = df['Greedy'] #5
dpi_values = df['milpa'] #6
dpt_values =  df['Greedy2']  #3
milpo_values = df['milpo']   #1
mi_values = df['MI']
ff_values = df['FF']

# Create a figure and axis
fig, ax = plt.subplots(figsize=(80, 40))

# Define a small offset for the y-values to decrease the vertical gap
offset = 0.3

# Plot blue dots for GD values equal to 1 with reduced markersize
#os_indices = os_values == 1
#os_points = time_steps[os_indices]
#ax.plot(os_points, [0.6 + offset] * sum(os_indices), 'bo', label='All', markersize=40)

mi_indices = mi_values == 1
mi_points = time_steps[mi_indices]
ax.plot(mi_points, [0.9 + offset] * sum(mi_indices), 'bo', label='Mutual Information', markersize=40)

ff_indices = ff_values == 1
ff_points = time_steps[ff_indices]
ax.plot(ff_points, [1.2 + offset] * sum(ff_indices), 'bo', label='Fixed frequency', markersize=40)

# Plot green dots for DA values equal to 1 with reduced markersize
da_indices = da_values == 1
da_points = time_steps[da_indices]
ax.plot(da_points, [1.5 + offset] * sum(da_indices), 'bo', label='Data-aware', markersize=40)

# Plot red dots for NA values equal to 1 with reduced markersize
na_indices = na_values == 1
na_points = time_steps[na_indices]
ax.plot(na_points, [1.8 + offset] * sum(na_indices), 'bo', label='Network-aware', markersize=40)

# Plot green dots for DA values equal to 1 with reduced markersize
# Plot magenta dots for DPT values equal to 1 with reduced markersize
dpt_indices = dpt_values == 1
dpt_points = time_steps[dpt_indices]
ax.plot(dpt_points, [2.1 + offset] * sum(dpt_indices), 'bo', label='Adaptive', markersize=40)

milpo_indices = milpo_values == 1
milpo_points = time_steps[milpo_indices]
ax.plot(milpo_points, [2.4 + offset] * sum(milpo_indices), 'bo', label='MILP', markersize=40)

#gd_indices = gd_values == 1
#gd_points = time_steps[gd_indices]
#ax.plot(gd_points, [2.1 + offset] * sum(gd_indices), 'bo', label='GD', markersize=40)

# Plot cyan dots for DPI values equal to 1 with reduced markersize
#dpi_indices = dpi_values == 1
#dpi_points = time_steps[dpi_indices]
#ax.plot(dpi_points, [3.5 + offset] * sum(dpi_indices), 'bo', label='MILP-All', markersize=40)

#for i in np.where(milpo_indices)[0]:

#for i in range (190):
#  if not np.isnan(xlat_values[i]) and not np.isnan(xlong_values[i]):
#    print(xlat_values[i], xlong_values[i]) 
#    ax.annotate(f'({xlat_values[i]}, {xlong_values[i]})', xy=(i,2.7), rotation=30, size=80)
#    #ax.annotate(f'({xlat_values[i]}, {xlong_values[i]})', (i, 2.7), xytext=(i,2.7), ha='center',rotation=20,fontsize=40)

positions = [0.6+offset, 0.9+offset, 1.2+offset, 1.5+offset, 1.8+offset, 2.1+offset, 2.4+offset] #, 4.2+offset,4.9+offset,5.6+offset]
# Set labels and title
ax.set_xlabel('Time steps visualized', fontsize=80)

ax.set_yticks(positions)
ax.set_yticklabels(['All','Fixed frequency','Mutual information','Data-aware','Network-aware','Adaptive','MILP'], rotation=25, fontsize=70)
#ax.set_yticklabels(['All','MI','Network-aware','Greedy','Greedy Adaptive','MILP-All', 'MILP-Online','Fixed frequency', 'Data-aware'], fontsize=100)
#ax.set_xticklabels([1, 2, 3, 4], fontsize=30)

num_steps = len(time_steps)
step_size = num_steps // 4  # Assuming num_steps > 4
evenly_spaced_time_steps = np.arange(1.5, num_steps, step_size) + 1
ax.set_xticks(evenly_spaced_time_steps)
ax.set_xticklabels(['2023-07-08', '2023-07-09', '2023-07-10', '2023-07-11'], fontsize=80)

ax.tick_params(axis='x', labelsize=80)

filename=sys.argv[1]+'.png'
plt.savefig(filename)

# Show the plot
#plt.show()

