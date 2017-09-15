import csv
import pandas as pd
from matplotlib import pyplot as plt
import matplotlib.dates as mdates
import matplotlib.ticker as plticker

##Retrieving Data
filename = ''
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
def remove_noise(data):
    for i in range(len(data)):
        if data[i] == -127.00:
            data[i] = data[i - 1]

remove_noise(temperature_out)
remove_noise(temperature_in)
remove_noise(temperature_ambient)

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
ax.yaxis.set_major_locator(loc_y)

plt.plot(timestamp_time,temperature_in,linewidth = 1, label = "Temperature Internal")
plt.plot(timestamp_time,temperature_out,linewidth = 1, label = "Temperature Surface")
plt.plot(timestamp_time,temperature_ambient,linewidth = 1, label = "Temperature Ambient")

#plt.plot(timestamp_time,diff_in_out,linewidth = 1, label = "Temperature Internal - Surface")

xfmt = mdates.DateFormatter('%Y-%m-%d %H:%M:%S')
ax.xaxis.set_major_formatter(xfmt)

plt.title('Temperature in Celcius')
plt.grid()
plt.legend()
plt.show()
