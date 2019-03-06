/**
 *\file grille.c
 *\author Gaydamakha Mikhail
 */
#include "grille.h"
/**
 *\brief init_grille_from_file alloue et initalise la grille g à partir d'un fichier
 *\param filename nom du fichier à ouvrir
 *\param g grille
 */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);

	int i,j,n,l,c,vivantes,non_viables=0;

	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);

	alloue_grille(l,c,g);

	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	fscanf(pfile, "%d", & non_viables);
	for (n=0; n< non_viables; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_non_viable(i,j,*g);
	}
	fclose (pfile);
}
/**
 *\brief alloue_grille initialisation de grille de taille l*c,
tout les cellules par defaut sont mortes
 *\param l nombre de ligne
 *\param c nombre de colonnes
 *\param g grille
 */
void alloue_grille (int l, int c, grille* g){
	g->nbl=l;
	g->nbc=c;
	g->cellules=calloc(l, sizeof(int*));
	g->age=calloc(l,sizeof(int*));
	for(int i=0;i<l;i++){
		g->cellules[i]=calloc(c,sizeof(int));
		g->age[i]=calloc(c,sizeof(int));
		for (int j=0;j<c;j++){
			set_morte(i,j,*g);
			g->age[i][j]=0;
		}
	}
}
/**
 *\brief libere_grille liberation de memoire qui est occupee par grille
 *\param g grille
 */
void libere_grille (grille* g){
	for(int i=0;i<(g->nbl);i++){
		free(g->cellules[i]);
		free(g->age[i]);
	}
	free(g->cellules);
	free(g->age);
}
/**
 *\brief copie_grille recopie gs dans gd (sans allocation)
 *\param gs grille
 *\param gd grille
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
}
/**
 *\brief vieillissement change l'age de cellule
 *\param g grille
 *\param i ligne
 *\param j colonne
 */
void vieillissement (grille g, int i, int j){
  g.age[i][j]+=1;
}
