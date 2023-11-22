#include "headers/creation.h"
#include "headers/types.h"
#include "headers/gamemanager.h"
#include "headers/mouvement.h" /* pour dir_from_char_vit */
#include <MLV/MLV_all.h>

/* crée tous les objets qui vont être utilisables dans le jeu:
   différentes balles, ennemis, les deux joueurs... */
void creer_tous_objets(game* game) {
    /* balles SUPPRIMER OU PAS? */
  ajouter_balle_obj(game, new_balle(new_vect(18, 18), 2, 10, 1, "img/balle1.png")); /* 0 */
    ajouter_balle_obj(game, new_balle(new_vect(12, 12), 2, 10, 1, "img/balle2.png")); /* 1 */
    ajouter_balle_obj(game, new_balle(new_vect(9, 9), 2, 10, 1, "img/balle3.png")); /* 2 */
    ajouter_balle_obj(game, new_balle(new_vect(3, 3), 2, 10, 1, "img/balle4.png")); /* 3 */
    ajouter_balle_obj(game, new_balle(new_vect(9, 18), 2, 10, 1, "img/balle5.png")); /* 4 */
    ajouter_balle_obj(game, new_balle(new_vect(3, 3), 2, 10, 1, "img/balle6.png")); /* 5 */
    /* balles des ennemis (défini par le 0) */
    ajouter_balle_obj(game, new_balle(new_vect(18, 18), 2, 5, 0, "img/balle1.png")); /* 6 */
    ajouter_balle_obj(game, new_balle(new_vect(12, 12), 2, 5, 0, "img/balle2.png")); /* 7 */
    ajouter_balle_obj(game, new_balle(new_vect(9, 9), 2, 5, 0, "img/balle3.png")); /* 8 */

    /* armes, 6 armes */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[4], STRAIGHT, 8)); /* balle joueur */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], CONE, 5));
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], CONE, 5));
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], CONE, 5));
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], CONE, 5));
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], CONE, 5));
    /* armes des ennemis */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[6], STRAIGHT, 30));
    ajouter_arme_obj(game, new_arme(game -> balles_obj[7], BOMB, 20));
    ajouter_arme_obj(game, new_arme(game -> balles_obj[8], SIDES, 30));
    ajouter_arme_obj(game, new_arme(game -> balles_obj[6], THREE, 30));
    ajouter_arme_obj(game, new_arme(game -> balles_obj[6], VISE, 5));
    ajouter_arme_obj(game, new_arme(game -> balles_obj[6], RANDOM, 2));

    /* ennemis de BASE: une arme et un sprite */
    printf("ennemi add...\n");
    ajouter_ennemi_obj(game, /* taureau */
		       new_ennemi(new_vect(33, 33), 3, 10,
				  game -> armes_obj[7], "img/taureau.png"));
    ajouter_ennemi_obj(game, /* cochon */
		       new_ennemi(new_vect(27, 42), 5, 10,
				  game -> armes_obj[6], "img/cochon.png"));
    ajouter_ennemi_obj(game, /* cochon de test qui ne bouge pas, victime boloss */
		       new_ennemi(new_vect(27, 42), 5, 10,
				  game -> armes_obj[6], "img/cochon.png"));
    ajouter_ennemi_obj(game, /* poule */
		       new_ennemi(new_vect(24, 30), 2, 4,
				  game -> armes_obj[8], "img/poule.png"));
    ajouter_ennemi_obj(game, /* mouton 1 */
		       new_ennemi(new_vect(33, 33), 4, 6,
				  game -> armes_obj[6], "img/mouton.png"));
    ajouter_ennemi_obj(game, /* mouton 2 */
		       new_ennemi(new_vect(33, 33), 6, 10,
				  game -> armes_obj[11], "img/mouton.png"));
    /* ENNEMI BOSS QUI TOURNE EN CARRE AU MILIEU ET QUI ENVOIE DU RANDOM */

}

game new_game() {
  game g;
    printf("ok\n");
  /* initialiser le nombre d'élément des listes d'entités */
  g.n_balles = 0;
  g.n_joueurs = 0;
  g.n_ennemis = 0;
  /* obtenir tous les objets possibles */
  g.n_balles_obj = 0;
  g.n_armes_obj = 0;
  g.n_ennemis_obj = 0;

  g.etat_ecran = 0; /* commence sur l'écran titre */
  /* menus - écran titre*/
  g.menu_titre.opt_act = 0;
  g.menu_titre.nb_opt = 5;
  g.menu_titre.type_menu = 0;
  /* écran de save */
  g.menu_save.opt_act = 0;
  g.menu_save.nb_opt = 4;
  g.menu_save.type_menu = 1;
  /* écran de pause */
  g.menu_pause.opt_act = 0;
  g.menu_pause.nb_opt = 2;
  g.menu_pause.type_menu = 2;

  /* waves */
  g.wc = 0;
  g.wave_act = 0;
  g.w_i = 0;

  printf("ok\n");
	
  creer_tous_objets(&g);

  printf("ok\n");
  
  return g;
}

/* créer un struct de type joueur (ne le crée pas dans le jeu) */
joueur new_joueur(vect pos_init, vect dir_init, int vitesse, arme arme, char* img_path) {
  joueur j;
  j.hitbox.x = J_HITBOX_W; j.hitbox.y = J_HITBOX_H;
  j.pos.x = pos_init.x;    j.pos.y = pos_init.y;
  j.dir.x = dir_init.x;    j.dir.y = dir_init.y;
  j.vitesse = vitesse;
  j.vie = J_VIE_INIT;
  j.arme = arme;
  j.image = MLV_load_image(img_path);
  
  return j;
}

balle new_balle(vect hitbox, int damage, float vitesse, int estJoueur, char* img_path) {
    balle b;
    b.hitbox.x = hitbox.x; b.hitbox.y = hitbox.y;
    b.damage = damage;
    b.vitesse = vitesse;
    b.estJoueur = estJoueur;
    b.image = MLV_load_image(img_path);

    b.existe = 1; /* la balle existe au début */

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

ennemi new_ennemi(vect hitbox, int vitesse, int vie, arme arme, char* img_path) {
  ennemi e;
  /* pos d'où le mettre? */
  e.hitbox.x = hitbox.x; e.hitbox.y = hitbox.y;
  e.vitesse = vitesse;
  e.vie = vie;
  e.arme = arme;
  e.image = MLV_load_image(img_path);

  e.existe = 1; /* l'ennemi existe */

  return e;
}

/* crée un nouveau vecteur de 2 éléments,
   surtout utile pour ne pas avoir à initialiser .x et .y manuellement */
vect new_vect(int x, int y) {
    vect c;
    c.x = x;     c.y = y;
    return c;
}
