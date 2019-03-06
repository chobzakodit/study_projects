/**
 *\file main.c
 *\author Gaydamakha Mikhail
 */
#include <stdio.h>
#include "grille.h"
#include "io.h"
#include "jeu.h"
/**
 *\fn main fonction principale du programme
 *\param argc nombre d'arguments
 *\param argv liste des arguments
 *\return 0 si aucune erreur
 */
int main (int argc, char ** argv) {

        if (argc != 2 )
        {
                printf("usage : main <fichier grille>\n");
                return 1;
        }

        grille g, gc;
        jeu(argv[1],g,gc);
        return 0;
}
