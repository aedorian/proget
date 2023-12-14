#include "headers/menu.h"
#include "headers/types.h"
#include "headers/evenement.h"
#include "headers/affichage.h"
#include "headers/gamemanager.h"
#include "headers/manip_fich.h"
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
  default:
    menu_act = &(game -> menu_titre); /* par défaut */
    printf("Erreur: mauvais etat_ecran\n");
    break;
  }

  /* obtenir les déplacements avec les flèches dans le menu actuel du game */
  
  /* afficher le menu */
  afficher_menu_actuel(menu_act);

  attendre_clavier_menu(game, menu_act);
}

void attendre_clavier_menu(game* game, menu* menu) {
  MLV_Keyboard_button touche_pressee;
  int opt_act;
  
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
    case 0: /* ECRAN TITRE */
      switch (menu -> opt_act) {
      case 0: init_partie(game, 1); break; /* aller au jeu */
      case 1: init_partie(game, 2); break; /* aller au jeu à deux joueurs */
      case 2:
	game -> etat_ecran_precedent = 0; /* on était à l'écran titre */
	game -> etat_ecran = 1;
	break;
      case 3: game -> etat_ecran = 4; break;
      case 4: exit(EXIT_SUCCESS); break;
      }
      break;
    case 1: /* ECRAN SAVE */
      switch (menu -> opt_act) {
      case 0:
      case 1:
      case 2:
	if (game -> etat_ecran_precedent == 0) {
	  /* sauvegarder l'opt_act précédent car il est overwrite avec init_partie */
	  opt_act = menu -> opt_act;
	  /* si on était à l'écran titre, charger une partie */
	  init_partie(game, 1); /* initialiser une partie qui va être remplacée */
	  charger_sauvegarde(game, opt_act + 1);
	  game -> etat_ecran_precedent = 3; /* pour que l'on revienne au jeu après la pause */
	  game -> etat_ecran = 2; /* met le jeu en pause */

	  /* recharger les polices et les images, sinon segfault */
	  game -> img_fonds[0] = MLV_load_image("img/back1.png");
	  game -> img_fonds[1] = MLV_load_image("img/fond_foret.png");
	  game -> police_nom_wave = MLV_load_font("font/pixelated.ttf", 40);
	  game -> police_score = MLV_load_font("font/pixelated.ttf", 16);
	}
	else {
	  /* sinon, on était en pause */
	  opt_act = menu -> opt_act;
	  /* init_partie(game, 1); */
	  ecrire_sauvegarde(game, menu -> opt_act + 1);
	  game -> etat_ecran = 2;
	}
	break;
      case 3:
	/* revient soit au menu de pause, soit à l'écran titre */
	game -> etat_ecran = game -> etat_ecran_precedent;
	break;
      }
      break;
    case 2: /* ECRAN PAUSE */
      switch (menu -> opt_act) {
      case 0:
	reprendre_temps_game(game); /* on reprend le temps de la partie */
	game -> etat_ecran = 3;
	break; /* on revient au jeu */
      case 1:
	game -> etat_ecran_precedent = 2;
	game -> etat_ecran = 1; /* bascule sur l'écran de save */
	break;
      case 2: game -> etat_ecran = 0; break; /* on revient à l'écran titre */
      }
      break;
    default:
      printf("Erreur: mauvais etat_ecran. Ceci n'est pas censé arriver\n");
      break;
    }
  }
}

