#define NB_ERROR -1
#define NB_SUCCESS 0
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "exprlist.h"
struct expr* addexpr(struct expr* list,struct expr* expr){
	expr->nextexpr=list;
	list=expr;
	return list;
}
struct expr* rmexpr(struct expr* list, char *date){
	struct expr* pointer=list;
	if(strcmp(pointer->date,date)==0){
		list=list->nextexpr;
		free(pointer);
		return list;
	}
	while(pointer->nextexpr!=NULL && strcmp(pointer->nextexpr->date,date)!=0){
		pointer=pointer->nextexpr;
	}
	struct expr* pointer2;
	//mais si expr n'est pas trouve', pas de modifications
	if(strcmp(pointer->nextexpr->date,date)==0){
		pointer2=pointer->nextexpr;
		pointer->nextexpr=pointer2->nextexpr;
		free(pointer2);
	}
	return list;
}

struct expr* searchexpr(struct expr* list, char* date){
	struct expr* pointer=list;
	while(pointer!=NULL && strcmp(pointer->date,date)!=0){
		pointer=pointer->nextexpr;
	}
	return pointer;
}

int strtoexpr(char *buf,struct expr *expr1){
	memset(expr1->arg1,'0',MAX_LEN_INT);
	memset(expr1->arg2,'0',MAX_LEN_INT);
	switch(buf[0])
	{
		case'+':expr1->op='+';
				break;
		case'-':expr1->op='-';
				break;
		case'*':expr1->op='*';
				break;
		case'/':expr1->op='/';
				break;
		default:
			return NB_ERROR;
	}
	if(buf[1]!='(' || buf[strlen(buf)-2]!=')'){
		return NB_ERROR;
	}

	int neg=0;
	char *arg1;
	char *arg2;
	char *sep=",()\n";
	int i;
	arg1=strtok(buf+2,sep);
	if(arg1!=NULL){
		i=0;
		if(arg1[0]=='-'){
			if(strlen(arg1)>MAX_LEN_INT)
				return NB_ERROR;
			neg=1;
			i=1;
		}else
			if(strlen(arg1)>MAX_LEN_INT-1)
				return NB_ERROR;

		for(; i<strlen(arg1) && i<MAX_LEN_INT; i++){
			if(arg1[i]<'0' || arg1[i]>'9')
				return NB_ERROR;
		}
	}
	else
		return NB_ERROR;

	if(neg){
		expr1->arg1[0]='-';
		strncpy(expr1->arg1+MAX_LEN_INT-strlen(arg1)+1,arg1+1,strlen(arg1)-1);
	}
	else
		strncpy(expr1->arg1+MAX_LEN_INT-strlen(arg1),arg1,strlen(arg1));

	neg=0;
	arg2=strtok(NULL,sep);

	if(arg2!=NULL){
		i=0;
		if(arg2[0]=='-'){
			if(strlen(arg2)>MAX_LEN_INT)
				return NB_ERROR;
			neg=1;
			i=1;
		}else
			if(strlen(arg2)>MAX_LEN_INT-1)
				return NB_ERROR;

		for(; i<strlen(arg2) && i<MAX_LEN_INT; i++){
			if(arg2[i]<'0' || arg2[i]>'9')
				return NB_ERROR;
		}
	}
	else
		return NB_ERROR;

	if((arg1=strtok(NULL,sep))!=NULL){
		return NB_ERROR;
	}
	if(neg){
		expr1->arg2[0]='-';
		strncpy(expr1->arg2+MAX_LEN_INT-strlen(arg2)+1,arg2+1,strlen(arg2)-1);
	}
	else
		strncpy(expr1->arg2+MAX_LEN_INT-strlen(arg2),arg2,strlen(arg2));

	return NB_SUCCESS;
}