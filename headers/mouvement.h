#ifndef _MOUVEMENT_H_
#define _MOUVEMENT_H_

#include "types.h"

void move_pos_joueur(vect* pos, vect* dir, vect* hitbox, joueur* joueur);
void move_pos_balle(vect* pos, vect* dir, vect* hitbox, balle* balle);
void move_pos_ennemi(vect* pos, vect* dir, vect* hitbox, ennemi* ennemi);

void move_balles(game* game);

void move_joueurs(game* game);

vect dir_from_char_vit(char c, int vit);

void move_ennemis(game * game);

void move_entites(game* game);

#endif
