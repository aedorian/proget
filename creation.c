#include "headers/creation.h"
#include "headers/types.h"
#include "headers/gamemanager.h"
#include <MLV/MLV_all.h>

/* crée tous les objets qui vont être utilisables dans le jeu:
   différentes balles, ennemis, les deux joueurs... */
void creer_tous_objets(game* game) {
    /* balles SUPPRIMER OU PAS? */
    ajouter_balle_obj(game, new_balle(new_vect(5, 5), 2, 10, 1, NULL));
    ajouter_balle_obj(game, new_balle(new_vect(5, 5), 2, 10, 1, NULL));

    /* armes */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], STRAIGHT, 5));
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], CONE, 5));
}

game new_game() {
  game g;
  /* initialiser les listes? */
  g.n_balles = 0;
  g.n_joueurs = 0;
  g.n_ennemis = 0;
  /* obtenir tous les objets possibles */
  g.n_balles_obj = 0;
  g.n_armes_obj = 0;
  g.n_ennemis_obj = 0;
  creer_tous_objets(&g);
  
  return g;
}

/* créer un struct de type joueur (ne le crée pas dans le jeu) */
joueur new_joueur(vect pos_init, vect dir_init, int vitesse, arme arme) {
  joueur j;
  j.hitbox.x = J_HITBOX_W; j.hitbox.y = J_HITBOX_H;
  j.pos.x = pos_init.x;    j.pos.y = pos_init.y;
  j.dir.x = dir_init.x;    j.dir.y = dir_init.y;
  j.vitesse = vitesse;
  j.vie = J_VIE_INIT;
  j.arme = arme;
  
  return j;
}

balle new_balle(vect hitbox, int damage, float vitesse, int estJoueur, MLV_Image* image) {
    balle b;
    b.hitbox.x = hitbox.x; b.hitbox.y = hitbox.y;
    b.damage = damage;
    b.vitesse = vitesse;
    b.estJoueur = estJoueur;
    /* APPLIQUER L'IMAGE */

    return b;
}

arme new_arme(balle balle, type_tir type_tir, int cadence) {
    arme a;
    a.balle = balle;
    a.type_tir = type_tir;
    a.cadence = cadence;
    a.cadence_act = 0; /* initialiser à 0 pour pouvoir tirer */

    return a;
}

/* crée un nouveau vecteur de 2 éléments,
   surtout utile pour ne pas avoir à initialiser .x et .y manuellement */
vect new_vect(int x, int y) {
    vect c;
    c.x = x;     c.y = y;
    return c;
}
