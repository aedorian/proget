#include "headers/mouvement.h"
#include "headers/types.h"
#include "headers/affichage.h"


void move_pos(vect* pos, vect* dir, vect* hitbox) {
  pos -> x += dir -> x;
  if (pos -> x < 0 || pos -> x > ECRAN_W - hitbox -> x) { /* si ça dépasse */
    pos -> x -= dir -> x;
  }
  pos -> y -= dir -> y; /* axe y inversé */
  if (pos -> y < 0 || pos -> y > ECRAN_H - hitbox -> y) {
    pos -> y += dir -> y;
  }
}

/* effectue le déplacement de toutes les balles dans le tableau
   du game actuel */
void move_balles(game* game) {
  int n, i;
  n = game -> n_balles;    /* nombre de balles, pour éviter d'y accéder à
			      chaque tour de boucle */
  for (i=0; i < n; i++) {
    move_pos(&(game -> balles[i].pos), &(game -> balles[i].dir), &(game -> joueurs[i].hitbox));
  }
}

void move_joueurs(game* game) {
  int i, n;
  n = game -> n_joueurs;

  for (i=0; i < n; i++) {

    move_pos(&(game -> joueurs[i].pos), &(game -> joueurs[i].dir), &(game -> joueurs[i].hitbox));
  }
}

/* obtenir une direction (vect) en fonction d'un char la représentant et d'une vitesse v */
vect dir_from_char_vit(char c, int vit) { /* vitesse v */
  vect v;
  switch (c) {
  case 'R': v.x = 1 * vit;     v.y = 0; break;
  case 'L': v.x = -1 * vit;    v.y = 0; break;
  case 'U': v.x = 0;           v.y = 1 * vit; break;
  case 'D': v.x = 0;           v.y = -1 * vit; break;
  default: v.x = 1 * vit;      v.y = 0; break; /* par défaut à droite mais normalement pas nécessaire */
  }
  return v;
}

void move_ennemis(game* game) {
  int i, n;
  ennemi *e; /* ennemi courant dans la boucle */
  n = game -> n_ennemis;

  for (i=0; i < n; i++) {
    e = &(game -> ennemis[i]);
    
    /* pour chaque ennemi, regarder si le compteur mouv_count est égal à la durée du mouvement
       actuel. si oui, alors changer la direction */

    /* si l'ennemi a parcouru (durée de son mouvement actuel) frames */
    if (e -> mouv_count >= (e -> mouvements[e -> i_mouv_act].duree)) {
      e -> mouv_count = 0; /* on remet mouv_count à 0 pour le prochain mouvement */
      
      (e -> i_mouv_act)++; /* on change le mouvement actuel */
      (e -> i_mouv_act) %= (e -> n_mouvements); /* on revient à 0 si on a atteint le dernier */
      
      e -> dir = dir_from_char_vit(e -> mouvements[e -> i_mouv_act].movetype, e -> vitesse);
    }

    (e -> mouv_count)++;

    /* dans tous les cas, effectuer le move_pos */
    move_pos(&(game -> ennemis[i].pos), &(game -> ennemis[i].dir), &(game -> ennemis[i].hitbox));
  }
}

void move_entites(game* game) {

  move_balles(game);
  move_joueurs(game);
  move_ennemis(game);
}
