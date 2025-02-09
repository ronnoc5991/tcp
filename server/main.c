#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12000
#define BUFFER_SIZE 100

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

int main(int argc, char **argv) {
	int socket_fd;
	char buffer[BUFFER_SIZE];
	struct sockaddr_in server_addr, client_addr;
	int client_struct_length = sizeof(client_addr);

	memset(buffer, '\0', BUFFER_SIZE);
	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	memset(&client_addr, 0, sizeof(struct sockaddr_in));

    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(PORT); 
 	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	// create a TCP socket
	socket_fd = Socket(AF_INET, SOCK_STREAM, 0);

	// bind that socket to our port of choice
	Bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	// turn this into a 'listening' socket
	Listen(socket_fd, 10);

	printf("Server listening on port %d...\n", PORT);

	int connected_fd = -1;
	struct sockaddr client_address;
	socklen_t client_addr_len = sizeof(client_address);

	while ((connected_fd = accept(socket_fd, &client_address, &client_addr_len)) > 0) {
		while (read(connected_fd, buffer, BUFFER_SIZE) > 0) {
			printf("From client: %s", buffer);
			memset(buffer, '\0', BUFFER_SIZE);
		}

		printf("Closing connection...\n");
		close(connected_fd);
	}

	close(socket_fd);

	return 0;
}
