#include "binarytree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 256
Tree initBinarySearchTree(){ //qui crée un nouvel arbre binaire de recherche vide.
	Tree root;
	root=malloc(sizeof(struct _bTree));		
	root->word=malloc(MAX_LEN);
	memset(root->word,0,MAX_LEN);
	root->positions=initOrderedSet();
	root->left=NULL;
	root->right=NULL;
	root->height=1;
	return root;
}
void freeBinarySearchTree(Tree root){ //qui libère la mémoire allouée pour l’arbre.
	if(root==NULL)
		return;
	freeBinarySearchTree(root->left);
	freeBinarySearchTree(root->right);
	freeOrderedSet(root->positions);
	free(root->word);
	free(root);
}
unsigned int getNumberString(Tree root){ //qui renvoie le nombre de mots différents contenus dans l’arbre.
	if(root==NULL)
		return 0;
	static unsigned int result=0;
	result=getNumberString(root->left)+getNumberString(root->right)+1;
	return result;
}
unsigned int getTotalNumberString(Tree root){//qui renvoie le nombre de paires mots-phrases différentes contenues dans l'arbre
	if(root==NULL)
		return 0;
	static unsigned int result=0;
	result=getNumberElt(root->positions)+getTotalNumberString(root->left)+getTotalNumberString(root->right);
	return result;
}
bool isBalanced(Tree root){//qui d´etermine si l’arbre est ´equilibr´e ou non.
	if(root ==NULL)
		return true;
	if(getFactor(root) ==1 || getFactor(root) ==0 || getFactor(root) ==-1)
		return true && isBalanced(root->left) && isBalanced(root->right);
	return false;
}
int getFactor(Tree root){//qui renvoie le facteur de balance d'un noeud
	return getHeight(root->right)-getHeight(root->left);
}
unsigned int getHeight(Tree root){//qui renvoie la hauteur de l’arbre.
	return (root!=NULL)?root->height:0;
}
void recountHeight(Tree root){//qui recompte la hauteur d'un noeud
	if(root){
		int h1=getHeight(root->left);
		int h2=getHeight(root->right);
		root->height=(h1>h2?h1:h2)+1;
	}
}
Tree rotateLeft(Tree root){//réalise rotation simple gauche
	Tree temp=root->right;
	root->right=temp->left;
	temp->left=root;
	recountHeight(temp);
	recountHeight(root);
	return temp;	
}
Tree rotateRight(Tree root){//réalise rotation simple droite
	Tree temp=root->left;
	root->left=temp->right;
	temp->right=root;
	recountHeight(root);
	recountHeight(temp);
	return temp;
}
Tree rotateLeftRight(Tree root){//réalise rotation double gauche-droite
	root->left=rotateLeft(root->left);
	root=rotateRight(root);
	return root;
}
Tree rotateRightLeft(Tree root){//réalise rotation double droite-gauche
	root->right=rotateRight(root->right);
	root=rotateLeft(root);
	return root;
}
Tree balance(Tree root){//qui équilibre le (sous)arbre
	recountHeight(root);
	if(getFactor(root)==2){
		if(getFactor(root->right)==1){
			return root=rotateLeft(root);
		}
		else if(getFactor(root->right)==-1){
			return root=rotateRightLeft(root);
		}
	}
	else if(getFactor(root)==-2){
		if(getFactor(root->left)==-1){	
			return root=rotateRight(root);
		}
		else if(getFactor(root->left)==1){
			return root=rotateLeftRight(root);
		}
	}
	return root;
}
Tree insert(Tree root,char *word,unsigned int pos){//qui permet d’ajouter une nouvelle paire mot-position dans l’arbre
	if(root==NULL){
		root=initBinarySearchTree();
		root->word=strcpy(root->word,word);
 		insertValue(pos,root->positions);
 		return root;
	}
	if(strcmp(root->word,"")==0){
		root->word=strcpy(root->word,word);
		insertValue(pos,root->positions);
		return root;
	}
	if(strcmp(word,root->word)<0)
		root->left=insert(root->left,word,pos);
	else if(strcmp(word,root->word)>0)
		root->right=insert(root->right,word,pos);
	else if(!contains(pos,root->positions))//le cas ou le mot deja existe
		insertValue(pos,root->positions);
	root=balance(root);
	return root;
}

