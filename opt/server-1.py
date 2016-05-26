#! /usr/bin/python
# -*- coding: utf-8 -*-

import socket

HOST = "localhost"
PORT = 1231

def listen():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind( (HOST, PORT) )
    s.listen(1)

    while True :
        conn, addr = s.accept()
        request = ""

        while True :
            data = conn.recv(1024)
            if not data : break
            request = request + data

        response = "Server #1 works.\n" + "Your request is: " + request + "\n"
        conn.sendall(response)
        conn.close()

if __name__ == '__main__' :
    listen()
