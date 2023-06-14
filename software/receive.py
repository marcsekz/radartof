import socket
import struct
import os
import math

import matplotlib.pyplot as plt
import numpy as np

zoneNumFmt = '<I'
zoneResultFmt = '<IIIff'

UDP_IP = "10.1.0.3"
UDP_PORT = 2001

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

labels = list('12345678')

plt.ion()

fig = plt.figure()
ax = fig.add_subplot(111)
 
# Want a more natural, table-like display
ax.invert_yaxis()
ax.xaxis.tick_top()
 
ax.set_xticklabels(labels, minor=False)
ax.set_yticklabels(labels, minor=False)

while 1:
    data, addr = sock.recvfrom(65536) # buffer size is 65536 bytes

    zonenum = struct.unpack(zoneNumFmt, data[0:4])[0]

    if zonenum != 64:
        continue

    zoneresults = list()
    distance = np.zeros((8,8))
    # status = list()

    for i in range(64):
        zoneresults.append(struct.unpack(zoneResultFmt, data[4+20*i:24+20*i]))

    # os.system('clear')
    # print(f'Number of zones: {zonenum}')
    # print("")

    rowsize = int(math.sqrt(zonenum))
    for i in range(zonenum):
        distance[i%8][int(i/8)] = zoneresults[i][1] # distance in mm
        # status.append(zoneresults[i][2]) # 0 if valid, 1 if invalid



        # if zonenum == 0:
        #     break

        # if not i%rowsize and i > 0:
        #     print("|")
        # if zoneresults[i][2]:
        #     print('| ;     ', end="")
        # else:
        #     print(f'|{zoneresults[i][0]:1};{zoneresults[i][1]:5}', end="")
    # print("|")

    heatmap = ax.pcolor(distance, cmap=plt.cm.autumn, vmin=0, vmax=500)
 
    # Put the major ticks at the middle of each cell
    ax.set_xticks(np.arange(distance.shape[0]), minor=False)
    ax.set_yticks(np.arange(distance.shape[0]), minor=False)

    fig.canvas.draw()
    fig.canvas.flush_events()

