#ifndef _MENU_H_
#define _MENU_H_

#include "menu.h"
#include "types.h"
#include "evenement.h"

void faire_evenements_menu(game* game);
void attendre_clavier_menu(game* game, menu* menu);
void afficher_menu_actuel(menu* menu);

#endif /* _MENU_H_ */
