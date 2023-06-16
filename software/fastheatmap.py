from tkinter import *
import numpy as np
import threading

import socket
import struct

rect_size = 50
distance = np.zeros((8,8), dtype=int)
dist_max = 2046

def colormap(dist: int) -> str:
    if dist == 9999:
        return '#000000'
    if dist > dist_max:
        print(dist)
        return '#ffffff'
    dist_mapped = int(dist/dist_max*1023)
    if dist_mapped < 256:
        return f'#ff{dist_mapped:02x}00'
    elif dist_mapped < 512:
        return f'#{511-dist_mapped:02x}ff00'
    elif dist_mapped < 768:
        return f'#00ff{dist_mapped-512:02x}'
    else:
        return f'#00{1023-dist_mapped:02x}ff'


class App(threading.Thread):

    def __init__(self):
        threading.Thread.__init__(self)
        self.start()

    def callback(self):
        self.root.quit()

    def run(self):
        # self.root = Tk()
        # self.root.protocol("WM_DELETE_WINDOW", self.callback)
        ws = Tk()
        ws.title('ToF render')
        ws.geometry('400x400')
        ws.config(bg='#345')

        canvas = Canvas(
            ws,
            height=8*rect_size,
            width=8*rect_size,
            bg="#fff"
            )
            
        canvas.pack()

        def update():
            mydist = np.copy(distance)
            # print(mydist)
            canvas.delete("all")
            for i in range(64):
                x = int(i%8)
                y = int(i/8)
                d = mydist[x][y]
                canvas.create_rectangle(
                    x*rect_size, y*rect_size,
                    (x+1)*rect_size, (y+1)*rect_size,
                    fill=colormap(d)
                )
            
            ws.after(67, update)

        # canvas.create_rectangle(
        #     30, 30, 180, 120,
        #     outline="#fb0",
        #     fill="#fb0")

        ws.after(67, update)

        ws.mainloop()


zoneNumFmt = '<I'
zoneResultFmt = '<IIIff'

UDP_IP = "10.1.0.3"
UDP_PORT = 2001

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

app = App()

while 1:
    data, addr = sock.recvfrom(65536) # buffer size is 65536 bytes

    zonenum = struct.unpack(zoneNumFmt, data[0:4])[0]

    if zonenum != 64:
        continue

    zoneresults = list()

    for i in range(64):
        zoneresults.append(struct.unpack(zoneResultFmt, data[4+20*i:24+20*i]))

    for i in range(zonenum):
        distance[i%8][int(i/8)] = 9999 if zoneresults[i][2] else zoneresults[i][1] # distance in mm