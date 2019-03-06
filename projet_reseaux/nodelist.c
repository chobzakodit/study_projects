#include "nodelist.h"

struct nodecalc* addnode(struct nodecalc* list,
						char op, 
						int nb_args,
						struct sockaddr_in6 addr,
						int state){
	struct nodecalc* new=malloc(sizeof(struct nodecalc));
	new->op=op;
	new->nb_args=nb_args;
	new->addr=addr;
	new->state=state;
	new->nextnode=list;
	list=new;
	return list;
}
struct nodecalc* removenode(struct nodecalc* list, struct sockaddr_in6 addr){
	struct nodecalc* pointer=list;
	if(pointer->addr.sin6_port==addr.sin6_port){
		list=list->nextnode;
		free(pointer);
		return list;
	}
	while(pointer->nextnode!=NULL && pointer->nextnode->addr.sin6_port!=addr.sin6_port){ 
		pointer=pointer->nextnode;
	}
	struct nodecalc* pointer2;
	//mais si noeud n'est pas trouve', pas de modifications
	if(pointer->nextnode->addr.sin6_port==addr.sin6_port){ 
		pointer2=pointer->nextnode;
		pointer->nextnode=pointer2->nextnode;
		free(pointer2);
	}
	return list;
}
struct nodecalc* searchnode(struct nodecalc* list,struct sockaddr_in6 addr){
	struct nodecalc* pointer=list;

	while(pointer!=NULL && pointer->addr.sin6_port!=addr.sin6_port)
		pointer=pointer->nextnode;

	return pointer;
}