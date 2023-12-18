#include "headers/types.h"
#include "headers/affichage.h"
#include "headers/creation.h"
#include <MLV/MLV_all.h>
#include <time.h>

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

    int nb_paexiste = 0;
    n = game -> n_joueurs;

    for (i=0; i < n; i++) {
        j = &(game -> joueurs[i]);
	MLV_draw_rectangle(j -> pos.x, j -> pos.y, j -> hitbox.x, j -> hitbox.y, MLV_COLOR_YELLOW);
    }

    
    n = game -> n_ennemis;
    for (i=0; i < n; i++) {
        e = &(game -> ennemis[i]);
        MLV_draw_rectangle(e -> pos.x, e -> pos.y, e -> hitbox.x, e -> hitbox.y, MLV_COLOR_BLUE);
    }

    n = game -> n_balles;
    for (i=0; i < n; i++) {
        b = &(game -> balles[i]);
	if (b -> existe == 0) {
	  nb_paexiste++;
	  if (b -> estJoueur) {
	    MLV_draw_filled_rectangle(b -> pos.x, b -> pos.y, b -> hitbox.x, b -> hitbox.y, MLV_COLOR_GREEN);
	  } else {
	    MLV_draw_filled_rectangle(b -> pos.x, b -> pos.y, b -> hitbox.x, b -> hitbox.y, MLV_COLOR_RED);
	  }
	} else {
	  if (b -> estJoueur) {
	    MLV_draw_rectangle(b -> pos.x, b -> pos.y, b -> hitbox.x, b -> hitbox.y, MLV_COLOR_GREEN);
	  } else {
	    MLV_draw_rectangle(b -> pos.x, b -> pos.y, b -> hitbox.x, b -> hitbox.y, MLV_COLOR_RED);
	  }
	}
	
    }

    printf("balles existent pas à la fin d'affichage: %d\n", nb_paexiste);
}

void afficher_joueurs(game* game, MLV_Image* images[]) {
  joueur* j; /* joueur courant dans la boucle */
  int i, n;
  n = game -> n_joueurs;

  for (i=0; i < n; i++) {
    j = &(game -> joueurs[i]);
    if (j -> existe)
      MLV_draw_image(images[j -> image], j -> pos.x, j -> pos.y);
  }
}

void afficher_ennemis(game* game, MLV_Image* images[]) {
  ennemi* e; /* ennemi courant dans la boucle */
  int i, n;
  n = game -> n_ennemis;

  for (i=0; i < n; i++) {
    e = &(game -> ennemis[i]);

    if (e -> existe == 1) {
      MLV_draw_image(images[e -> image], e -> pos.x, e -> pos.y);
    }
  }
}

void afficher_balles(game* game, MLV_Image* images[]) {
  balle* b; /* balle courante dans la boucle */
  int i, n;
  n = game -> n_balles;

  for (i=0; i < n; i++) {
    b = &(game -> balles[i]);

    if (b -> existe == 1) {
      MLV_draw_image(images[b -> image], b -> pos.x, b -> pos.y);
    }
  }
}

/* afficher un fond particulier en fonction de la wave actuelle */
void afficher_fond(game* game) {
  struct timespec t_debut;
  clock_gettime(CLOCK_REALTIME, &t_debut);

  /* MLV_draw_image(game -> img_fonds[(game -> wave_act) / 4], 0, 0); */
  
  if (game -> wave_act < 4) { /* PLAINES */
    MLV_draw_image(game -> img_fonds[0], 0, 0);
    MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(29, 112, 55, 180));
  } else
    if (game -> wave_act < 8) { /* FORET E0571E */
      MLV_draw_image(game -> img_fonds[1], 0, 0);
      MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(69, 40, 13, 180));
    } else
      if (game -> wave_act < 12) { /* CAVE */
	MLV_draw_image(game -> img_fonds[2], 0, 0);
	MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(55, 51, 59, 180));
      }
      else
      if (game -> wave_act < 16) { /* ILE DESERTE */
	MLV_draw_image(game -> img_fonds[3], 0, 0);
	MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(181, 129, 32, 180));
      }
  else
      if (game -> wave_act < 19) { /* VOLCAN */
	MLV_draw_image(game -> img_fonds[4], 0, 0);
	MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(110, 21, 13, 180));
      }
  else

    if (game -> wave_act < 21) { /* ESPACE */
	MLV_draw_image(game -> img_fonds[5], 0, 0);
	MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(79, 34, 121, 180));
      }
  
}

