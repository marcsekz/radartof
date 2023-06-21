import socket
import struct
import os
import datetime

t = datetime.datetime.now()
i = 1
filename_base = f'./tof_record_{t.day}-{t.month}-{t.year}_{t.hour}-{t.minute}'
filename = filename_base
while os.path.exists(filename):
    filename = filename_base + '-' + str(i)
    i += 1

zoneNumFmt = '<I'
zoneResultFmt = '<IIIff'

UDP_IP = "10.1.0.3"
UDP_PORT = 2001

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

labels = list('12345678')
linecount = 0

with open(filename, "w") as fp:

    while 1:
        data, addr = sock.recvfrom(65536) # buffer size is 65536 bytes

        zonenum = struct.unpack(zoneNumFmt, data[0:4])[0]

        if zonenum != 64:
            continue

        zoneresults = list()

        for i in range(64):
            zoneresults.append(struct.unpack(zoneResultFmt, data[4+20*i:24+20*i]))

        for i in range(zonenum):
            d = -1 if zoneresults[i][2] or 0==zoneresults[i][0] else zoneresults[i][1] # distance in mm
            fp.write(f'{d},')

        fp.write('\n')
        linecount += 1
        print(linecount)

