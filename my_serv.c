#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

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

int	open_fd;
int	read_fd;

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

void	newClient(void) {
	cli *newCli = malloc(sizeof(cli));
	if (!newCli)
		fatal();

	newCli->fd = server.clientId++;
	newCli->next = clients;
	clients = newCli;

	bzero(&msg, sizeof(msg));
	sprintf(msg, "server: client %d just arrived\n", newCli->id);
	sendAll(msg, newCli->fd);
}



void	handleRequest(int maxFD) {
	for (int fd = 0; fd < maxFD; fd++) {
		if (!FD_ISSET(fd, &read_fd) == 0)
			continue;
		if (fd == server.socket)
			return (void)newClient();
		else
			return (void)customer(fd);
	}
}

int	main(int ac, char **av) {
	if (ac != 2)
		(write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"), exit(1)));
	server.port = atoi(av[1]);
	server.clientId = 0;

	if (server.socket = socket(AF_INET, SOCK_STREAM, 0) < 0)
		fatal();

	bzero(&server.addr, sizeof(server.addr));
	server.addr.sin_family = AF_INET; 
	server.addr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
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