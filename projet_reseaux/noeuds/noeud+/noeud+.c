#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <pthread.h>
#define MAX_LEN_INT 11
#define MAX_BUF 1024
#define NB_ERROR -1
#define NB_SUCCESS 0
#define PORT_ORCH 2020
#define TIME_WAIT 10
#define MAX_WAIT 50

char *prog;
int debug;

void raler(int syserr, const char *fmt,...) {
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);

	if (syserr) {
		perror("");
	}
	exit(EXIT_FAILURE);
}
void usage (void){
	fprintf (stderr, "%s <adresse_orchestrateur> <local_port> <debug {0,1}>\n", prog) ;
	exit (1) ;
}
/* socket du noeud */
int my_sockfd;
/* server address */
struct sockaddr_in* serveraddr4;//au cas si l'utilisateur choisit ipv4
struct sockaddr_in6* serveraddr6;//au cas si l'utilisateur choisit ipv6
struct sockaddr *serveraddr;//adresse du serveur pour unifier de adresse ci-dessus
socklen_t addrlen;

struct sockaddr_in my_addr;//au cas si l'utilisateur choisit ipv4
struct sockaddr_in6 my_addr6;//au cas si l'utilisateur choisit ipv6

void* announce(void *addr){//thread qui envoie les annonce chaque TIME_WAIT secondes
	char conditions[3]="+2\0";
	while(1){
		if(debug)
			printf("envoie %s len %d\n",conditions,sizeof(conditions)-1);

		if(sendto(my_sockfd,conditions,sizeof(conditions)-1,0,(struct sockaddr *)addr,addrlen)==-1)
			raler(1,"send");
		sleep(TIME_WAIT);
	}
}

int main(int argc,char *argv[]){
	prog=argv[0];
	if(argc!=4)
		usage();
	debug=atoi(argv[3]);
	if(debug!=0 && debug!=1)
		usage();

	char buf[MAX_BUF];

	int nbytes;

	int yes = 1;

	/* construction de l'adresse du serveur */
	serveraddr4=(struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	serveraddr6=(struct sockaddr_in6*)malloc(sizeof(struct sockaddr_in6));

	if(inet_pton(AF_INET, argv[1],(void*)&(serveraddr4->sin_addr)) == 1){
		free(serveraddr6);
		serveraddr6=NULL;
		serveraddr4->sin_port=htons(PORT_ORCH);
		serveraddr4->sin_family=AF_INET;
		serveraddr=(struct sockaddr*)serveraddr4;
		addrlen=sizeof(struct sockaddr_in);
	}
	else {
		if(inet_pton(AF_INET6, argv[1],(void*)&(serveraddr6->sin6_addr)) == 1){
			free(serveraddr4);
			serveraddr4=NULL;
			serveraddr6->sin6_port=htons(PORT_ORCH);
			serveraddr6->sin6_family=AF_INET6;
			serveraddr=(struct sockaddr*)serveraddr6;
			addrlen=sizeof(struct sockaddr_in6);
		}
		else{
			close(my_sockfd);
			raler(1,"inet_pton");
		}
	}

	/* adresse du noeud */
	if(serveraddr4!=NULL){
		if((my_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
			raler(1,"socket");
		if(debug)
   			printf("Socket is ok\n");
		/* bind */
		my_addr.sin_family = AF_INET;
		my_addr.sin_port	= htons(atoi(argv[2]));
		my_addr.sin_addr.s_addr   = htonl(INADDR_ANY);;

		if(bind(my_sockfd,(struct sockaddr *) &my_addr, sizeof(my_addr))==-1){
			close(my_sockfd);
			raler(1,"bind");
		}
		if(debug)
   			printf("Bind is ok\n");
	}
	else{
		if((my_sockfd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)) == -1)
			raler(1,"socket");

		if(debug)
   			printf("Socket is ok\n");

		/* bind */
		my_addr6.sin6_family = AF_INET6;
		my_addr6.sin6_port	 = htons(atoi(argv[2]));
		my_addr6.sin6_addr   = in6addr_any;

		if(bind(my_sockfd,(struct sockaddr *) &my_addr6, sizeof(my_addr6))==-1){
			close(my_sockfd);
			raler(1,"bind");
		}
		if(debug)
   			printf("Bind is ok\n");
	}
   	
	
	/*"address already in use" message d'erreur*/
	if(setsockopt(my_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
		close(my_sockfd);
		raler(1,"setsockopt");
	}

	if(debug)
   		printf("Setsockopt is ok\n");

	pthread_t announcer;//creer thread qui fait les annonces
	if(pthread_create(&announcer, NULL, announce,(void*)serveraddr)!=0)
			raler(1,"pthread_create");

	char carg1[MAX_LEN_INT+1];//+1 pour '\0'
	char carg2[MAX_LEN_INT+1];
	char cres[MAX_LEN_INT+1];
	int arg1;
	int arg2;
	int res;
	char tmpres[MAX_LEN_INT];
	char date[6];
	int r;
	while(1){
		memset(buf,'\0',sizeof(buf));
		if((nbytes=recvfrom(my_sockfd, buf, sizeof(buf), 0, serveraddr, &addrlen)) == -1)
        		perror("recvfrom");

        if (nbytes==28){//donnees 'a traiter
        	int i;
        	for(i=0;i<nbytes && ((buf[i]>='0' && buf[i]<='9') || buf[i]=='-');i++){ }
        	if(i!=nbytes){
        		//invalide formate de la message, demande de se liberer
        		if(debug){
        			fprintf(stderr,"Invalide format of message\n");
        		}
        		//demander le serveur de se liberer (paquet d'erreur)
				if(sendto(my_sockfd,"0",1,0,serveraddr,addrlen)==-1)
					perror("send");
				continue;
        	}
         	else{
         		//convertir le message
         		strncpy(date,buf,6);
				strncpy(carg1,buf+6,11);
				strncpy(carg2,buf+17,11);
				arg1=atoi(carg1);
				arg2=atoi(carg2);
				//faire le calcul
				res=arg1+arg2;
				//reconvertir le resultat
				sprintf(tmpres,"%d",res);
				memset(cres,'0',MAX_LEN_INT);
				if(res<0){
					cres[0]='-';
					strncpy(cres+MAX_LEN_INT-strlen(tmpres)+1,tmpres+1,strlen(tmpres)-1);
				}
				else{
					strncpy(cres+MAX_LEN_INT-strlen(tmpres),tmpres,strlen(tmpres));
				}
				//attendre quelque secondes (MAX_WAIT au maximum)
				srand(time(NULL));
				r=rand() % (MAX_WAIT+1);
				if(debug)
					sleep(1);
				else
					sleep(r);
				//effacer les donne'es pre'ce'dentes
				memset(buf,'\0',sizeof(buf));
				//formater le message
				strncpy(buf,date,6);	
				strncpy(buf+6,cres,11);
				if(debug)
					printf("envoie %s, len %d\n",buf,strlen(buf));
				//envoyer-le
				if(sendto(my_sockfd,buf,strlen(buf),0,serveraddr,addrlen)==-1)
					perror("send");
         	}
        }
        else{
			if(debug)
					fprintf(stderr,"Invalide format of message\n");
				
			if(sendto(my_sockfd,"0",1,0,serveraddr,addrlen)==-1)
				perror("send");
        }
	}
}