void afficher_menu_actuel(menu* menu) {
  int i;
  int wave_nb, second, nb_joueurs; /* infos sur la save */
  char info_wave[] = "wave 00"; /* à afficher */
  char info_duree[20];
  MLV_Font* police_1 = MLV_load_font("font/pixelated.ttf", 24);
  MLV_Image* curseur = MLV_load_image("img/curseur.png");
  MLV_Image* ecran_titre;

  /* afficher le fond seulement si l'on est pas en pause
     (on affiche le jeu si on est en pause) */
  if (menu -> type_menu != 2) {
    MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(21, 41, 26, 255));
  }

  for (i=0; i < (menu -> nb_opt); i++) {
    switch (menu -> type_menu) {
    case 0: /* écran titre */
      ecran_titre = MLV_load_image("img/ecrantitre.png");
      MLV_draw_image(ecran_titre, 0, 70);
      
      switch (i) {
      case 0: MLV_draw_text_with_font(50, 40 + 60 * i, "Nouvelle partie (1 joueur)", police_1, MLV_COLOR_WHITE);
	break;
      case 1: MLV_draw_text_with_font(50, 40 + 60 * i, "Nouvelle partie (2 joueurs)", police_1, MLV_COLOR_WHITE); break;
      case 2: MLV_draw_text_with_font(50, 40 + 60 * i, "Charger partie...", police_1, MLV_COLOR_WHITE); break;
      case 3: MLV_draw_text_with_font(50, 40 + 60 * i, "High scores", police_1, MLV_COLOR_WHITE); break;
      case 4: MLV_draw_text_with_font(50, 40 + 60 * i, "Quitter", police_1, MLV_COLOR_WHITE);
	/* MLV_draw_text_with_font(50, 520, "Projet L2 Info", police_1, MLV_COLOR_WHITE);
	MLV_draw_text_with_font(50, 550, "Tom YUNGMANN", police_1, MLV_COLOR_WHITE);
	MLV_draw_text_with_font(50, 580, "Adrian AUBE", police_1, MLV_COLOR_WHITE); */
	break;
      }
      break;

      
    case 1: /* écran save */
      switch (i) {
      case 0:
        MLV_draw_text_with_font(50, 40 + 60 * i, "Partie 1", police_1, MLV_COLOR_WHITE);
	/* obtenir les infos de la wave sauvegardée */
	obtenir_info_save(1, &wave_nb, &second, &nb_joueurs);
        info_wave[5] = '0' + (wave_nb + 1) / 10;
	info_wave[6] = '0' + (wave_nb + 1) % 10;
	sprintf(info_duree, "%d : %02d", second/60, second%60);
	MLV_draw_text_with_font(200, 40 + 60 * i, info_wave, police_1, MLV_COLOR_WHITE);
	MLV_draw_text_with_font(340, 40 + 60 * i, info_duree, police_1, MLV_COLOR_WHITE);
	if (nb_joueurs == 1) {
	  MLV_draw_text_with_font(450, 40 + 60 * i, "1 joueur", police_1, MLV_COLOR_WHITE);
	} else {
	  MLV_draw_text_with_font(450, 40 + 60 * i, "2 joueurs", police_1, MLV_COLOR_WHITE);
	}
	break;
      case 1: MLV_draw_text_with_font(50, 40 + 60 * i, "Partie 2", police_1, MLV_COLOR_WHITE);
	/* obtenir les infos de la wave sauvegardée */
	obtenir_info_save(2, &wave_nb, &second, &nb_joueurs);
        info_wave[5] = '0' + (wave_nb + 1) / 10;
	info_wave[6] = '0' + (wave_nb + 1) % 10;
	sprintf(info_duree, "%d : %02d", second/60, second%60);
	MLV_draw_text_with_font(200, 40 + 60 * i, info_wave, police_1, MLV_COLOR_WHITE);
	MLV_draw_text_with_font(340, 40 + 60 * i, info_duree, police_1, MLV_COLOR_WHITE);
	if (nb_joueurs == 1) {
	  MLV_draw_text_with_font(450, 40 + 60 * i, "1 joueur", police_1, MLV_COLOR_WHITE);
	} else {
	  MLV_draw_text_with_font(450, 40 + 60 * i, "2 joueurs", police_1, MLV_COLOR_WHITE);
	}
	break;
      case 2: MLV_draw_text_with_font(50, 40 + 60 * i, "Partie 3", police_1, MLV_COLOR_WHITE);
	/* obtenir les infos de la wave sauvegardée */
	obtenir_info_save(3, &wave_nb, &second, &nb_joueurs);
        info_wave[5] = '0' + (wave_nb + 1) / 10;
	info_wave[6] = '0' + (wave_nb + 1) % 10;
	sprintf(info_duree, "%d : %02d", second/60, second%60);
	MLV_draw_text_with_font(200, 40 + 60 * i, info_wave, police_1, MLV_COLOR_WHITE);
	MLV_draw_text_with_font(340, 40 + 60 * i, info_duree, police_1, MLV_COLOR_WHITE);
	if (nb_joueurs == 1) {
	  MLV_draw_text_with_font(450, 40 + 60 * i, "1 joueur", police_1, MLV_COLOR_WHITE);
	} else {
	  MLV_draw_text_with_font(450, 40 + 60 * i, "2 joueurs", police_1, MLV_COLOR_WHITE);
	}
	break;
      case 3: MLV_draw_text_with_font(50, 40 + 60 * i, "... Revenir", police_1, MLV_COLOR_WHITE); break;
        /* REVENIR doit avoir la possibilité de revenir soit à l'écran titre, soit à l'écran de pause (dans le main?
           recevoir les fonctions des menus dans la boucle while (!quitter) pour les gérer et changer de game.etat_ecran? */
      }
      break;

      
  case 2: /* écran pause */
      switch (i) {
      case 0: MLV_draw_text_with_font(50, 40 + 60 * i, "Reprendre", police_1, MLV_COLOR_WHITE); break;
      case 1: MLV_draw_text_with_font(50, 40 + 60 * i, "Sauvegarder partie", police_1, MLV_COLOR_WHITE); break;
      case 2: MLV_draw_text_with_font(50, 40 + 60 * i, "... Revenir au menu", police_1, MLV_COLOR_WHITE); break;
      }
      break;
    }
  }

  MLV_draw_image(curseur, 25, 46 + 60 * (menu -> opt_act));

  MLV_actualise_window();
}

