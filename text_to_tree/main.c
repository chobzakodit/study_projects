#include "orderedset.h"
#include "binarytree.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define	CODE_ERREUR	255
#define PUNCT " .,;:!?-\n\t"
#define MAX_LEN 256
char *prog;
//gestion des erreurs
void raler (int syserr, const char *fmt, ...){
    va_list ap ;

    va_start (ap, fmt) ;
    fprintf (stderr, "%s: ", prog) ;
    vfprintf (stderr, fmt, ap) ;
    fprintf (stderr, "\n") ;
    va_end (ap) ;

    if (syserr)
	perror ("") ;

    exit (CODE_ERREUR) ;
}

void usage (void){
    fprintf (stderr, "[Usage]: %s [fichier]\n", prog) ;
    exit (1) ;
}

int main(int argc,char *argv[]){
	prog=argv[0];
	if(argc != 2)
		usage();
	FILE *file;
	if((file=fopen(argv[1],"r")) == NULL)
		raler(1,"Can not open file");
	char *word;
	char st[MAX_LEN];
	unsigned int row=1;

	Tree root=initBinarySearchTree();
	while(fgets(st,256,file) != NULL){
		word=strtok(st,PUNCT);
		while(word!=NULL){
			root=insert(root,word,row);
			word=strtok(NULL,PUNCT);
		}
		row++;
	}
	fclose(file);
	printBinarySearchTree(root);
	printf("%f\n",getAverageDepth(root));
	printOrderedSet(findCooccurrences(root,"foo","waldo",NULL));
	freeBinarySearchTree(root);
	return 0;
}




