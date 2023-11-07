#ifndef _MOUVEMENT_H_
#define _MOUVEMENT_H_

#include "types.h"

void move_pos(vect* pos, vect* dir);

void move_balles(game* game);

void move_joueurs(game* game);

void move_entites(game* game);

#endif
