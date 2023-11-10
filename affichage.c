#include "headers/types.h"
#include "headers/affichage.h"
#include <MLV/MLV_all.h>

void creer_fenetre() {
  MLV_create_window("proget", "keyboard events", ECRAN_W, ECRAN_H);
}

void fermer_fenetre() {
  MLV_free_window();
}

/* afficher les hitbox */
void debug_hitbox(game* game) {
    joueur* j; /* joueur courant dans la boucle */
    balle* b;
    int i, n;
    n = game -> n_joueurs;

    for (i=0; i < n; i++) {
        j = &(game -> joueurs[i]);

        /* affichage d'un joueur */
        MLV_draw_rectangle(j -> pos.x, j -> pos.y, j -> hitbox.x, j -> hitbox.y, MLV_COLOR_GREEN);
        /* fin affichage */
    }

    n = game -> n_balles;
    for (i=0; i < n; i++) {
        b = &(game -> balles[i]);

        /* affichage d'un joueur */
        MLV_draw_rectangle(b -> pos.x, b -> pos.y, b -> hitbox.x, b -> hitbox.y, MLV_COLOR_GREEN);
        /* fin affichage */
    }
}

void afficher_joueurs(game* game) {
  joueur* j; /* joueur courant dans la boucle */
  int i, n;
  n = game -> n_joueurs;

  for (i=0; i < n; i++) {
    j = &(game -> joueurs[i]);

    /* affichage d'un joueur */
    MLV_draw_filled_rectangle(j -> pos.x, j -> pos.y, 20, 20, MLV_COLOR_RED);
    /* fin affichage */
  }
}

void afficher_et_actualiser(game* game) {

  /* affichage du fond */
  MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_COLOR_BLACK);
  
  afficher_joueurs(game);
  /* afficher balles */
  /* afficher ennemis... */
  debug_hitbox(game);

  MLV_actualise_window();
}
