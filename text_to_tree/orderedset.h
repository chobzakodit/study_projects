#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#ifndef __ORDERED_SET__
#define __ORDERED_SET__
typedef struct _elem {
	unsigned int pos;
	struct _elem *next;
} Elem;
typedef struct _list
{
	Elem *first;
} *OrderedSet;
OrderedSet initOrderedSet();// qui crée un nouvel ensemble ordonné.
void freeOrderedSet(OrderedSet set);// qui libère la mémoire allouée pour l’ensemble ordonné.
unsigned int getNumberElt(OrderedSet set);// qui renvoie le nombre d’éléments contenus dans l’ensemble ordonné.
Elem* insertAfter(unsigned int value,Elem *elt);//qui crée un nouvel élément aprés elt;
Elem* insertBefore(unsigned int value,Elem *elt);//qui crée un nouvel élément avant elt;
OrderedSet insertValue(unsigned int nouv_pos,OrderedSet set); //qui insère un nouvel élément dans l’ensemble ordonné.
bool contains(unsigned int pos_srch,OrderedSet set);// qui teste si un élément appartient à l’ensemble ordonné.
void printOrderedSet(OrderedSet set);// qui affiche un ensemble ordonné.
void inter2list(OrderedSet dest,OrderedSet set1,OrderedSet set2);//qui fait l'intersection de 2 ensembles ordonnés.
void intersect(OrderedSet dest,OrderedSet *tabSet,int n); //qui réalise l’intersection de plusieurs ensembles ordonnés.
#endif