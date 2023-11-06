#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "headers/types.h"
#include "headers/affichage.h"

#define FPS 25                /* frames par seconde */
#define NANO_S 1000000000     /* valeurs à utiliser dans les calculs de temps
				 ici le nombre de nanosecondes en 1 seconde */
#define MILLI_S 1000000       /* nombre de millisecondes en 1 seconde */

int main() {
  /* struct timespec t_debut, t_fin; UTILISER LONG?
  struct timespec t_diff; */
  long tpf;                  /* temps que doit prendre chaque frame */
  int quitter = 0;            /* quitter la boucle principale */

  tpf = (1.0 * NANO_S) / FPS;

  printf("Début exec %ld\n", tpf);

  creer_fenetre();
  
  /* boucle principale */
  while (!quitter) {
    /* clock_gettime(CLOCK_REALTIME, &t_debut); GERER SI -1 */
    /**/

    printf("%d\n", quitter);

    /* if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE)) quitter = 1; */
    
    /**/
    /* clock_gettime(CLOCK_REALTIME, &t_fin);

    t_diff = t_fin.tv_nsec - t_debut.tv_nsec;
    printf("temps:\t\t%d\tsoit%fsur\t\t%f\n", t_diff, tpf, tpf/(t_diff*1.0));
    if (t_diff < tpf) {
      MLV_wait_milliseconds(t_diff / MILLI_S); pour l'avoir en millisecondes
    }
    */

    MLV_wait_milliseconds(80);
  }
  

  

  printf("Fin exec\n");
  exit(EXIT_SUCCESS);
}
