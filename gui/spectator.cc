// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2018 Sacha Delanoue

#include "prologin.hh"
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

extern "C" const char* dump_state_json();

static int conn = 0;

static void send_and_wait()
{
    const char* dump = dump_state_json();
    send(conn, dump, strlen(dump), 0);
    char buffer[1024] = {0};
    std::string received = "";
    while (received != "NEXT")
    {
        int len = read(conn, buffer, 1024);
        if (len == 0)
            received = "";
        else
        {
            int offset = 0;
            while (int(buffer[offset]) < 33 and offset < 1024)
                ++offset;
            received = std::string(buffer + offset);
        }
    }
}

void partie_init()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!socket_fd)
        exit(1);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(0);

    if (bind(socket_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
        exit(2);
    if (listen(socket_fd, 1) < 0)
        exit(3);

    socklen_t len = sizeof(address);
    int port = 0;
    if (getsockname(socket_fd, (struct sockaddr*)&address, &len) == -1)
        exit(4);
    else
        port = ntohs(address.sin_port);
    if (!fork())
    {
        auto s = std::to_string(port);
        execl("/usr/bin/prologin2018-gui", "/usr/bin/prologin2018-gui",
              s.c_str(), (char*)nullptr);
        exit(5);
    }
    conn = accept(socket_fd, (struct sockaddr*)&address, (socklen_t*)&len);
    if (conn < 0)
        exit(6);
    send_and_wait();
}

void jouer_tour()
{
    send_and_wait();
}

void partie_fin()
{
}
