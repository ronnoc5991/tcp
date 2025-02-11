#ifndef MYSOCKETS_H
#define MYSOCKETS_H

int Socket(int domain, int type, int protocol);

void Bind(int socket, const struct sockaddr *address, socklen_t address_len);

void Listen(int socket, int backlog);

#endif
