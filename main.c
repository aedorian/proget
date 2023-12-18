#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "headers/types.h"
#include "headers/affichage.h"
#include "headers/collision.h"
#include "headers/gamemanager.h"
#include "headers/evenement.h"
#include "headers/mouvement.h"
#include "headers/creation.h"
#include "headers/menu.h"
#include "headers/manip_fich.h"

#define FPS 45                /* frames par seconde */
#define FPS_FOCUS 25
#define NANO_S 1000000000     /* valeurs à utiliser dans les calculs de temps
				 ici le nombre de nanosecondes en 1 seconde */
#define MILLI_S 1000000       /* nombre de millisecondes en 1 seconde */

int main() {
  game game;
  struct timespec t_debut, t_fin;
  long t_diff;
  long tpf, tpf_normal, tpf_focus;                  /* temps que doit prendre chaque frame en fonction des fps */
  int quitter = 0;            /* quitter la boucle principale */

  /* toutes les images qui vont être utilisées dans le jeu */
  MLV_Image* images_balles[IMAGE_MAX];
  MLV_Image* images_joueurs[IMAGE_MAX];
  MLV_Image* images_ennemis[IMAGE_MAX];

  srand(time(NULL));

  tpf_normal = (1.0 * NANO_S) / FPS;
  tpf_focus = (1.0 * NANO_S) / FPS_FOCUS;
  tpf = tpf_normal;

  creer_fenetre();

  charger_images(images_balles, images_joueurs, images_ennemis);

  new_game(&game);

  /* écran de chargement */
  MLV_draw_text_with_font(210, 290, "Chargement...", game.police_nom_wave, MLV_COLOR_WHITE);
  MLV_actualise_window();
  
  /* chargement de toutes les vagues dans la liste */
  charger_waves_dans_tab(&game, game.waves);
					 

  /* boucle principale */
  while (!quitter) {
    switch (game.etat_ecran) {
    case 3: /* JEU PRINCIPAL */
      clock_gettime(CLOCK_REALTIME, &t_debut);

      /* AFFICHAGE IMAGE COURANTE */
      afficher_et_actualiser(&game, images_balles, images_joueurs, images_ennemis);

      /* FOCUS MODE: plus lent pour éviter les balles */
      if (MLV_get_keyboard_state(MLV_KEYBOARD_RCTRL) == MLV_PRESSED)
	tpf = tpf_focus;
      else
	tpf = tpf_normal;

      /* RECUPERATION EVENEMENT CLAVIER */
      gerer_evenements_clavier(&game); /* déplacements et tirs */
      faire_tirer_ennemis(&game);
      gerer_waves(&game, game.waves); /* avancement des vagues */

      /* RESOLUTION EVENEMENTS */

      /* DEPLACEMENT DES OBJETS (en fonction de dir) */
      move_entites(&game);
      /* RESOLUTION DES COLLISIONS */
      resolution_collisions(&game);
      
      clock_gettime(CLOCK_REALTIME, &t_fin);

      t_diff = t_fin.tv_nsec - t_debut.tv_nsec; /* temps qu'a prit une frame */
      if (t_diff < tpf && t_diff > 0) {
	MLV_wait_milliseconds((tpf - t_diff) / MILLI_S); /* conversion pour l'avoir en millisecondes */
      }
      
      break;

      
    case 0: /* ECRAN TITRE */
    case 1: /* MENU SAVE */
      faire_evenements_menu(&game); /* même fonction à appeler pour les deux */
      break;

    case 2: /* MENU PAUSE */
      afficher_et_actualiser(&game, images_balles, images_joueurs, images_ennemis);
      faire_evenements_menu(&game);
      break;

    case 4: /* HIGH SCORES */
      afficher_attendre_high_scores(&game);
      break;
    }
    
  }
  
  exit(EXIT_SUCCESS);
}
