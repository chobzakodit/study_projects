/**
 *\file io.c
 *\author Gaydamakha Mikhail
 */
#include "io.h"
/**
 *\brief affiche_trait affichage d'un trait horizontal
 *\param c quantite de case
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
}
/**
 *\brief affiche_ligne affichage d'une ligne de la grille
 *\param g grille
 *\param l numero de la ligne à afficher
 */
void affiche_ligne (grille g, int l){
	for (int i=0; i<g.nbc; ++i){
		if(est_vivante(l,i,g)) printf("|%d  ",g.age[l][i]);
		else{
			if(g.cellules[l][i]==-1) printf("| X ");
			else printf("|   ");
		}
	}
	printf("|\n");
}
/**
 *\brief affiche_grille affichage d'une grille
 *\param g grille
 */
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(g, i);
		affiche_trait(c);
	}
	printf("\n");
}
/**
 *\brief efface_grille effacement d'une grille
 *\param g grille
 */
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5);
}
/**
 *\brief debut_jeu debute le jeu
 *\param g grille
 *\param gc grille
 *\param truc sert à signaler, si l'utilisateur veut charger un autre fichier
 */
void debut_jeu(grille *g,grille *gc,char *truc){
	char c = getchar();
	int (*compte_voisin_vivants)(int i,int j, grille g)=compte_voisins_vivants_non_cyclique;
	int n=0,change_age=0;
	printf("\n");
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				n++;
				evolue(g,gc,*compte_voisin_vivants,change_age);
				efface_grille(*g);
				printf("\rPas de temps N:%d",n);
				affiche_grille(*g);
				break;
			}
			case 'c':
			{// touche 'c' pour changer le mode de verification de voisinage
        			if (compte_voisin_vivants == &compte_voisins_vivants_cyclique){
						printf("Mode:Non_cyclique");
          				compte_voisin_vivants=&compte_voisins_vivants_non_cyclique;
          				break;
				}
			        if (compte_voisin_vivants == &compte_voisins_vivants_non_cyclique){
						printf("                 \rMode:Cyclique");
          				compte_voisin_vivants=&compte_voisins_vivants_cyclique;
          				break;
				}
			}
			case 'v' :
			{//touche 'v' pour changer le mode: faire viellir des cellules
				change_age=!change_age;
				if(change_age==0)
					for(int i=0;i<g->nbl;i++)
						for(int j=0;j<g->nbc;j++)
							if (est_vivante(i,j,*g))
								g->age[i][j]=0;
				break;
			}
			case 'n':
			{//touche 'n' pour charger un autre fichier dynamiquement
				*truc=c;
				break;
			}
			default :
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		if (c=='n')
			break;
		c = getchar();
	}
}
/**
 *\brief jeu lance toutes les fonction (avec la possibilite relancement pour nouveau grille)
 *\param file fichier à ouvrir
 *\param g grille
 *\param gc grille
 */
void jeu (char *file, grille g, grille gc){
        char *truc=malloc(sizeof(char));
        char *filename=malloc(sizeof(char));
        do{
                *truc='\n';
                init_grille_from_file(file,&g);
                alloue_grille (g.nbl, g.nbc, &gc);
                affiche_grille(g);
                debut_jeu(&g, &gc,truc);
                libere_grille(&g);
                libere_grille(&gc);
                if (*truc=='n'){
                        FILE*pfile=NULL;
                        do{
                                printf("Veuillez saisir un nom de fichier\n");
                                scanf("%s",file);
                                pfile=fopen(file,"r");
                        }while(pfile==NULL && *file!='q');
			if (*file == 'q')
				break;
                }
        }while (*truc == 'n');
}

