import csv
import pandas as pd
from matplotlib import pyplot as plt
import matplotlib.dates as mdates
import matplotlib.ticker as plticker

##Retrieving Data
filename = 'outdoor_shaded.csv'
with open(filename) as f:
    reader = csv.reader(f)
    header_row = next(reader)

    timestamp_str = []
    temperature_in = []
    temperature_out = []
    temperature_ambient = []

    for row in reader:
        timestamp_str.append(row[0])
        temperature_in.append(float(row[1]))
        temperature_out.append(float(row[2]))
        temperature_ambient.append(float(row[3]))

#Removing noise
for i in range(len(temperature_in)):
    if temperature_in[i] == -127.00:
        temperature_in[i] = temperature_in[i-1]

    if temperature_out[i] == -127.00:
        temperature_out[i] = temperature_out[i-1]

    if temperature_ambient[i] == -127.00:
        temperature_ambient[i] = temperature_ambient[i-1]

#Examining difference between internal and surface temperature
''' 
diff_in_out = []
for i in range(len(temperature_in)):
    diff_in_out.append(temperature_in[i] - temperature_out[i])
'''    
timestamp_time = pd.to_datetime(timestamp_str) #Convert string to TimeIndex format

##Plot##
fig, ax = plt.subplots(1)
fig.autofmt_xdate()
#loc_x = plticker.MultipleLocator(base=0.005) # this locator puts ticks at regular intervals
loc_y = plticker.MultipleLocator(base=1)
#ax.xaxis.set_major_locator(loc_x)
ax.xaxis.set_major_locator(loc_y)

plt.plot(timestamp_time,temperature_in,linewidth = 1, label = "Temperature Internal")
plt.plot(timestamp_time,temperature_out,linewidth = 1, label = "Temperature Surface")
plt.plot(timestamp_time,temperature_ambient,linewidth = 1, label = "Temperature Ambient")

#plt.plot(timestamp_time,diff_in_out,linewidth = 1, label = "Temperature Internal - Surface")

xfmt = mdates.DateFormatter('%d-%m-%y %H:%M:%S')
ax.xaxis.set_major_formatter(xfmt)

plt.title('Temperature in Celcius')
plt.grid()
plt.legend()
plt.show()
