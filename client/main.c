#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "../include/mysockets.h"

#define MAX_MESSAGE 100

int main(int argc, char **argv) {
	if (argc != 3) {
		printf("Usage: %s hostname/IP port\n", argv[0]);
		exit(1);
	}

	char *hostname = argv[1];
	char *port = argv[2];

	int socket_fd;
	char message[MAX_MESSAGE];
	struct addrinfo hints, *res, *p;

	memset(&hints, 0, sizeof hints);
	memset(message, '\0', MAX_MESSAGE);

	hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
	hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

	getaddrinfo(hostname, port, &hints, &res);
	
	for (p = res; p != NULL; p = p->ai_next) {
		socket_fd = Socket(p->ai_family, p->ai_socktype, p->ai_protocol);

		if (socket_fd < 0) {
			continue;
		}

		if (connect(socket_fd, p->ai_addr, p->ai_addrlen) < 0) {
			printf("Failed to connect to server\n");
			socket_fd = -1;
		}

		break; // we made a connection successfully
	}

	if (socket_fd < 0) {
		printf("Unable to establish a connection with process at %s:%s\n", hostname, port);
		exit(1);
	}

	while (1) {
		printf("> ");

		if (fgets(message, MAX_MESSAGE, stdin) == NULL) {
			printf("Failed to read the message!\n");
			return 1;
		}

		if (strcmp(message, "exit\n") == 0) {
			break;
		} else {
			if (send(socket_fd, message, strlen(message), 0) < 0) {
				printf("Failed to send the message :(\n");
				return 1;
			}
		}
	}

	printf("Goodbye!\n");
	close(socket_fd);

	return 0;
}
