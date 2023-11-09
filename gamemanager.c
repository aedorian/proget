#include "headers/gamemanager.h"
#include "headers/types.h"
#include <MLV/MLV_all.h>

/* crée vraiment un joueur et le crée dans le game */
void creer_joueur(joueur* joueur, game* game) {
  game -> joueurs[game -> n_joueurs] = *joueur; /* l'ajouter à la fin du tableau */
  (game -> n_joueurs)++; /* il y a un joueur de plus */
}
