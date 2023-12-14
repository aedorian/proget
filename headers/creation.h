#ifndef _CREATION_H_
#define _CREATION_H_

#include "types.h"

#define J_HITBOX_W 30 /* taille en pixels de la largeur de la hitbox du joueur */
#define J_HITBOX_H 42 /* et de la hauteur */
#define J_VIE_INIT 30 /* vie de départ */

/* macros des images (balles, powerups, joueurs, ennemis) */
#define B_VACHE 0
#define B_PIG 1
#define B_SHEEP 2
#define B_BLAIREAU 3
#define B_GOLDSHEEP 4
#define B_POULE 5
#define B_TAUREAU 6
#define B_ICEPIG 7
#define B_BEAR 8
#define B_COQ 9
#define B_VACHE_PETITE 10
#define B_VACHE_GRANDE 11
#define B_MEDUSE 12

#define PW_COEUR 15
#define PW_ARME 16

#define VACHE_1 0
#define VACHE_2 1

#define TAUREAU 0
#define COCHON 1
#define POULE 2
#define MOUTON 3
#define GOLDSHEEP 4
#define BLAIREAU 5
#define BEAR 6
#define COQ 7
#define ICEPIG 8
#define MEDUSE 9

void charger_images(MLV_Image* img_balles[], MLV_Image* img_joueurs[], MLV_Image* img_ennemis[]);
void creer_tous_objets(game* game);
game new_game();
joueur new_joueur(vect pos_init, vect dir_init, int vitesse, arme arme, int indice_image);
balle new_balle(vect hitbox, int damage, float vitesse, int estJoueur, int indice_image);
arme new_arme(balle balle, type_tir type_tir, int cadence);
ennemi new_ennemi(vect hitbox, int vitesse, int vie, arme arme, int indice_image);
vect new_vect(int x, int y);

#endif
