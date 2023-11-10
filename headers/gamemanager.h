#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "types.h"

void creer_joueur(joueur* joueur, game* game);
void creer_balle(balle* balle, game* game);
void ajouter_balle_obj(game* game, balle balle);
void ajouter_arme_obj(game* game, arme arme);

#endif
