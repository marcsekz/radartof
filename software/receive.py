import socket
from timeit import default_timer as timer

UDP_IP = "10.1.0.3"
UDP_PORT = 2001

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

sumlen = 0
start = timer()

while (timer() - start) < 10:
    data, addr = sock.recvfrom(65536) # buffer size is 1024 bytes
    #print(f"len: {len(data)}")
    sumlen += len(data)

end = timer()
print(end - start)
print(f'{sumlen/(end-start)/1e6}MB/s\t{sumlen/(end-start)/1e6*8}Mbps')
