#ifndef _CREATION_H_
#define _CREATION_H_

#include "types.h"

#define J_HITBOX_W 30 /* taille en pixels de la largeur de la hitbox du joueur */
#define J_HITBOX_H 42 /* et de la hauteur */
#define J_VIE_INIT 100 /* vie de départ */

void creer_tous_objets(game* game);
game new_game();
joueur new_joueur(vect pos_init, vect dir_init, int vitesse, arme arme, char* img_path);
balle new_balle(vect hitbox, int damage, float vitesse, int estJoueur, char* img_path);
arme new_arme(balle balle, type_tir type_tir, int cadence);
ennemi new_ennemi(vect hitbox, int vitesse, int vie, arme arme, char* mouvements, char* img_path);
vect new_vect(int x, int y);

#endif
