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
    ennemi* e;
    int i, n;
    n = game -> n_joueurs;

    for (i=0; i < n; i++) {
        j = &(game -> joueurs[i]);
        MLV_draw_rectangle(j -> pos.x, j -> pos.y, j -> hitbox.x, j -> hitbox.y, MLV_COLOR_GREEN);
    }

    n = game -> n_balles;
    for (i=0; i < n; i++) {
        b = &(game -> balles[i]);
        MLV_draw_rectangle(b -> pos.x, b -> pos.y, b -> hitbox.x, b -> hitbox.y, MLV_COLOR_GREEN);
    }

    n = game -> n_ennemis;
    for (i=0; i < n; i++) {
        e = &(game -> ennemis[i]);
        MLV_draw_rectangle(e -> pos.x, e -> pos.y, e -> hitbox.x, e -> hitbox.y, MLV_COLOR_GREEN);
    }
}

void afficher_joueurs(game* game) {
  joueur* j; /* joueur courant dans la boucle */
  int i, n;
  n = game -> n_joueurs;

  for (i=0; i < n; i++) {
    j = &(game -> joueurs[i]);

    MLV_draw_image(j -> image, j -> pos.x, j -> pos.y);
  }
}

void afficher_ennemis(game* game) {
  ennemi* e; /* ennemi courant dans la boucle */
  int i, n;
  n = game -> n_ennemis;

  for (i=0; i < n; i++) {
    e = &(game -> ennemis[i]);

    if (e -> existe == 1) {
      MLV_draw_image(e -> image, e -> pos.x, e -> pos.y);
    }
  }
}

void afficher_balles(game* game) {
  balle* b; /* balle courante dans la boucle */
  int i, n;
  n = game -> n_balles;

  for (i=0; i < n; i++) {
    b = &(game -> balles[i]);

    if (b -> existe == 1) {
      MLV_draw_image(b -> image, b -> pos.x, b -> pos.y);
    }
  }
}

/* afficher l'interface utilisateur: scores, vie... */
void afficher_ui(game* game) {
  MLV_draw_filled_rectangle(0, 615, ECRAN_W, ECRAN_H, MLV_COLOR_BLACK);
}

void afficher_et_actualiser(game* game) {

  /* affichage du fond 94,120,140 */
  MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(29, 122, 55,255));

  afficher_balles(game);
  afficher_joueurs(game);
  afficher_ennemis(game);
  /* afficher ennemis... */

  debug_hitbox(game);

  afficher_ui(game);

  MLV_actualise_window();
}
