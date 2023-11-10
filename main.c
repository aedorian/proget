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

#define FPS 25                /* frames par seconde */
#define NANO_S 1000000000     /* valeurs à utiliser dans les calculs de temps
				 ici le nombre de nanosecondes en 1 seconde */
#define MILLI_S 1000000       /* nombre de millisecondes en 1 seconde */

int main() {
  game game;
  joueur test_joueur;
  /* struct timespec t_debut, t_fin; UTILISER LONG?
  struct timespec t_diff; */
  long tpf;                  /* temps que doit prendre chaque frame */
  int quitter = 0;            /* quitter la boucle principale */

  tpf = (1.0 * NANO_S) / FPS;

  printf("Début exec %ld\n", tpf);


  
  /* création des joueurs */

  game = new_game();

  test_joueur = new_joueur(new_vect(200, 300), new_vect(0, 0), 5,
      game.armes_obj[1]);

  creer_joueur(&test_joueur, &game);

  creer_fenetre();
  


  /* boucle principale */
  while (!quitter) {
    /* clock_gettime(CLOCK_REALTIME, &t_debut); GERER SI -1 */
    /**/

    /* AFFICHAGE IMAGE COURANTE */
    afficher_et_actualiser(&game);

    /* RECUPERATION EVENEMENT CLAVIER */
    gerer_evenements_clavier(&game);

    /* RESOLUTION EVENEMENTS */

    /* DEPLACEMENT DES OBJETS (en fonction de dir) */
    move_entites(&game);

    /* RESOLUTION DES COLLISIONS */

    /* if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE)) quitter = 1; */
    
    /**/
    /* clock_gettime(CLOCK_REALTIME, &t_fin);

    t_diff = t_fin.tv_nsec - t_debut.tv_nsec;
    printf("temps:\t\t%d\tsoit%fsur\t\t%f\n", t_diff, tpf, tpf/(t_diff*1.0));
    if (t_diff < tpf) {
      MLV_wait_milliseconds(t_diff / MILLI_S); pour l'avoir en millisecondes
    }
    */

    MLV_wait_milliseconds(20);
  }
  

  

  printf("Fin exec\n");
  exit(EXIT_SUCCESS);
}
