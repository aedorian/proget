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
  joueur joueur1, joueur2;
  struct timespec t_debut, t_fin;
  long t_diff;
  long tpf;                  /* temps que doit prendre chaque frame en fonction des fps*/
  int quitter = 0;            /* quitter la boucle principale */

  vect TEST_VECT[4];

  tpf = (1.0 * NANO_S) / FPS;

  printf("Début exec %ld\n", tpf);


  
  /* création des joueurs */

  creer_fenetre();

  game = new_game();

  joueur1 = new_joueur(new_vect(200, 300), new_vect(0, 0), 5,
			   game.armes_obj[0], "img/vache.png");
  joueur2 = new_joueur(new_vect(200, 300), new_vect(0, 0), 5,
			   game.armes_obj[0], "img/vache.png");

  creer_joueur(&joueur1, &game);
  creer_joueur(&joueur2, &game);

  /* creer_ennemi(&game.ennemis_obj[0], &game, new_vect(320, 10)); */
  creer_ennemi(&game.ennemis_obj[2], &game, new_vect(320, 100));
  /* creer_ennemi(&game.ennemis_obj[3], &game, new_vect(120, 0));
  creer_ennemi(&game.ennemis_obj[3], &game, new_vect(640 - 120, 0)); */



  TEST_VECT[0] = new_vect(10, 10);
  TEST_VECT[1] = new_vect(0, 0);
  TEST_VECT[2] = new_vect(11, 11);

  printf("%d\n",
	 collision_rectangles(&TEST_VECT[0], &TEST_VECT[1], &TEST_VECT[0], &TEST_VECT[2]));


  /* boucle principale */
  while (!quitter) {
    switch (game.etat_ecran) {
    case 3:
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



    case 0:
      faire_evenements_menu(&game);
    }
    
  }
  

  

  printf("Fin exec\n");
  exit(EXIT_SUCCESS);
}
