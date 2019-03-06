/**
 *\file jeu.c
 *\author Gaydamakha Mikhail
 */
#include "jeu.h"
/**
 *\brief compte_voisins_vivants_non_cyclique compte le quantite de voisins vivants
avec limites non_cycliques
 *\param i position i
 *\param j position j
 *\param g grille
 *\return quant le quantite de voisins vivants de la cellule
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g){
        int quant= 0,l=g.nbl,c=g.nbc;
	if (limit(i-1,j-1,g)==1)
           { quant+= est_vivante(i-1,j-1,g);}
	if (limit(i-1,j,g)==1)
            {quant+= est_vivante(i-1,j,g);}
        if (limit(i-1,j+1,g)==1)
            {quant+= est_vivante(i-1,j+1,g);}
        if (limit(i,j-1,g)==1)
            {quant+= est_vivante(i,j-1,g);}
        if (limit(i,j+1,g)==1)
            {quant+= est_vivante(i,j+1,g);}
        if (limit(i+1,j-1,g)==1)
           { quant+= est_vivante(i+1,j-1,g);}
        if (limit(i+1,j,g)==1)
           { quant+= est_vivante(i+1,j,g);}
        if (limit(i+1,j+1,g)==1)
            {quant+= est_vivante(i+1,j+1,g);}
        return quant;
}
/**
 *\brief compte_voisins_vivants_cyclique compte le quantite de voisins vivants de la cellule (i,j)
avec bords cycliques
 *\param i position i
 *\param j position j
 *\param g grille
 *\return v le quantite de voisins vivants de la cellule (i,j)
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0,l=g.nbl,c=g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);
	return v;
}
/**
 *\brief limit teste si la cellule (i,j) dépasse la taille de la grille ou pas
 *\param i position i
 *\param j position j
 *\param g grille
 *\return 1 si la cellule est dans la grille, 0 sinon
 */
int limit (int i, int j, grille g) {
        if (i<0 || j<0 || i>(g.nbl - 1) || j>(g.nbc - 1)) return 0;
        else return 1;
}
/**
 *\brief evolue fait evoluer la grille g d'un pas de temps
 *\param g grille
 *\param gc grille
 *\param compte_voisins_vivants pointeur sur la fonction
compte_voisins_vivants_cyclique ou non_cyclique
 *\param change_age soit 1 si on pourrait faire viellir une cellule, 0 sinon
 */
void evolue (grille *g, grille *gc, int (*compte_voisins_vivants)(int i,int j,grille g), int change_age){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,vsn;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			vsn = compte_voisins_vivants (i, j, *gc);
			if (est_vivante(i,j,*g))
			{ // evolution d'une cellule vivante
				if (change_age==1){
					vieillissement(*g, i, j);
				}
				if ( vsn!=2 && vsn!= 3 ){
					set_morte(i,j,*g);
				}
			}
			else
			{ // evolution d'une cellule morte
				if ( vsn==3 && g->cellules[i][j]!=-1) {
					set_vivante(i,j,*g);
				}
			}
		}
	}
}
