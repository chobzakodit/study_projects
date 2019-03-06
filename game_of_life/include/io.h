#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

// affichage d'un trait horizontal
void affiche_trait (int c);

// affichage d'une ligne de la grille
void affiche_ligne (grille g, int l);

// affichage d'une grille
void affiche_grille (grille g);

// effacement d'une grille
void efface_grille (grille g);

// debute le jeu
void debut_jeu(grille *g, grille *gc,char *truc);

// fonction principale
void jeu (char *file, grille g, grille gc);

#endif
