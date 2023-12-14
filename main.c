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
#define NANO_S 1000000000     /* valeurs à utiliser dans les calculs de temps
				 ici le nombre de nanosecondes en 1 seconde */
#define MILLI_S 1000000       /* nombre de millisecondes en 1 seconde */

int main() {
  game game;
  struct timespec t_debut, t_fin;
  long t_diff;
  long tpf;                  /* temps que doit prendre chaque frame en fonction des fps */
  int quitter = 0;            /* quitter la boucle principale */

  /* toutes les images qui vont être utilisées dans le jeu */
  MLV_Image* images_balles[IMAGE_MAX];
  MLV_Image* images_joueurs[IMAGE_MAX];
  MLV_Image* images_ennemis[IMAGE_MAX];

  srand(time(NULL));

  tpf = (1.0 * NANO_S) / FPS;

  printf("Début exec %ld\n", tpf);
  
  /* création des joueurs */

  creer_fenetre();

  charger_images(images_balles, images_joueurs, images_ennemis);

  new_game(&game);
  /* game = new_game();
     game.wave_act = 5; */

  /* PROBLEME: QUAND ON MEURT, REFAIRE UN GAME DANS INIT_PARTIE */

  printf("game cree\n");

  /* écran de chargement */
  MLV_draw_text_with_font(210, 290, "Chargement...", game.police_nom_wave, MLV_COLOR_WHITE);
  MLV_actualise_window();
  
  /* chargement de toutes les vagues dans la liste */
  charger_waves_dans_tab(&game, game.waves);

  printf("waves chargées\n");

  /* exit(EXIT_SUCCESS); */


  /* boucle principale */
  while (!quitter) {
    switch (game.etat_ecran) {
    case 3: /* JEU PRINCIPAL */
      /* printf("debut frame----------------------\n"); */
      clock_gettime(CLOCK_REALTIME, &t_debut);
      /**/

      /* AFFICHAGE IMAGE COURANTE */
      afficher_et_actualiser(&game, images_balles, images_joueurs, images_ennemis);

      /* FOCUS MODE */
      if (MLV_get_keyboard_state(MLV_KEYBOARD_RCTRL) == MLV_PRESSED)
	tpf = (1.0 * NANO_S) / 30;
      else
	tpf = (1.0 * NANO_S) / 45;

      /* RECUPERATION EVENEMENT CLAVIER */
      gerer_evenements_clavier(&game); /* déplacements et tirs */

      gerer_waves(&game, game.waves); /* avancement des vagues */

      /*
      for (i=0; i < game.n_ennemis; i++) {
	printf("ennemi %d ", game.ennemis[i].existe);
      }
      printf("\n"); */

      faire_tirer_ennemis(&game);

      /* RESOLUTION EVENEMENTS */

      /* DEPLACEMENT DES OBJETS (en fonction de dir) */
      move_entites(&game);

      /* RESOLUTION DES COLLISIONS */

      resolution_collisions(&game);

      /* gestion de la mort */
      /* if (game.n_joueurs == 0) { */
	/* on ajoute aux secondes */
        /* arreter_temps_game(&game); } */
        /* sauvegarde du score seulement lorsqu'on meurt */
	/* game.wc = NOM_WAVE_T; */
	/* sauvegarde_highscore(game.score_act.score, game.score_act.second);
	   game.etat_ecran = 4; */

      

      /* if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE)) quitter = 1; */
    
      /**/
      clock_gettime(CLOCK_REALTIME, &t_fin);

      t_diff = t_fin.tv_nsec - t_debut.tv_nsec; /* temps qu'a prit une frame */
      /* printf("temps:\t\t %ld \t soit %ld sur \t\t%f\n", t_diff, tpf, (t_diff*1.0)/tpf); */
      if (t_diff < tpf && t_diff > 0) {
	/* printf("%ld\n", (tpf - t_diff) / MILLI_S); */
	MLV_wait_milliseconds((tpf - t_diff) / MILLI_S); /* pour l'avoir en millisecondes */
      }
      break;









      
    case 0: /* ECRAN TITRE */
      faire_evenements_menu(&game);
      break;

    case 1: /* MENU SAVE */
      faire_evenements_menu(&game);
      break;

    case 2: /* MENU PAUSE */
      printf("EST DANS MENU PAUSE\n");
      afficher_et_actualiser(&game, images_balles, images_joueurs, images_ennemis);
      faire_evenements_menu(&game);
      break;

    case 4: /* HIGH SCORES */
      afficher_attendre_high_scores(&game);
      break;
    }
    
  }
  

  

  printf("Fin exec\n");
  exit(EXIT_SUCCESS);
}
