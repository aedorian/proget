#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_

#define ECRAN_W 640
#define ECRAN_H 640
#define NOM_WAVE_T -75

void creer_fenetre();
void fermer_fenetre();
void debug_hitbox(game* game);
void afficher_joueurs(game* game, MLV_Image* images[IMAGE_MAX]);
void afficher_ennemis(game* game, MLV_Image* images[IMAGE_MAX]);
void afficher_balles(game* game, MLV_Image* images[IMAGE_MAX]);
void afficher_fond(game* game);
void afficher_ui(game* game);
void afficher_et_actualiser(game* game, MLV_Image* img_balles[IMAGE_MAX], MLV_Image* img_joueurs[IMAGE_MAX], MLV_Image* img_ennemis[IMAGE_MAX]);

#endif
