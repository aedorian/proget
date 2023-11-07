#include "headers/mouvement.h"
#include "headers/types.h"
#include "headers/affichage.h"


void move_pos(vect* pos, vect* dir) {
  pos -> x += dir -> x;
  if (pos -> x < 0 || pos -> x > ECRAN_W) { /* si ça dépasse */
    pos -> x -= dir -> x;
  }
  pos -> y += dir -> y;
  if (pos -> y < 0 || pos -> y > ECRAN_H) {
    pos -> y -= dir -> y;
  }
}

/* effectue le déplacement de toutes les balles dans le tableau
   du game actuel */
void move_balles(game* game) {
  int n, i;
  n = game -> n_balles;    /* nombre de balles, pour éviter d'y accéder à
			      chaque tour de boucle */
  for (i=0; i < n; i++) {
    move_pos(&(game -> balles[i] -> pos), &(game -> balles[i] -> dir));
  }
}

void move_joueurs(game* game) {
  int i, n;
  n = game -> n_joueurs;

  for (i=0; i < n; i++) {
    printf("mouvement du J%d\n", i+1);

    move_pos(&(game -> joueurs[i] -> pos), &(game -> joueurs[i] -> dir));
  }
}

void move_entites(game* game) {
  printf("MOUVEMENT GENERAL\n");

  move_balles(game);
  move_joueurs(game);
}
