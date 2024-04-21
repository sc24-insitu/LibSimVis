import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

# Load the CSV file into a pandas DataFrame
df = pd.read_csv(sys.argv[1])

# Extract TimeStep
time_steps = df['TimeStep']
os_values = df['L_OS']
da_values = df['L_DA']  
na_values = df['L_NA']  
dpt_values = df['L_GDA'] 
dpi_values = df['L_MILP'] 
ff_values = df['L_FF']   
mi_values = df['L_MI']  
milpo_values=df['L_MILPO']
xlat_values = df['XLAT']
xlong_values = df['XLONG']

# Create a figure and axis
fig, ax = plt.subplots(figsize=(80, 40))

# Define a small offset for the y-values to decrease the vertical gap
offset = 0.3

os_indices = os_values == 1
os_points = time_steps[os_indices]
ax.plot(os_points, [0.6 + offset] * sum(os_indices), 'bo', label='All', markersize=40)

mi_indices = mi_values == 1
mi_points = time_steps[mi_indices]
ax.plot(mi_points, [0.9 + offset] * sum(mi_indices), 'bo', label='Mutual Information', markersize=40)

ff_indices = ff_values == 1
ff_points = time_steps[ff_indices]
ax.plot(ff_points, [1.2 + offset] * sum(ff_indices), 'bo', label='Fixed frequency', markersize=40)

da_indices = da_values == 1
da_points = time_steps[da_indices]
ax.plot(da_points, [1.5 + offset] * sum(da_indices), 'bo', label='Data-aware', markersize=40)

na_indices = na_values == 1
na_points = time_steps[na_indices]
ax.plot(na_points, [1.8 + offset] * sum(na_indices), 'bo', label='Network-aware', markersize=40)

dpt_indices = dpt_values == 1
dpt_points = time_steps[dpt_indices]
ax.plot(dpt_points, [2.1 + offset] * sum(dpt_indices), 'bo', label='Adaptive', markersize=40)

milpo_indices = milpo_values == 1
milpo_points = time_steps[milpo_indices]
ax.plot(milpo_points, [2.4 + offset] * sum(milpo_indices), 'bo', label='MILP', markersize=40)

for i in range (190):
  if not np.isnan(xlat_values[i]) and not np.isnan(xlong_values[i]):
    ax.annotate(f'({xlat_values[i]}, {xlong_values[i]})', xy=(i,2.7), rotation=30, size=80)

positions = [0.6 + offset, 0.9 + offset, 1.2 + offset, 1.5 + offset, 1.8+offset, 2.1+offset, 2.4+offset] 

# Set labels and title
ax.set_xlabel('Time steps visualized', fontsize=80)

ax.set_yticks(positions)
ax.set_yticklabels(['All','Fixed frequency','Mutual information','Data-aware','Network-aware','Adaptive','MILP'], rotation=25, fontsize=70)

num_steps = len(time_steps)
step_size = num_steps // 4  # Assuming num_steps > 4
evenly_spaced_time_steps = np.arange(1.5, num_steps, step_size) + 1
ax.set_xticks(evenly_spaced_time_steps)

if "2019" in sys.argv[1]:
 ax.set_xticklabels(['2019-04-25', '2019-04-26', '2019-04-27', '2019-04-28'], fontsize=80) #Fani
else:
 ax.set_xticklabels(['2023-10-17', '2023-10-18', '2023-10-19', '2023-10-20'], fontsize=80) #Hamoon

ax.tick_params(axis='x', labelsize=80)

filename=sys.argv[1]+'.png'
plt.savefig(filename)

