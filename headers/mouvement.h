#ifndef _MOUVEMENT_H_
#define _MOUVEMENT_H_

#include "types.h"

void move_pos_joueur(vect* pos, vect* dir, vect* hitbox);
void move_pos_balle(vect* pos, vect* dir, vect* hitbox, balle* balle, game *game);
void move_pos_ennemi(vect* pos, vect* dir, vect* hitbox, ennemi* ennemi, game *game);

void move_balles(game* game);

void move_joueurs(game* game);

vect dir_from_char_vit(char c, int vit);

void move_ennemis(game * game);

void move_entites(game* game);

#endif
