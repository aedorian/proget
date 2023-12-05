#ifndef _EVENEMENT_H_
#define _EVENEMENT_H_

#include "types.h"

/* définition de toutes les touches */
#define J1_UP MLV_KEYBOARD_UP
#define J1_DOWN MLV_KEYBOARD_DOWN
#define J1_LEFT MLV_KEYBOARD_LEFT
#define J1_RIGHT MLV_KEYBOARD_RIGHT
#define J1_TIR MLV_KEYBOARD_KP0

#define J2_UP MLV_KEYBOARD_z
#define J2_DOWN MLV_KEYBOARD_s
#define J2_LEFT MLV_KEYBOARD_q
#define J2_RIGHT MLV_KEYBOARD_d
#define J2_TIR MLV_KEYBOARD_SPACE

#define PAUSE MLV_KEYBOARD_ESCAPE

void gerer_evenements_clavier(game* game);
void obtenir_deplacement_joueur(joueur* joueur, int numJoueur);
void obtenir_tir_joueur(game* game, joueur* joueur, int numJoueur);
void update_cadence_arme(arme* arme);
void faire_tirer_ennemis(game* game);
void set_balle_dir(balle* balle, vect dir);
void set_balle_angle_dir(balle* balle, float angle);
void set_balle_vise_dir(balle* balle, ennemi* e, game* game);
void tirer_arme_joueur(game* game, joueur* joueur);
void tirer_arme_ennemi(game* game, ennemi* ennemi);

#endif
