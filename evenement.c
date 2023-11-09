#include "headers/evenement.h"
#include "headers/types.h"
#include <MLV/MLV_all.h>

/* fonction générale pour obtenir et gérer tous les évènements clavier */
void gerer_evenements_clavier(game* game) {
    int n, i;
    n = game -> n_joueurs;

    for (i=0; i < n; i++) {
      obtenir_deplacement_joueur(&(game -> joueurs[i]), i+1);
    }
}

/* Change dir de joueur en un vecteur orthonormé */
void obtenir_deplacement_joueur(joueur* joueur, int numJoueur) {
    if (numJoueur == 1){
        if (MLV_get_keyboard_state(J1_UP) == MLV_PRESSED)
            joueur -> dir.y = 1;
        else
            joueur -> dir.y = -(MLV_get_keyboard_state(J1_DOWN) == MLV_PRESSED);
	
        if (MLV_get_keyboard_state(J1_RIGHT) == MLV_PRESSED)
            joueur -> dir.x = 1;
        else
            joueur -> dir.x = -(MLV_get_keyboard_state(J1_LEFT) == MLV_PRESSED);
        
        
    }
    else {  /* joueur 2 */
        if (MLV_get_keyboard_state(J2_UP) == MLV_PRESSED)
            joueur -> dir.y = 1;
        else
            joueur -> dir.y = -(MLV_get_keyboard_state(J2_DOWN) == MLV_PRESSED);
	
        if (MLV_get_keyboard_state(J2_RIGHT) == MLV_PRESSED)
            joueur -> dir.y = 1;
        else
            joueur -> dir.y = -(MLV_get_keyboard_state(J2_LEFT) == MLV_PRESSED);
    }

    /* appliquer la vitesse */
    joueur -> dir.x *= joueur -> vitesse;
    joueur -> dir.y *= joueur -> vitesse;
}
