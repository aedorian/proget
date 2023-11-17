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
  attendre_clavier_menu(menu_act);
  /* afficher le menu */
  afficher_menu_actuel(menu_act);
}

void attendre_clavier_menu(menu* menu) {
  MLV_Keyboard_button touche_pressee;
  
  MLV_wait_keyboard(&touche_pressee, NULL, NULL);
    
  if (touche_pressee == J1_UP) { /* monter */
    if (--(menu -> opt_act) < 0)
      menu -> opt_act = menu -> nb_opt - 1;
  }
  if (touche_pressee == J1_DOWN) { /* descendre */
    menu -> opt_act++;
    (menu -> opt_act) %= (menu -> nb_opt);
  }
}

void afficher_menu_actuel(menu* menu) {
  int i;
  MLV_Font* police_1 = MLV_load_font("font/ka1.ttf", 16);
  MLV_Image* curseur = MLV_load_image("img/curseur.png");
  printf("affiche %d %d\n", menu -> type_menu, menu -> nb_opt);

  MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(10, 80, 20,255));
  
  for (i=0; i < (menu -> nb_opt); i++) {
    switch (menu -> type_menu) {
    case 0: /* écran titre */
      printf("menu\n");
      switch (i) {
      case 0: MLV_draw_text_with_font(40, 40 + 60 * i, "Nouvelle partie", police_1, MLV_COLOR_WHITE); break;
      case 1: MLV_draw_text_with_font(40, 40 + 60 * i, "Charger partie", police_1, MLV_COLOR_WHITE); break;
      case 2: MLV_draw_text_with_font(40, 40 + 60 * i, "High scores", police_1, MLV_COLOR_WHITE); break;
      case 3: MLV_draw_text_with_font(40, 40 + 60 * i, "Quitter", police_1, MLV_COLOR_WHITE); break;
      }
    }
    case 1: /* écran save */
      printf("save\n");
      switch (i) {
      case 0: MLV_draw_text_with_font(40, 40 + 60 * i, "Slot 1", police_1, MLV_COLOR_WHITE); break;
      case 1: MLV_draw_text_with_font(40, 40 + 60 * i, "Slot 2", police_1, MLV_COLOR_WHITE); break;
      case 2: MLV_draw_text_with_font(40, 40 + 60 * i, "Slot 3", police_1, MLV_COLOR_WHITE); break;
      case 3: MLV_draw_text_with_font(40, 40 + 60 * i, "... Revenir", police_1, MLV_COLOR_WHITE); break;
        /* REVENIR doit avoir la possibilité de revenir soit à l'écran titre, soit à l'écran de pause (dans le main?
           recevoir les fonctions des menus dans la boucle while (!quitter) pour les gérer et changer de game.etat_ecran? 
      }
    }
  case 2: /* écran pause */
      printf("pause\n");
      switch (i) {
      case 0: MLV_draw_text_with_font(40, 40 + 60 * i, "Reprendre", police_1, MLV_COLOR_WHITE); break;
      case 1: MLV_draw_text_with_font(40, 40 + 60 * i, "Sauvegarder partie", police_1, MLV_COLOR_WHITE); break;
      case 2: MLV_draw_text_with_font(40, 40 + 60 * i, "High scores", police_1, MLV_COLOR_WHITE); break;
      case 3: MLV_draw_text_with_font(40, 40 + 60 * i, "Quitter", police_1, MLV_COLOR_WHITE); break;
      }
    }
    printf("%d\n", i);
  }

  MLV_draw_image(curseur, 20, 40 + 60 * (menu -> opt_act));

  MLV_actualise_window();
}
