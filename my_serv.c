#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

typedef struct s { 
	int	socket;
	int	port;
	int	clientId;
	struct sockaddr_in addr;
} serv;

typedef struct c {
	int	fd;
	int	id;
	struct c *next;
} cli;

serv server;
cli *clients = NULL;

fd_set	open_fd, read_fd;

char msg[512], str_recv[123456], str_send[135791];

void	fatal() {
	write(2, "Fatal error\n", 12);
	exit(1);
}

int	getMaxFd(void) {
	int max = server.socket;
	for (cli *tmp = clients; tmp; tmp = tmp->next)
		if (tmp->fd > max)
			max = tmp->fd;
	return max;
}

int getId(int fd) {
	for (cli *tmp = clients; tmp; tmp = tmp->next)
		if (tmp->fd == fd)
			return tmp->id;
	return -1;
}

void sendAll(char *msg, int fdSender) {
	for (cli *tmp = clients; tmp; tmp = tmp->next)
		if (tmp->fd != fdSender)
			send(tmp->fd, msg, strlen(msg), 0);
}

void	removeClient(int fd) {
	if (clients && clients->fd == fd) {
		cli *tmp = clients;
		clients = clients->next;
	
		FD_CLR(tmp->fd, &open_fd);
		close(tmp->fd);
		free(tmp);
	}
	for (cli *tmp = clients; tmp; tmp = tmp->next) {
		if (tmp->next && tmp->next->fd == fd) {
			
			cli *freeing = tmp->next;
			tmp->next = tmp->next->next;

			FD_CLR(freeing->fd, &open_fd);
			close(freeing->fd);
			free(freeing);
		}
	}
}

void	newClient(void) {
	cli *newCli = malloc(sizeof(cli));
	if (!newCli)
		fatal();
	
	newCli->fd = accept(server.socket, NULL, NULL);
	if (newCli->fd < 0)
		return free(newCli);

	newCli->id = server.clientId++;
	newCli->next = clients;
	clients = newCli;

	bzero(&msg, sizeof(msg));
	sprintf(msg, "server: client %d just arrived\n", newCli->id);
	sendAll(msg, newCli->fd);

	FD_SET(newCli->fd, &open_fd);
}

void customer(int fd) {
	int size = 1;
	bzero(&str_recv, sizeof(str_recv));

	while (size == 1 && (!*str_recv || str_recv[strlen(str_recv) - 1] != '\n'))
		size = recv(fd, str_recv + strlen(str_recv), 1, 0);
	if (size == 0) {
		bzero(&msg, sizeof(msg));
		sprintf(msg, "server: client %d just left\n", getId(fd));
		sendAll(msg, fd);
		removeClient(fd);
		return ;
	}
	bzero(&str_send, sizeof(str_send));
	sprintf(str_send, "client %d: %s", getId(fd), str_recv);
	sendAll(str_send, fd);
}

void	handleRequest(int maxFD) {
	for (int fd = 0; fd <= maxFD; fd++) {
		if (FD_ISSET(fd, &read_fd) == 0)
			continue;
		if (fd == server.socket)
			return newClient();
		else
			return customer(fd);
	}
}

int	main(int ac, char **av) {
	if (ac != 2)
		(write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n")), exit(1));
	
	server.port = atoi(av[1]);
	server.clientId = 0;

	server.socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server.socket < 0)
		fatal();

	bzero(&server.addr, sizeof(server.addr));
	server.addr.sin_family = AF_INET; 
	server.addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); //127.0.0.1
	server.addr.sin_port = htons(server.port); 

	if ((bind(server.socket, (const struct sockaddr *)&server.addr, sizeof(server.addr))) != 0)
		fatal();
	if (listen(server.socket, 667) != 0)
		fatal();
	FD_ZERO(&open_fd);
	FD_SET(server.socket, &open_fd);

	while (1) {
		read_fd = open_fd;
		int maxFd = getMaxFd();
		if (select(maxFd + 1, &read_fd, NULL, NULL, NULL) < 0)
			fatal();
		handleRequest(maxFd);
	}
}