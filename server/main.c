#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "../include/mysockets.h"

// TODO: add define here for number of pending connections
#define BUFFER_SIZE 100

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	char *port = argv[1];

	int socket_fd;
	char buffer[BUFFER_SIZE];
	struct addrinfo hints, *servinfo;
	struct sockaddr_in client_addr;
	int client_struct_length = sizeof(client_addr);

	memset(buffer, '\0', BUFFER_SIZE);
	memset(&client_addr, 0, sizeof(struct sockaddr_in));

	hints.ai_family = AF_UNSPEC; // IPv4 or v6 (no preference)
	hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_flags = AI_PASSIVE; // fill in my IP for me

	if (getaddrinfo(NULL, port, &hints, &servinfo) != 0) {
		printf("Unable to getaddrinfo\n");
		exit(1);
	}

	// create a TCP socket
	socket_fd = Socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

	// bind that socket to our port of choice
	Bind(socket_fd, servinfo->ai_addr, servinfo->ai_addrlen);

	// turn this into a 'listening' socket
	Listen(socket_fd, 10);

	printf("Server listening on port %s...\n", port);

	int connected_fd = -1;
	struct sockaddr client_address;
	socklen_t client_addr_len = sizeof(client_address);

	while ((connected_fd = accept(socket_fd, &client_address, &client_addr_len)) > 0) {
		printf("Connected to a new client...\n"); // could print out their addr info (IP and port)

		// could use buffered io here?
		while (read(connected_fd, buffer, BUFFER_SIZE) > 0) {
			printf("From client: %s", buffer);
			memset(buffer, '\0', BUFFER_SIZE);
		}

		printf("Closing connection...\n");
		close(connected_fd);
	}

	close(socket_fd);
	freeaddrinfo(servinfo);

	return 0;
}
