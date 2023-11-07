#include "headers/creation.h"
#include "headers/types.h"
#include <MLV/MLV_all.h>

/* crée tous les objets qui vont être utilisables dans le jeu:
   différentes balles, ennemis, les deux joueurs... */
void creer_tous_objets() {
  
}

game new_game() {
  game g;
  /* initialiser les listes? */
  g.n_balles = 0;
  g.n_joueurs = 0;
  g.n_ennemis = 0;

  return g;
}

/* créer un struct de type joueur (ne le crée pas dans le jeu) */
joueur new_joueur(vect pos_init, vect dir_init) {
  joueur j;
  j.hitbox.x = J_HITBOX_W; j.hitbox.y = J_HITBOX_H;
  j.pos.x = pos_init.x;    j.pos.y = pos_init.y;
  j.dir.x = dir_init.x;    j.dir.y = dir_init.y;
  j.vie = J_VIE_INIT;
  
  return j;
}

/* crée un nouveau vecteur de 2 éléments,
   surtout utile pour ne pas avoir à initialiser .x et .y manuellement */
vect new_vect(int x, int y) {
    vect c;
    c.x = x;     c.y = y;
    return c;
}
