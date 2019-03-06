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
#include <signal.h>
#include "nodelist.h"
#include "exprlist.h"
#define MAX_TIMEALIVE 35 //temps maximal de l'attente de l'annonce d'un noeud
#define MAX_BUF 1024
#define EXIT_STR "exit\n"
#define NB_ERROR -1 /*erreur, en general de parsing*/
#define NB_SUCCESS 0
#define FREE 1	//si un noeud est libre
#define OCCUPIED 0 //cas contraire
#define PORT 2020 //port d'ecoute du serveur

char *prog; //nom du programm, pour "usage"
int debug; //debug option

void raler(int syserr, const char *fmt,...) { //message d'erreur
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
	fprintf (stderr, "%s <debug mod {0,1}>\n", prog) ;
	exit (1) ;
}
//traiter l'annonce d'un noeud et mettre 'a jour ses informations principales
int traiter_annonce(struct nodecalc* pointer,char *buf){ 
	switch(buf[0]){
		case '+':pointer->op='+';
				break;
		case '-':pointer->op='-';
				break;
		case '*':pointer->op='*';
				break;
		case '/':pointer->op='/';
				break;
		default:
				return NB_ERROR;
	}
	if(buf[1]>='0' && buf[1]<='9')
		pointer->nb_args=atoi(&buf[1]);
	else{
		pointer->op='?';
		return NB_ERROR;/*error of parsing*/
	}
	pointer->timealive=0;
	return NB_SUCCESS;
}
//liste des noeuds globale 
struct nodecalc *nodelist=NULL;
//liste des expressions 'a resoudre
struct expr *exprlist=NULL;
//descripteur de socket du serveur
int listener;

//maintien la liste des noeuds et traite toutes les annonces
void *manager_of_list(void* port){
	/* server adress */
	struct sockaddr_in6 serveraddr;
	/* noeud adress 
	* sockaddr_in6 p.q. ipv4 sont traiter comme ipv6 aussi
	*/
	struct sockaddr_in6 clientaddr;
	/* longeur des adresses*/
	socklen_t addrlen;
	/* buffer pour le data d'un nieud */
	char buf[MAX_BUF];
	int nbytes;
	/* pour setsockopt() SO_REUSEADDR, ci-dessous */
	int yes = 1;

	if((listener = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)) == -1)
       raler(1,"Orchestrateur-socket");

   	if(debug)
   		printf("Socket is ok\n");
    /*"address already in use" message d'erreur */
	if(setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
		close(listener);
		raler(1,"setsockopt");
	}

	if(debug)
   		printf("Setsockopt is ok\n");

    /* bind */
    serveraddr.sin6_family      = AF_INET6;
    serveraddr.sin6_port        = htons(PORT);
    serveraddr.sin6_addr        = in6addr_any;
    addrlen 					= sizeof(serveraddr);
    if(bind(listener, (struct sockaddr *) &serveraddr, addrlen) == -1){
    	close(listener);
        raler(1,"bind");
    }

    if(debug)
   		printf("Bind is ok\n");

	struct nodecalc* pointer;
	struct expr* exprpointer;
	char date[DATE_LEN];
	char addrbuf[INET6_ADDRSTRLEN];
	/* loop */
	for(;;){
		//effacer l'information precedente
		memset(buf,'\0',sizeof(buf));
		memset(addrbuf,'\0',sizeof(addrbuf));
		memset(date,'\0',sizeof(date));
		if((nbytes=recvfrom(listener, buf, sizeof(buf), 0, (struct sockaddr *) &clientaddr, &addrlen)) == -1)
        	perror("recvfrom");

        //la recherce d'une noeud
		pointer=searchnode(nodelist, clientaddr);

    	if(pointer==NULL){/*noeud n'est pas trouve', nouvelle connection*/
    		if(nbytes==2){
    			//ajouter nouvelle n
				nodelist=addnode(nodelist, '?', 0, clientaddr, FREE);
				/*traiter l'annonce */
				if(traiter_annonce(nodelist,buf)==NB_ERROR){
					if(debug)
						fprintf(stderr,"Don't support this format in first message\n");
					continue;
				}
				if(debug){
					if(inet_ntop(AF_INET6,&clientaddr.sin6_addr.s6_addr,addrbuf,INET6_ADDRSTRLEN)==NULL)
						perror("inet_ntop");
					else{
						printf("New connection from %s on port %d\n",
										addrbuf,
										clientaddr.sin6_port);
					}
				}	
			}
			else{
				/* refuser connection- c.'a.d ne pas ajouter nouvelle noeud*/
				if(debug)
					fprintf(stderr,"Don't support this format in first message\n");
			}
    	}
    	else{/*connection existante- "pointer" point 'a noeud qui envoie qch*/
    		
    		if(nbytes==0){//message vide
    			nodelist=removenode(nodelist, clientaddr);
    			if(debug)
    				printf("Orchestrateur: port %d hung up\n", clientaddr.sin6_port);
    		}
    		else if (nbytes==1 && buf[0]=='0'){//demande de noeud de se liberer
    			pointer->state=FREE;//liberer noeud
    		}
    		else if (nbytes==2){//annonce que noeud est encore vivant
    			if(debug){
    				printf("Announce received:%s len %d\n",buf,nbytes);
    			}
				if(traiter_annonce(pointer,buf)==NB_ERROR){
					if(debug)
						fprintf(stderr,"Don't support this format in announce\n");
					continue;
				}
				pointer->timealive=0;//mettre 'a zero son temps de l'attente de l'annonce
    		}
    		else if (nbytes==17){/* on a recu le message a afficher */
    			strncpy(date,buf,6);
    			//chercher l'expression correspondate 'a resoudre
    			if((exprpointer=searchexpr(exprlist,date))==NULL){
    				if(debug)
    					fprintf(stderr,"The expression not found\n");
    				pointer->state=FREE;
    				continue;
    			}
    			//elle est trouve', afficher le resultat
    			fprintf(stdout,"\n%c%c:%c%c:%c%c ",date[0],date[1],date[2],date[3],date[4],date[5]);

    			int arg1=atoi(exprpointer->arg1);
    			int arg2=atoi(exprpointer->arg2);
    			char cres[11];
    			strncpy(cres,buf+6,11);
    			int res=atoi(cres);
    			fprintf(stdout,"%c(%d,%d) = %d ",exprpointer->op,arg1,arg2,res);

    			if(inet_ntop(AF_INET6,clientaddr.sin6_addr.s6_addr,addrbuf,INET6_ADDRSTRLEN)==NULL)
					perror("inet_ntop");

    			time_t horloge;
				struct tm *tm;
				horloge=time(NULL);
				tm=localtime(&horloge);
				if(strftime(date, sizeof date, "%T", tm) <= 0) 
					perror("strftime");

    			fprintf(stdout,"by <%s> at %s\n",addrbuf,date);
				//liberer le noeud
				pointer->state=FREE;
				//retirer l'expression de liste 'a resoudre
    			exprlist=rmexpr(exprlist,exprpointer->date);
    		}
    	}
	}
	pthread_exit(EXIT_SUCCESS);
}
//mettre 'a jour temps de l'attente de l'annonce pour chaque noeud
//retirer de la liste si l'attente est trop long
void* clock_func(void* arg){
	struct nodecalc* pointer;
	struct sockaddr_in6 clientaddr;
	while(1){
		sleep(1);
		pointer=nodelist;
		while(pointer!=NULL){
			pointer->timealive+=1;
			if(pointer->timealive>MAX_TIMEALIVE){//retirer
				if(debug)
					printf("clock_func: removing %d\n",pointer->addr.sin6_port);

				clientaddr=pointer->addr;
				pointer=pointer->nextnode;
				nodelist=removenode(nodelist,clientaddr);
			}
			else
				pointer=pointer->nextnode;
		}
	}
}

