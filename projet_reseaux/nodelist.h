#include <sys/un.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdlib.h>
struct nodecalc {
	char op;
	int nb_args;
	struct sockaddr_in6 addr;
	int state;
	struct nodecalc* nextnode;
	int timealive;
};

struct nodecalc* addnode(struct nodecalc* list,
						char op,
						int nb_args,
						struct sockaddr_in6 addr,
						int state);
struct nodecalc* removenode(struct nodecalc* list, struct sockaddr_in6 addr);

struct nodecalc* searchnode(struct nodecalc* list, struct sockaddr_in6 addr);
