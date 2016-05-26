#! /usr/bin/python
# -*- coding: utf-8 -*-

import sys
import socket

HOST = "localhost"
PORTS = (1231, 1232, 1233)

def query(request, PORT):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect( (HOST, PORT) )
    s.sendall(request)
    s.shutdown(socket.SHUT_WR)
    response = ""
    while True :
        data = s.recv(1024)
        if not data : break
        response = response + data
        s.close()
        return response

if __name__ == "__main__" :
    request = sys.argv[1] if 1 in sys.argv else "Test"
    for PORT in PORTS :
        response = query(request, PORT)
        print response
