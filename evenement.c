#include "headers/evenement.h"
#include "headers/creation.h"
#include "headers/gamemanager.h"
#include "headers/types.h"
#include <MLV/MLV_all.h>

/* fonction générale pour obtenir et gérer tous les évènements clavier */
void gerer_evenements_clavier(game* game) {
    int n, i;
    n = game -> n_joueurs;

    for (i=0; i < n; i++) {
        update_cadence_arme(&(game -> joueurs[i].arme));
      
      obtenir_deplacement_joueur(&(game -> joueurs[i]), i+1);
      obtenir_tir_joueur(game, &(game -> joueurs[i]), i+1);
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

void obtenir_tir_joueur(game* game, joueur* joueur, int numJoueur) {
    /* REMPLACER PAR OU? */
    if (numJoueur == 1) {
        if (MLV_get_keyboard_state(J1_TIR) == MLV_PRESSED) {
            tirer_arme(game, joueur);
        }
    }

    if (numJoueur == 2) {
        if (MLV_get_keyboard_state(J2_TIR) == MLV_PRESSED) {
            tirer_arme(game, joueur);
        }
    }
}

/* faire descendre la cadence de 1 */
void update_cadence_arme(arme* arme) {
    if (arme -> cadence_act != 0) {
        (arme -> cadence_act)--;
    }
}

void set_balle_dir(balle* balle, vect dir) {
    balle -> dir = dir; /* METTRE DES POINTEURS POUR OPTI */
    balle -> dir.x *= balle -> vitesse;
    balle -> dir.y *= balle -> vitesse;
}

void tirer_arme(game* game, joueur* joueur) {
    balle balle_arme = joueur -> arme.balle;

    if (joueur -> arme.cadence_act == 0) {
        joueur -> arme.cadence_act = joueur -> arme.cadence;
        balle_arme.pos.x = joueur -> pos.x;
        balle_arme.pos.y = joueur -> pos.y;
        switch (joueur -> arme.type_tir) {
        case STRAIGHT:
            set_balle_dir(&balle_arme, new_vect(0, 1)); 
            creer_balle(&balle_arme, game);
            break;
        case CONE:
            set_balle_dir(&balle_arme, new_vect(-1, 1)); 
            creer_balle(&balle_arme, game);
            set_balle_dir(&balle_arme, new_vect(1, 1)); 
            creer_balle(&balle_arme, game);
            break;
        }
    }
}