Tree find(Tree root,char* word){ //qui permet de retrouver tous les indices d’occurrences d’un mot.
	if(root==NULL || strcmp(root->word,word)==0)
		return root;
	if(strcmp(word,root->word)<0)
		return find(root->left,word);
	else
		return find(root->right,word);
}
OrderedSet findCooccurrences(Tree root,char* word,...){ //qui permet de retrouver tous les indices de coocurrences de plusieurs mots.
	char* temp;
	va_list arg_ptr;
	va_start(arg_ptr,word);
	temp=va_arg(arg_ptr,char*);
	int n=1;
	while(temp!=NULL){
		n++;
		temp=va_arg(arg_ptr,char*);
	}
	va_end(arg_ptr);
	OrderedSet *tabSet=malloc(n*sizeof(OrderedSet*));
	tabSet[0]=find(root,word)->positions;

	va_start(arg_ptr,word);
	temp=va_arg(arg_ptr,char*);
	for(int i=1;i<n;i++){
		tabSet[i]=find(root,temp)->positions;
		temp=va_arg(arg_ptr,char*);
	}
	va_end(arg_ptr);
	OrderedSet result=initOrderedSet();
	intersect(result,tabSet,n);
	free(tabSet);
	return result;
}
int getSumOfHeight(Tree root){
	int res=0;
	if(root != NULL)
		res=getHeight(root)+getSumOfHeight(root->left)+getSumOfHeight(root->right);	
	return res;
}
double getAverageDepth(Tree root){
	return getSumOfHeight(root)/getNumberString(root);
}
//affichage
Queue init_queue(){//qui initialise la queue  
	Queue queue=malloc(sizeof(struct _Queue));
	queue->head = queue->tail = NULL;
	return queue;
}

void enQueue(Queue pQueue,Tree pTNode,int pDepth){//qui ajoute un élément dans la queue
	QNode pQNode = (QNode)malloc(sizeof(struct _q_node));  
	pQNode->depth = pDepth;  
	pQNode->blank = 0;
	if(pTNode==NULL){
		pQNode->blank=1;
	}
	pQNode->t_node= pTNode;  
	if(pQueue->head == NULL){
		pQueue->head = pQNode;   
		pQueue->tail = pQNode;       
	}
	else{
		pQueue->tail->next = pQNode;
		pQueue->tail = pQNode;  
	}
}
QNode deQueue(Queue pQueue){//qui deinsère un element de queue
	if(pQueue->head == NULL){
		return NULL;
	}
	QNode deNode= pQueue->head;
	pQueue->head = pQueue->head->next;
	return deNode;
}  
int ifEmpty(Queue pQueue){//qui vérifie si la queue est vide
	if(pQueue->head == NULL)
		return 0;
	return 1;  
}
void printBinarySearchTree(Tree pRoot){//qui affiche un arbre binaire de recherche.
	int height = getHeight(pRoot);
	int pad_num = 4;
	int current_depth = 1;
	if(!pRoot)
		return;
	Queue pQueue=init_queue();
	enQueue(pQueue,pRoot,1);
	printf("_______________________\n");
	printf("Tree Begin to print:\n");

	while(ifEmpty(pQueue)!=0){
		QNode  qNode  = deQueue(pQueue);
		//la profondeur de sous-noeud est augmenté par un par rapport à celle de parent
		int child_depth = qNode->depth+1;
		if(qNode->depth > current_depth){
			current_depth = qNode->depth;
			printf("\n\n");
		}
		int pad_front = (1<< (height - current_depth))-1;
		if(qNode->blank == 1)
		{
			//ajouter des espaces de parent
			if(pad_front == 0)
				printf("%*s%*s",pad_num," ",pad_num," ");
			else
				printf("%*s%*s%*s",pad_front*pad_num," ",pad_num," ",(1+pad_front)*pad_num," ");
			if(child_depth<=height){
				//ajouter deux nouveaux noeud-null qui corréspond à QNode blanc
				enQueue(pQueue,NULL,child_depth);
				enQueue(pQueue,NULL,child_depth);
			}
		}
		else{
			if(pad_front == 0){
				printf("%*s ",pad_num,qNode->t_node->word);
				printOrderedSet(qNode->t_node->positions);
				printf(" %d%*s",qNode->t_node->height,pad_num," ");
			}
			else{
				printf("%*s%*s ",pad_front*pad_num," ",pad_num,qNode->t_node->word);
				printOrderedSet(qNode->t_node->positions);
				printf(" %d%*s",qNode->t_node->height,(1+pad_front)*pad_num," ");
			}
			if(child_depth <=height){
				enQueue(pQueue,qNode->t_node->left,child_depth);
				enQueue(pQueue,qNode->t_node->right,child_depth);
			}
		}
		free(qNode);
	} //fin while
	printf("\n");
	free(pQueue);
	return;
}