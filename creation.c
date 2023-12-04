#include "headers/creation.h"
#include "headers/types.h"
#include "headers/gamemanager.h"
#include "headers/mouvement.h" /* pour dir_from_char_vit */
#include "headers/affichage.h"
#include <MLV/MLV_all.h>

/* crée tous les objets qui vont être utilisables dans le jeu:
   différentes balles, ennemis, les deux joueurs... */
void creer_tous_objets(game* game) {
    /* balles du joueur */
  ajouter_balle_obj(game, new_balle(new_vect(9, 18), 10, 10, 1, "img/balle_vache.png")); /* 0 : tir jaune normal */
  ajouter_balle_obj(game, new_balle(new_vect(12, 12), 2, 10, 1, "img/balle_vache.png")); /* 1 */
  ajouter_balle_obj(game, new_balle(new_vect(9, 9), 2, 10, 1, "img/balle_vache.png")); /* 2 */
  ajouter_balle_obj(game, new_balle(new_vect(12, 12), 2, 10, 1, "img/balle_vache.png")); /* 3 */
  ajouter_balle_obj(game, new_balle(new_vect(9, 9), 2, 10, 1, "img/balle_vache.png")); /* 4 */
    /* balles des ennemis (défini par le 0) */
    ajouter_balle_obj(game, new_balle(new_vect(15, 24), 2, 5, 0, "img/balle_pig.png")); /* 5 : cochon */
    ajouter_balle_obj(game, new_balle(new_vect(18, 18), 2, 5, 0, "img/balle_sheep.png")); /* 6 : sheep */
    ajouter_balle_obj(game, new_balle(new_vect(9, 9), 2, 6, 0, "img/balle_blaireau.png")); /* 7 : blaireau */
    ajouter_balle_obj(game, new_balle(new_vect(33, 15), 2, 5, 0, "img/balle_goldsheep.png")); /* 8 : goldsheep */
    ajouter_balle_obj(game, new_balle(new_vect(12, 12), 2, 8, 0, "img/balle_poule.png")); /* 9 */
    ajouter_balle_obj(game, new_balle(new_vect(18, 18), 2, 5, 0, "img/balle_taureau.png")); /* 10 */
    ajouter_balle_obj(game, new_balle(new_vect(15, 24), 2, 8, 0, "img/balle_icepig.png")); /* 11 */
    ajouter_balle_obj(game, new_balle(new_vect(24, 24), 2, 4, 0, "img/balle_bear.png")); /* 12 : ours */
    ajouter_balle_obj(game, new_balle(new_vect(12, 12), 2, 3, 0, "img/balle_coq.png")); /* 13 : coq */
    ajouter_balle_obj(game, new_balle(new_vect(12, 12), 1, 9, 0, "img/balle_bear.png")); /* 14 : ours plus vite */

    /* armes, 5 armes */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], STRAIGHT, 8)); /* 0 : tir normal jaune */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], CONE, 15)); /* 1 : tir en cône, 3 balles */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], CONE, 5)); /* 2 */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], CONE, 5)); /* 3 */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], CONE, 5)); /* 4 */
    /* armes des ennemis */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[5], STRAIGHT, 30)); /* 5 : tir cochon droit */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[6], STRAIGHT, 30)); /* 6 : tir mouton droit */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[10], BOMB, 20)); /* 7 : tir taureau dans 8 directions */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[9], SIDES, 20)); /* 8 : tir poule sur les côtés */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[6], THREE, 30)); /* 9 */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[6], RANDOWN, 5)); /* 10 */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[7], RANDOM, 5)); /* 11 : tir blaireau aléatoire */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[12], RANDOWN, 4)); /* 12 : tir golsheep vers le bas */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[13], CROSS, 20)); /* 13 : tir coq sur tous les côtés */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[8], STRAIGHT, 40)); /* 14 : tir VERT BARRE vers le bas */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[14], VISE, 20)); /* 15 : tir ours vers le joueur */

    /* ennemis de BASE: une arme et un sprite */
    printf("ennemi add...\n");
    ajouter_ennemi_obj(game, /* 0 : taureau, BOMB */
		       new_ennemi(new_vect(33, 33), 3, 20, game -> armes_obj[7], "img/taureau.png"));
    ajouter_ennemi_obj(game, /* 1 : cochon droit */
		       new_ennemi(new_vect(27, 42), 5, 10, game -> armes_obj[5], "img/cochon.png"));
    ajouter_ennemi_obj(game, /* 2 : poule côtés */
		       new_ennemi(new_vect(24, 30), 3, 4, game -> armes_obj[8], "img/poule.png"));
    ajouter_ennemi_obj(game, /* 3 : mouton droit */
		       new_ennemi(new_vect(33, 33), 4, 6, game -> armes_obj[6], "img/mouton.png"));
    ajouter_ennemi_obj(game, /* 4 : mouton */
		       new_ennemi(new_vect(33, 33), 2, 20, game -> armes_obj[12], "img/goldsheep.png"));
    ajouter_ennemi_obj(game, /* 5 : blaireau */
		       new_ennemi(new_vect(21, 36), 5, 10, game -> armes_obj[11], "img/blaireau.png"));
    ajouter_ennemi_obj(game, /* 6 : ours */
		       new_ennemi(new_vect(33, 33), 6, 10, game -> armes_obj[15], "img/bear.png"));
    ajouter_ennemi_obj(game, /* 7 : coq */
		       new_ennemi(new_vect(24, 30), 3, 10, game -> armes_obj[13], "img/coq.png"));
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
  g.wc = NOM_WAVE_T; /* pour que le jeu puisse commencer sur l'affichage de la wave 01 */
  g.wave_act = 0;
  g.w_i = 0;

  /* chargement des images à afficher en fond */
  g.img_fonds[0] = MLV_load_image("img/fond_plaine.png");
  g.img_fonds[1] = MLV_load_image("img/fond_foret.png");

  /* charger les polices une seule fois au début */
  g.police_nom_wave = MLV_load_font("font/pixelated.ttf", 40);
  g.police_score = MLV_load_font("font/pixelated.ttf", 14);

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
