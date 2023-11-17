#include "headers/menu.h"
#include "headers/types.h"
#include "headers/evenement.h"
#include "headers/affichage.h"
#include <MLV/MLV_all.h>

void faire_evenements_menu(game* game) {
  menu* menu_act;
  /* obtenir menu actuel */
  switch (game -> etat_ecran) {
  case 0:
    menu_act = &(game -> menu_titre);
    break;
  case 1:
    menu_act = &(game -> menu_save);
    break;
  case 2:
    menu_act = &(game -> menu_pause);
    break;
  }

  /* obtenir les déplacements avec les flèches dans le menu actuel du game */
  
  /* afficher le menu */
  afficher_menu_actuel(menu_act);

  attendre_clavier_menu(game, menu_act);
}

void attendre_clavier_menu(game* game, menu* menu) {
  MLV_Keyboard_button touche_pressee;
  
  MLV_wait_keyboard(&touche_pressee, NULL, NULL);

  /* déplacement */
  if (touche_pressee == J1_UP) { /* monter */
    if (--(menu -> opt_act) < 0)
      menu -> opt_act = menu -> nb_opt - 1;
  }
  if (touche_pressee == J1_DOWN) { /* descendre */
    menu -> opt_act++;
    (menu -> opt_act) %= (menu -> nb_opt);
  }

  /* confirmation */
  if (touche_pressee == MLV_KEYBOARD_RETURN) {
    switch (menu -> type_menu) {
    case 0:
      switch (menu -> opt_act) {
      case 0: game -> etat_ecran = 3; break; /* aller au jeu */
      case 1: game -> etat_ecran = 1; break;
      case 2: break;
      case 3: break;
      }
      break;
    case 1:
      switch (menu -> opt_act) {
      case 0: break;
      case 1: break;
      case 2: break;
      case 3: break;
      }
      break;
    case 2:
      switch (menu -> opt_act) {
      case 0: break;
      case 1: break;
      case 2: break;
      case 3: break;
      }
      break;
    }
  }
}

void afficher_menu_actuel(menu* menu) {
  int i;
  MLV_Font* police_1 = MLV_load_font("font/pixelated.ttf", 24);
  MLV_Image* curseur = MLV_load_image("img/curseur.png");
  MLV_Image* ecran_titre;

  MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(3, 40, 5,255));
  
  for (i=0; i < (menu -> nb_opt); i++) {
    switch (menu -> type_menu) {
    case 0: /* écran titre */
      ecran_titre = MLV_load_image("img/ecrantitre.png");
      MLV_draw_image(ecran_titre, 0, 0);
      
      switch (i) {
      case 0: MLV_draw_text_with_font(50, 40 + 60 * i, "Nouvelle partie", police_1, MLV_COLOR_WHITE); break;
      case 1: MLV_draw_text_with_font(50, 40 + 60 * i, "Charger partie", police_1, MLV_COLOR_WHITE); break;
      case 2: MLV_draw_text_with_font(50, 40 + 60 * i, "High scores", police_1, MLV_COLOR_WHITE); break;
      case 3: MLV_draw_text_with_font(50, 40 + 60 * i, "Quitter", police_1, MLV_COLOR_WHITE); break;
      }
      break;

      
    case 1: /* écran save */
      switch (i) {
      case 0: MLV_draw_text_with_font(50, 40 + 60 * i, "Slot 1", police_1, MLV_COLOR_WHITE); break;
      case 1: MLV_draw_text_with_font(50, 40 + 60 * i, "Slot 2", police_1, MLV_COLOR_WHITE); break;
      case 2: MLV_draw_text_with_font(50, 40 + 60 * i, "Slot 3", police_1, MLV_COLOR_WHITE); break;
      case 3: MLV_draw_text_with_font(50, 40 + 60 * i, "... Revenir", police_1, MLV_COLOR_WHITE); break;
        /* REVENIR doit avoir la possibilité de revenir soit à l'écran titre, soit à l'écran de pause (dans le main?
           recevoir les fonctions des menus dans la boucle while (!quitter) pour les gérer et changer de game.etat_ecran? */
      }
      break;

      
  case 2: /* écran pause */
      switch (i) {
      case 0: MLV_draw_text_with_font(50, 40 + 60 * i, "Reprendre", police_1, MLV_COLOR_WHITE); break;
      case 1: MLV_draw_text_with_font(50, 40 + 60 * i, "Sauvegarder partie", police_1, MLV_COLOR_WHITE); break;
      case 2: MLV_draw_text_with_font(50, 40 + 60 * i, "High scores", police_1, MLV_COLOR_WHITE); break;
      case 3: MLV_draw_text_with_font(50, 40 + 60 * i, "Quitter", police_1, MLV_COLOR_WHITE); break;
      }
      break;
    }
  }

  MLV_draw_image(curseur, 25, 46 + 60 * (menu -> opt_act));

  MLV_actualise_window();
}