/* afficher l'interface utilisateur: scores, vie... */
void afficher_ui(game* game) {
  float ratio_j1;
  float ratio_j2;
  char score_tmp[10]; /* pour afficher le score */

  ratio_j1 = (game -> joueurs[0].vie) / (J_VIE_INIT * 1.0) * 10;

  /* afficher le fond */
  MLV_draw_filled_rectangle(0, 630, ECRAN_W, ECRAN_H, MLV_COLOR_BLACK);
  
  /* afficher la vie du joueur 1*/
  MLV_draw_filled_rectangle(-1, 630, J_VIE_INIT * 9, 10, MLV_rgba(70, 5, 3, 255));
  MLV_draw_filled_rectangle(-1, 630, ratio_j1 * 27, 10, MLV_rgba(223, 34, 59, 255));

  if (game -> n_joueurs > 1) {
    ratio_j2 = (game -> joueurs[1].vie) / (J_VIE_INIT * 1.0) * 10;

    /* afficher la vie du joueur 2*/
    MLV_draw_filled_rectangle(ECRAN_W - J_VIE_INIT * 9, 630, ECRAN_W + 1, 10, MLV_rgba(70, 5, 3, 255));
    MLV_draw_filled_rectangle(ECRAN_W - ratio_j2 * 27, 630,
			      ECRAN_W + 1, 10, MLV_rgba(223, 34, 59, 255));
  }

  /* afficher le score */
  sprintf(score_tmp, "%d", game -> score_act.score);
  MLV_draw_text_with_font(300, 626, score_tmp, game -> police_score, MLV_COLOR_WHITE);
}

void afficher_et_actualiser(game* game, MLV_Image* img_balles[], MLV_Image* img_joueurs[], MLV_Image* img_ennemis[]) {
    char nom_wave[8] = "Wave 01";

  /* affichage du fond 94,120,140 */
  afficher_fond(game);
  /* afficher_fond(game); */

    /* afficher le numéro de la wave si il doit être affiché */
  /* pas dans une fonction pour l'afficher sous le joueur, les balles et les ennemis */
  if (game -> wc < 0) {
    if (game -> n_joueurs == 0) {
      MLV_draw_text_with_font(180, 290, "Game over", game -> police_nom_wave, MLV_COLOR_WHITE);
    }
    else {
      if (game -> wave_act == 20) {
	MLV_draw_text_with_font(260, 290, "You win !", game -> police_nom_wave, MLV_COLOR_WHITE);
      }
      else {
	nom_wave[5] = '0' + (game -> wave_act + 1) / 10;
	nom_wave[6] = '0' + (game -> wave_act + 1) % 10;
	MLV_draw_text_with_font(215, 280, nom_wave, game -> police_nom_wave, MLV_COLOR_WHITE);
      }
    }
  }

  /* afficher les entités */
  afficher_balles(game, img_balles);
  afficher_joueurs(game, img_joueurs);
  afficher_ennemis(game, img_ennemis);

  /* debug_hitbox(game); */

  afficher_ui(game);

  /* si le jeu est en pause, afficher un rectangle transparent 131, 67, 51 */
  if (game -> etat_ecran == 2) {
    MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(114, 47, 55, 180));
  }

  /* FOCUS MODE */
  if (MLV_get_keyboard_state(MLV_KEYBOARD_RCTRL) == MLV_PRESSED)
    MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(0, 0, 20, 30));

  MLV_actualise_window();
}