void afficher_highscore(MLV_Font* p_small, MLV_Font* p_large){
    highscore t[MAX_HIGHSCORE];
    int n, i;
    char rang[9], score[11], time[20];
   
    /* affichage titre */
    MLV_draw_text_with_font(260, 20, "Records", p_large, MLV_COLOR_WHITE);
   
    /* affichage du tableau de record */
    MLV_draw_text_with_font(80, 80, "Rang", p_large, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(280, 80, "Score", p_large, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(480, 80, "Temps", p_large, MLV_COLOR_WHITE);

    n = charger_highscore(t);

    for (i = 0; i < n; i++){
        sprintf(rang, "%d", i+1);
        MLV_draw_text_with_font(100, 150 + i * 42, rang, p_small, MLV_COLOR_WHITE);

        sprintf(score, "%d", t[i].score);
        MLV_draw_text_with_font(290, 150 + i * 42, score, p_small, MLV_COLOR_WHITE);

        sprintf(time, "%d : %02d", t[i].second/60, t[i].second%60);
        MLV_draw_text_with_font(490, 150 + i * 42, time, p_small, MLV_COLOR_WHITE);
    }
}

void afficher_attendre_high_scores(game *game) {
  MLV_Font* police_1 = MLV_load_font("font/pixelated.ttf", 24);
  MLV_Font* police_2 = MLV_load_font("font/pixelated.ttf", 34);
  MLV_Keyboard_button touche; /* touche pressée */

  MLV_draw_filled_rectangle(0, 0, ECRAN_W, ECRAN_H, MLV_rgba(21, 41, 26, 255));

  afficher_highscore(police_1, police_2);

  MLV_draw_text_with_font(150, 580, "Appuyer sur <echap> pour quitter...", police_1, MLV_COLOR_WHITE);

  MLV_actualise_window();

  /* affichage terminé, on attend une touche du clavier */
  while (touche != MLV_KEYBOARD_ESCAPE) {
    MLV_wait_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  }
  printf("retour\n");
  /* MLV_wait_keyboard(NULL, NULL, NULL); */
  game -> etat_ecran = 0;
}
