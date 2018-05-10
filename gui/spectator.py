# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

from api import *
import subprocess
import socket
import ctypes

get_dump = None
conn = None


def partie_init():
    global get_dump
    global conn
    librules = ctypes.cdll.LoadLibrary('libprologin2018.so')
    get_dump = librules.dump_state_json
    get_dump.argtypes = []
    get_dump.restype = ctypes.c_char_p

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('', 0))
    port = sock.getsockname()[1]
    sock.listen(1)
    subprocess.Popen(['prologin2018-gui', str(port)])
    conn, _ = sock.accept()

    conn.send(get_dump())
    data = ''
    while 'NEXT' not in data:
        data = conn.recv(1024).decode()


def jouer_tour():
    global get_dump
    global conn

    conn.send(get_dump())
    data = ''
    while 'NEXT' not in data:
        data = conn.recv(1024).decode()


def partie_fin():
    pass
