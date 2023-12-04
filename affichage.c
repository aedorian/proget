#include "headers/types.h"
#include "headers/affichage.h"
#include "headers/creation.h"
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

/* afficher un fond particulier en fonction de la wave actuelle */
void afficher_fond(game* game) {
  if (game -> wave_act < 4) { /* PLAINES */
    MLV_draw_image(game -> img_fonds[0], 0, 0);
    MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(29, 122, 55, 255));
  } else
    if (game -> wave_act < 8) { /* FORET E0571E */
      MLV_draw_image(game -> img_fonds[1], 0, 0);
      MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(79, 50, 13, 255));
    } else
      if (game -> wave_act < 12) { /* CAVE */
	MLV_draw_image(game -> img_fonds[1], 0, 0);
	MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(65, 61, 69, 255));
      }
      else
      if (game -> wave_act < 16) { /* ILE DESERTE */
	MLV_draw_image(game -> img_fonds[1], 0, 0);
	MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(201, 149, 52, 255));
      }
  else
      if (game -> wave_act < 20) { /* VOLCAN */
	MLV_draw_image(game -> img_fonds[1], 0, 0);
	MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(166, 51, 33, 255));
      }
  else
      if (game -> wave_act < 24) { /* ESPACE */
	MLV_draw_image(game -> img_fonds[1], 0, 0);
	MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(129, 84, 171, 255));
      }
  
}

/* afficher l'interface utilisateur: scores, vie... */
void afficher_ui(game* game) {
  int ratio_j1;
  int ratio_j2;
  char nom_wave[8] = "Wave 01";
  
  ratio_j1 = (game -> joueurs[0].vie) / (J_VIE_INIT * 1.0) * 10;

  /* afficher le fond */
  MLV_draw_filled_rectangle(0, 630, ECRAN_W, ECRAN_H, MLV_COLOR_BLACK);
  
  /* afficher la vie du joueur 1*/
  MLV_draw_filled_rectangle(0, 630, J_VIE_INIT * 10, 10, MLV_rgba(108, 5, 3, 255));
  MLV_draw_filled_rectangle(0, 630, ratio_j1 * 20, 10, MLV_rgba(223, 34, 59, 255));

  if (game -> n_joueurs > 1) {
    ratio_j2 = (game -> joueurs[1].vie) / (J_VIE_INIT * 1.0) * 10;

    /* afficher la vie du joueur 2*/
    MLV_draw_filled_rectangle(ECRAN_W - J_VIE_INIT * 10, 630, ECRAN_W, 10, MLV_rgba(108, 5, 3, 255));
    MLV_draw_filled_rectangle(ECRAN_W - ratio_j2 * 20, 630,
			      ECRAN_W, 10, MLV_rgba(223, 34, 59, 255));
  }

  /* afficher le numéro de la wave si il doit être affiché */
  if (game -> wc < 0) {
    nom_wave[5] = '0' + (game -> wave_act + 1) / 10;
    nom_wave[6] = '0' + (game -> wave_act + 1) % 10;
    MLV_draw_text_with_font(260, 290, nom_wave, game -> police_nom_wave, MLV_COLOR_WHITE);
  }

  /* afficher le score */
  MLV_draw_text_with_font(300, 626, "12345678", game -> police_score, MLV_COLOR_WHITE);
}

void afficher_et_actualiser(game* game) {

  /* affichage du fond 94,120,140 */
  afficher_fond(game);
  /* afficher_fond(game); */

  /* afficher les entités */
  afficher_balles(game);
  afficher_joueurs(game);
  afficher_ennemis(game);

  /* debug_hitbox(game); */

  afficher_ui(game);

  MLV_actualise_window();
}
