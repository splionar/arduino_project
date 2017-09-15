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
    temperature_1 = []
    temperature_2 = []
    temperature_3 = []
    temperature_4 = []
    temperature_5 = []
    temperature_6 = []

    for row in reader:
        timestamp_str.append(row[0])
        temperature_1.append(float(row[1]))
        temperature_2.append(float(row[2]))
        temperature_3.append(float(row[3]))
        temperature_4.append(float(row[4]))
        temperature_5.append(float(row[5]))
        temperature_6.append(float(row[6]))

#Removing noise
def remove_noise(data):
    for i in range(len(data)):
        if data[i] == -127.00:
            data[i] = data[i - 1]

remove_noise(temperature_1)
remove_noise(temperature_2)
remove_noise(temperature_3)
remove_noise(temperature_4)
remove_noise(temperature_5)
remove_noise(temperature_6)

timestamp_time = pd.to_datetime(timestamp_str) #Convert string to TimeIndex format

##Plot##
fig, ax = plt.subplots(1)
fig.autofmt_xdate()
#loc_x = plticker.MultipleLocator(base=0.005) # this locator puts ticks at regular intervals
loc_y = plticker.MultipleLocator(base=1)
#ax.xaxis.set_major_locator(loc_x)
ax.yaxis.set_major_locator(loc_y)

plt.plot(timestamp_time,temperature_1,linewidth = 1, label = "Temperature 1")
plt.plot(timestamp_time,temperature_2,linewidth = 1, label = "Temperature 2")
plt.plot(timestamp_time,temperature_3,linewidth = 1, label = "Temperature 3")
plt.plot(timestamp_time,temperature_4,linewidth = 1, label = "Temperature 4")
plt.plot(timestamp_time,temperature_5,linewidth = 1, label = "Temperature 5")
plt.plot(timestamp_time,temperature_6,linewidth = 1, label = "Temperature 6")

xfmt = mdates.DateFormatter('%Y-%m-%d %H:%M:%S')
ax.xaxis.set_major_formatter(xfmt)

plt.title('(°C)')
plt.grid()
plt.legend()
plt.show()
