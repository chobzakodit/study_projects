#include "orderedset.h"
#include <stdarg.h> 
#ifndef __BINARY_TREE__
#define __BINARY_TREE__
typedef struct _bTree{
	char* word;
	OrderedSet positions;
	struct _bTree *left;
	struct _bTree *right;
	int height;
} *Tree;
//des structures utilisées lors de l'affichage
typedef struct _q_node  
{  
  Tree t_node;  
  int depth;  
  int blank;  //0 veut dire que un noeud n'est pas null
  struct _q_node *next;  
}*QNode;  

typedef struct _Queue
{  
   QNode head;  
   QNode tail;  
}*Queue;

Tree initBinarySearchTree(); //qui crée un nouvel arbre binaire de recherche vide.
void freeBinarySearchTree(Tree root); //qui libère la mémoire allouée pour l’arbre.
unsigned int getNumberString(Tree root); //qui renvoie le nombre de mots différents contenus dans l’arbre.
unsigned int getTotalNumberString(Tree root); //qui renvoie le nombre de paires mots-phrases différentes contenues dans l'arbre
bool isBalanced(Tree root);//qui détermine si l’arbre est équilibré ou non.
int getFactor(Tree root);//qui renvoie le facteur de balance d'un noeud
unsigned int getHeight(Tree root); //qui renvoie la hauteur de l’arbre.
void recountHeight(Tree root);//qui recompte la hauteur d'un noeud.
Tree rotateLeft(Tree root);//réalise rotation simple gauche
Tree rotateRight(Tree root);//réalise rotation simple droite
Tree rotateLeftRight(Tree root);//réalise rotation double gauche-droite
Tree rotateRightLeft(Tree root);//réalise rotation double droite-gauche
Tree balance(Tree root);//qui équilibre le (sous)arbre
Tree insert(Tree root,char *word,unsigned int pos);//qui permet d’ajouter une nouvelle paire mot-position dans l’arbre
Tree find(Tree root,char* word); //qui permet de retrouver tous les indices d’occurrences d’un mot.
OrderedSet findCooccurrences(Tree root,char* word,...); //qui permet de retrouver tous les indices de coocurrences de plusieurs mots.
int getSumOfHeight(Tree root);//qui fait la somme de tous les hateurs d'un arbre.
double getAverageDepth(Tree root);//qui renvoie la profondeur moyenne de chaque noeud de l’arbre.
//les fonctions utilisées lors de l'affichage
Queue init_queue();//qui initialise la queue.
void enQueue(Queue pQueue,Tree pTNode,int pDepth);//qui ajoute un élément dans la queue.
QNode deQueue(Queue pQueue);//qui fait extraction d'un element de queue.
int ifEmpty(Queue pQueue);//qui vérifie si la queue est vide.
void printBinarySearchTree(Tree pRoot); //qui affiche un arbre binaire de recherche.
#endif