#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_

#define ECRAN_W 640
#define ECRAN_H 640

void creer_fenetre();
void fermer_fenetre();
void debug_hitbox(game* game);
void afficher_joueurs(game* game);
void afficher_ennemis(game* game);
void afficher_balles(game* game);
void afficher_et_actualiser(game* game);

#endif