int main(int argc, char **argv){

	prog=argv[0];
	if(argc != 2)
		usage();
	
	debug=atoi(argv[1]);
	if(debug!=0 && debug!=1)
		usage();

	char buf[MAX_BUF];
	memset(buf,'\0',sizeof(buf));
	//creer thread qui g'ere retire les noeuds "vieux"
	pthread_t clock;

	if(pthread_create(&clock, NULL, clock_func,NULL)!=0)
		raler(1,"pthread_create");

	//creer thread qui g'ere les noeuds
	pthread_t manager;

	if(pthread_create(&manager, NULL, manager_of_list,NULL)!=0)
		raler(1,"pthread_create");

	struct expr *expr;

	fprintf(stdout,"orchestrateur> ");

	while(strcmp(fgets(buf,MAX_BUF,stdin),EXIT_STR)!=0){//recevoir demande d'utilisateur

		expr=malloc(sizeof(struct expr));
		if(strtoexpr(buf,expr)==NB_ERROR){
			fprintf(stderr,"Expression mal formé\n");
			fprintf(stdout,"orchestrateur> ");
			continue;//refuser calcul
		}

		struct nodecalc* pointer=nodelist;

		while(pointer!=NULL){//prendre premier noeud libre convenant
		 	if(expr->op==pointer->op && pointer->state && pointer->nb_args==2)
				break;
			else
				pointer=pointer->nextnode;
		}
		
		if(pointer==NULL){//noeud n'est pas trouve'
			fprintf(stdout,"Aucun noeud disponible pour %c\n",expr->op);
			fprintf(stdout,"orchestrateur> ");
			continue;//refuser calcul
		}
		else{
			//enregistrer le temps de la demande
			time_t horloge;
			struct tm *tm;
			char date [7];
			horloge=time(NULL);
			tm=localtime(&horloge);
			if(strftime(date, sizeof date, "%H%M%S", tm) <= 0) 
				perror("strftime");
			//formater: HHMMSS<arg1><arg2>
			sprintf(buf,"%s%s%s",date,expr->arg1,expr->arg2);
			sprintf(expr->date,"%s",date);
			exprlist=addexpr(exprlist,expr);
			//envoyer 'a noeud
			if(debug)
				printf("envoie %s, len:%d\n",buf,strlen(buf));

			if(sendto(listener,buf,strlen(buf),0,(struct sockaddr*)&pointer->addr,sizeof(pointer->addr))==-1)
				perror("sendto");
			pointer->state=OCCUPIED;
		}
		fprintf(stdout,"orchestrateur> ");	
	}
	//tuer les thread avant de finir
	pthread_kill(manager,SIGINT);
	pthread_kill(clock,SIGINT);
	
	return 0;
}