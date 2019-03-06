#include <stdio.h>
#include <stdlib.h>
#include "orderedset.h"

OrderedSet initOrderedSet(){// qui crée un nouvel ensemble ordonné.
	OrderedSet init = malloc(sizeof(OrderedSet));
	init->first=NULL;
	return init;
}

void freeOrderedSet(OrderedSet set){// qui libère la mémoire allouée pour l’ensemble ordonné.
	if(set == NULL) 
		return;
	while(set->first != NULL){
		Elem *temp = set->first->next;
		free(set->first);
		set->first=temp;
	}
	free(set);
}

unsigned int getNumberElt(OrderedSet set){// qui renvoie le nombre d’éléments contenus dans l’ensemble ordonné.
	if (set==NULL || set->first==NULL){
		return 0;
	}
	Elem *temp;
	temp=set->first->next;
	unsigned int count=1;
	while(temp!=NULL){
		temp=temp->next;
		count++;
	}
	return count;
}

bool contains(unsigned int pos_srch,OrderedSet set){// qui teste si un élément appartient à l’ensemble ordonné.
	if (set->first==NULL){
		return false;
	}
	Elem *temp = set->first;
	while(temp != NULL){
		if(temp->pos == pos_srch){
			return true;
		} 
		temp=temp->next;
	}
	return false;
}

void printOrderedSet(OrderedSet set){// qui affiche un ensemble ordonné.
	if(set==NULL)
		return;
	if (set->first==NULL){
		printf("This is an empty list.\n");
		return;
	}
	Elem *temp = set->first;
	while(temp->next != NULL){
		printf("%d|",temp->pos );
		temp=temp->next;
	}
	printf("%d",temp->pos );
}

Elem* insertAfter(unsigned int value,Elem* elt){//qui crée un nouvel élément aprés elt;
	if (elt!=NULL){
		Elem *temp=malloc(sizeof(Elem));
		temp->next=elt->next;
		temp->pos=value;
		elt->next=temp;
	}
	return elt;
}
Elem* insertBefore(unsigned int value,Elem* elt){//qui crée un nouvel élément avant elt;
	Elem *temp=malloc(sizeof(Elem));
	temp->pos=value;
	temp->next=elt;
	return temp;
}
OrderedSet insertValue(unsigned int nouv_pos,OrderedSet set){ //qui insère un nouvel élément dans l’ensemble ordonné.
	if (set==NULL)
		return NULL;
	if(!contains(nouv_pos,set)){
		if(set->first==NULL){
			set->first=malloc(sizeof(Elem));
			set->first->pos=nouv_pos;
			set->first->next=NULL;
			return set;
		}
		if(nouv_pos<set->first->pos){
			set->first=insertBefore(nouv_pos,set->first);
			return set;
		}
		Elem* temp=set->first;
		
		while(temp->next!=NULL){
			if(nouv_pos<temp->next->pos){
				insertAfter(nouv_pos,temp);
				return set;
			}
			temp=temp->next;
		}
		insertAfter(nouv_pos,temp);
	}
	return set;
}
void inter2list(OrderedSet dest,OrderedSet set1,OrderedSet set2){//qui fait l'intersection de 2 ensembles ordonnés.
	if(dest==NULL||set1==NULL||set2==NULL)
		return;
	Elem *temp1=set1->first;
	Elem *temp2;
	while(temp1!=NULL){
		temp2=set2->first;
		while(temp2!=NULL){
			if(temp1->pos==temp2->pos){
				dest=insertValue(temp1->pos,dest);
			}
			temp2=temp2->next;
		}
		temp1=temp1->next;
	}
}
void intersect(OrderedSet dest,OrderedSet *tabSet,int n){//qui réalise l’intersection de plusieurs ensembles ordonnés.
	if(tabSet==NULL || dest==NULL || n<1)
		return;
	if(n==1){
		dest=tabSet[0];
		return;
	}
	inter2list(dest,tabSet[0],tabSet[1]);
	for(int i=2;i<n;i++)
		inter2list(dest,dest,tabSet[i]);
	return;
}















