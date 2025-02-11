#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "../include/mysockets.h"

int Socket(int domain, int type, int protocol) {
	int socket_fd;

	if ((socket_fd = socket(domain, type, protocol)) < 0) {
		printf("Failed to create a socket!\n");
		exit(1);
	}
	
	return socket_fd;
}

void Bind(int socket, const struct sockaddr *address, socklen_t address_len) {
	if (bind(socket, address, address_len) < 0) {
		printf("Failed to bind socket\n");
		exit(1);
	}
}

void Listen(int socket, int backlog) {
	if (listen(socket, backlog) < 0) {
		printf("Failed to listen!\n");
		exit(1);
	}
}
