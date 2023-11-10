#ifndef _CREATION_H_
#define _CREATION_H_

#include "types.h"

#define J_HITBOX_W 20 /* taille en pixels de la largeur de la hitbox du joueur */
#define J_HITBOX_H 20 /* et de la hauteur */
#define J_VIE_INIT 100 /* vie de départ */

void creer_tous_objets(game* game);
game new_game();
joueur new_joueur(vect pos_init, vect dir_init, int vitesse, arme arme);
balle new_balle(vect hitbox, int damage, float vitesse, int estJoueur, MLV_Image* image);
arme new_arme(balle balle, type_tir type_tir, int cadence);
vect new_vect(int x, int y);

#endif
