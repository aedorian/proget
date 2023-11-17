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

#define FPS 40                /* frames par seconde */
#define NANO_S 1000000000     /* valeurs à utiliser dans les calculs de temps
				 ici le nombre de nanosecondes en 1 seconde */
#define MILLI_S 1000000       /* nombre de millisecondes en 1 seconde */

int main() {
  game game;
  struct timespec t_debut, t_fin;
  long t_diff;
  long tpf;                  /* temps que doit prendre chaque frame en fonction des fps*/
  int quitter = 0;            /* quitter la boucle principale */

  int debug_ennemi = 1;

  tpf = (1.0 * NANO_S) / FPS;

  printf("Début exec %ld\n", tpf);


  
  /* création des joueurs */

  creer_fenetre();

  game = new_game();

  switch (debug_ennemi) {
  case 0:
    creer_ennemi(&game.ennemis_obj[4], &game, new_vect(50, 10));
    break;
  case 1:
    creer_ennemi(&game.ennemis_obj[5], &game, new_vect(320, 10));
    break;
  case 2:
    creer_ennemi(&game.ennemis_obj[0], &game, new_vect(320, 10));
    break;
  }
  /* creer_ennemi(&game.ennemis_obj[0], &game, new_vect(320, 10));
  creer_ennemi(&game.ennemis_obj[2], &game, new_vect(320, 100));
  creer_ennemi(&game.ennemis_obj[3], &game, new_vect(120, 0));
  creer_ennemi(&game.ennemis_obj[3], &game, new_vect(640 - 120, 0)); */



  /* boucle principale */
  while (!quitter) {
    switch (game.etat_ecran) {
    case 3: /* JEU PRINCIPAL */
      clock_gettime(CLOCK_REALTIME, &t_debut);
      /**/

      /* AFFICHAGE IMAGE COURANTE */
      afficher_et_actualiser(&game);

      /* RECUPERATION EVENEMENT CLAVIER */
      gerer_evenements_clavier(&game);

      faire_tirer_ennemis(&game);

      /* RESOLUTION EVENEMENTS */

      /* DEPLACEMENT DES OBJETS (en fonction de dir) */
      move_entites(&game);

      /* RESOLUTION DES COLLISIONS */

      resolution_collisions(&game);

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
      /* problème: comment savoir de là où on vient pour savoir si on doit
	 sauvegarder ou charger la partie? faire deux menus save? */
      faire_evenements_menu(&game);
      break;

    case 2: /* MENU PAUSE */
      faire_evenements_menu(&game);
      break;
    }
    
  }
  

  

  printf("Fin exec\n");
  exit(EXIT_SUCCESS);
}
