#include "headers/creation.h"
#include "headers/types.h"
#include "headers/gamemanager.h"
#include "headers/mouvement.h" /* pour dir_from_char_vit */
#include "headers/affichage.h"
#include <MLV/MLV_all.h>

/* crée tous les objets qui vont être utilisables dans le jeu: différentes balles, ennemis... */
void creer_tous_objets(game* game) {
  /* balles du joueur */
  ajouter_balle_obj(game, new_balle(new_vect(9, 18), 2, 10, 1, B_VACHE)); /* 0 : tir jaune normal */
  ajouter_balle_obj(game, new_balle(new_vect(9, 12), 1, 10, 1, B_VACHE_PETITE)); /* 1 : tir jaune petit */
  ajouter_balle_obj(game, new_balle(new_vect(15, 21), 4, 10, 1, B_VACHE_GRANDE)); /* 2 : tir jaune grand */
  ajouter_balle_obj(game, new_balle(new_vect(12, 12), 2, 10, 1, B_VACHE)); /* 3 */
  ajouter_balle_obj(game, new_balle(new_vect(9, 9), 2, 10, 1, B_VACHE)); /* 4 */
    /* balles des ennemis (définies par le 0 avant la macro) */
    ajouter_balle_obj(game, new_balle(new_vect(15, 24), 2, 5, 0, B_PIG)); /* 5 : cochon */
    ajouter_balle_obj(game, new_balle(new_vect(18, 18), 2, 5, 0, B_SHEEP)); /* 6 : sheep */
    ajouter_balle_obj(game, new_balle(new_vect(9, 9), 2, 6, 0, B_BLAIREAU)); /* 7 : blaireau */
    ajouter_balle_obj(game, new_balle(new_vect(33, 15), 2, 5, 0, B_GOLDSHEEP)); /* 8 : goldsheep */
    ajouter_balle_obj(game, new_balle(new_vect(12, 12), 2, 8, 0, B_POULE)); /* 9 */
    ajouter_balle_obj(game, new_balle(new_vect(18, 18), 2, 5, 0, B_TAUREAU)); /* 10 */
    ajouter_balle_obj(game, new_balle(new_vect(15, 24), 2, 8, 0, B_ICEPIG)); /* 11 */
    ajouter_balle_obj(game, new_balle(new_vect(24, 24), 2, 4, 0, B_BEAR)); /* 12 : ours */
    ajouter_balle_obj(game, new_balle(new_vect(12, 12), 1, 3, 0, B_COQ)); /* 13 : coq */
    ajouter_balle_obj(game, new_balle(new_vect(24, 24), 1, 9, 0, B_BEAR)); /* 14 : ours plus vite */
    ajouter_balle_obj(game, new_balle(new_vect(12, 12), 2, 8, 0, B_POULE)); /* 15 */
    ajouter_balle_obj(game, new_balle(new_vect(18, 18), 2, 5, 0, B_TAUREAU)); /* 16 */
    ajouter_balle_obj(game, new_balle(new_vect(15, 24), 2, 8, 0, B_ICEPIG)); /* 17 */
    ajouter_balle_obj(game, new_balle(new_vect(18, 18), 2, 7, 0, B_MEDUSE)); /* 18 */
    /* power-ups (définis comme des balles ennemies pour simplifier) */
    ajouter_balle_obj(game, new_balle(new_vect(21, 18), 1, 5, 0, PW_COEUR)); /* 19 */
    ajouter_balle_obj(game, new_balle(new_vect(30, 18), 1, 5, 0, PW_ARME)); /* 20 */

    /* armes joueur: 5 armes */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], STRAIGHT, 8)); /* 0 : tir normal jaune 8 */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], CONE, 15)); /* 1 : tir en cône, 3 balles */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[0], DOUBLE, 12)); /* 2 : double tir */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[1], STRAIGHT, 4)); /* 3 : tir jaune plus petit */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[2], STRAIGHT, 17)); /* 4 : grosse balle */
    /* armes des ennemis */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[5], STRAIGHT, 30)); /* 5 : tir cochon droit */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[6], STRAIGHT, 30)); /* 6 : tir mouton droit */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[10], BOMB, 20)); /* 7 : tir taureau dans 8 directions */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[9], SIDES, 20)); /* 8 : tir poule sur les côtés */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[6], PUMP, 25)); /* 9 : tir icepig */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[18], MULTI, 20)); /* 10 */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[7], RANDOM, 5)); /* 11 : tir blaireau aléatoire */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[12], RANDOWN, 4)); /* 12 : tir goldsheep vers le bas */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[13], CROSS, 30)); /* 13 : tir coq sur tous les côtés */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[8], STRAIGHT, 40)); /* 14 : tir VERT BARRE vers le bas */
    ajouter_arme_obj(game, new_arme(game -> balles_obj[14], VISE, 30)); /* 15 : tir ours vers le joueur */

    /* ennemis de BASE: une arme et un sprite (le mouvement sera ajouté plus tard dans le chargement des vagues) */
    ajouter_ennemi_obj(game, /* 0 : taureau */
		       new_ennemi(new_vect(33, 33), 3, 20, game -> armes_obj[7], TAUREAU));
    ajouter_ennemi_obj(game, /* 1 : cochon */
		       new_ennemi(new_vect(27, 42), 5, 10, game -> armes_obj[5], COCHON));
    ajouter_ennemi_obj(game, /* 2 : poule côtés */
		       new_ennemi(new_vect(24, 30), 3, 4, game -> armes_obj[8], POULE));
    ajouter_ennemi_obj(game, /* 3 : mouton droit */
		       new_ennemi(new_vect(33, 33), 4, 6, game -> armes_obj[6], MOUTON));
    ajouter_ennemi_obj(game, /* 4 : mouton */
		       new_ennemi(new_vect(33, 33), 2, 20, game -> armes_obj[12], GOLDSHEEP));
    ajouter_ennemi_obj(game, /* 5 : blaireau */
		       new_ennemi(new_vect(21, 36), 5, 10, game -> armes_obj[11], BLAIREAU));
    ajouter_ennemi_obj(game, /* 6 : ours */
		       new_ennemi(new_vect(33, 33), 6, 10, game -> armes_obj[15], BEAR));
    ajouter_ennemi_obj(game, /* 7 : coq */
		       new_ennemi(new_vect(24, 30), 3, 8, game -> armes_obj[13], COQ));
    ajouter_ennemi_obj(game, /* 8 : icepig */
		       new_ennemi(new_vect(27, 42), 3, 8, game -> armes_obj[9], ICEPIG));
    ajouter_ennemi_obj(game, /* 9 : meduse */
		       new_ennemi(new_vect(57, 45), 5, 40, game -> armes_obj[10], MEDUSE));
}

/* charger toutes les images du jeu */
void charger_images(MLV_Image* img_balles[], MLV_Image* img_joueurs[], MLV_Image* img_ennemis[]){
    img_balles[B_VACHE] = MLV_load_image("img/balle_vache.png");
    img_balles[B_PIG] = MLV_load_image("img/balle_pig.png");
    img_balles[B_SHEEP] = MLV_load_image("img/balle_sheep.png");
    img_balles[B_BLAIREAU] = MLV_load_image("img/balle_blaireau.png");
    img_balles[B_GOLDSHEEP] = MLV_load_image("img/balle_goldsheep.png");
    img_balles[B_POULE] = MLV_load_image("img/balle_poule.png");
    img_balles[B_TAUREAU] = MLV_load_image("img/balle_taureau.png");
    img_balles[B_ICEPIG] = MLV_load_image("img/balle_icepig.png");
    img_balles[B_BEAR] = MLV_load_image("img/balle_bear.png");
    img_balles[B_COQ] = MLV_load_image("img/balle_coq.png");
    img_balles[B_VACHE_PETITE] = MLV_load_image("img/balle_vache_petite.png");
    img_balles[B_VACHE_GRANDE] = MLV_load_image("img/balle_vache_grande.png");
    img_balles[B_MEDUSE] = MLV_load_image("img/balle_meduse.png");

    img_balles[PW_COEUR] = MLV_load_image("img/power_coeur.png");
    img_balles[PW_ARME] = MLV_load_image("img/power_arme.png");

    img_joueurs[VACHE_1] = MLV_load_image("img/vache1.png");
    img_joueurs[VACHE_2] = MLV_load_image("img/vache2.png");

    img_ennemis[TAUREAU] = MLV_load_image("img/taureau.png");
    img_ennemis[COCHON] = MLV_load_image("img/cochon.png");
    img_ennemis[POULE] = MLV_load_image("img/poule.png");
    img_ennemis[MOUTON] = MLV_load_image("img/mouton.png");
    img_ennemis[GOLDSHEEP] = MLV_load_image("img/goldsheep.png");
    img_ennemis[BLAIREAU] = MLV_load_image("img/blaireau.png");
    img_ennemis[BEAR] = MLV_load_image("img/bear.png");
    img_ennemis[COQ] = MLV_load_image("img/coq.png");
    img_ennemis[ICEPIG] = MLV_load_image("img/icepig.png");
    img_ennemis[MEDUSE] = MLV_load_image("img/meduse.png");
}

game new_game(game* g) {
  /* initialiser le nombre d'élément des listes d'entités */
  g -> n_balles = 0;
  g -> n_joueurs = 0;
  g -> n_ennemis = 0;
  /* obtenir tous les objets possibles */
  g -> n_balles_obj = 0;
  g -> n_armes_obj = 0;
  g -> n_ennemis_obj = 0;

  g -> etat_ecran = 0; /* commence sur l'écran titre */
  /* menus - écran titre*/
  g -> menu_titre.opt_act = 0;
  g -> menu_titre.nb_opt = 5;
  g -> menu_titre.type_menu = 0;
  /* écran de save */
  g -> menu_save.opt_act = 0;
  g -> menu_save.nb_opt = 4;
  g -> menu_save.type_menu = 1;
  /* écran de pause */
  g -> menu_pause.opt_act = 0;
  g -> menu_pause.nb_opt = 3;
  g -> menu_pause.type_menu = 2;

  /* waves */
  g -> wc = NOM_WAVE_T; /* pour que le jeu puisse commencer sur l'affichage de la wave 01 */
  g -> wave_act = 0; /* commencer à la première vague */
  g -> w_i = 0;
	
  /* score */
  g -> score_act.score = 0;
  g -> score_act.second = 0;

  /* chargement des images à afficher en fond */
  g -> img_fonds[0] = MLV_load_image("img/back1.png");
  g -> img_fonds[1] = MLV_load_image("img/back2.png");
  g -> img_fonds[2] = MLV_load_image("img/back3.png");
  g -> img_fonds[3] = MLV_load_image("img/back4.png");
  g -> img_fonds[4] = MLV_load_image("img/back5.png");
  g -> img_fonds[5] = MLV_load_image("img/back6.png");

  /* charger les polices une seule fois au début */
  g -> police_nom_wave = MLV_load_font("font/pixelated.ttf", 40);
  g -> police_score = MLV_load_font("font/pixelated.ttf", 16);
	
  creer_tous_objets(g);
  
  return *g;
}

/* créer un struct de type joueur (ne le crée pas dans le jeu) */
joueur new_joueur(vect pos_init, vect dir_init, int vitesse, arme arme, int indice_image) {
  joueur j;
  j.hitbox.x = J_HITBOX_W; j.hitbox.y = J_HITBOX_H;
  j.pos.x = pos_init.x;    j.pos.y = pos_init.y;
  j.dir.x = dir_init.x;    j.dir.y = dir_init.y;
  j.vitesse = vitesse;
  j.vie = J_VIE_INIT;
  j.arme = arme;
  j.image = indice_image;
  j.existe = 1;
  
  return j;
}

balle new_balle(vect hitbox, int damage, float vitesse, int estJoueur, int indice_image) {
    balle b;
    b.hitbox.x = hitbox.x; b.hitbox.y = hitbox.y;
    b.damage = damage;
    b.vitesse = vitesse;
    b.estJoueur = estJoueur;
    b.image = indice_image;
    b.powerup = 0; /* la balle par défaut n'est pas un powerup */

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

ennemi new_ennemi(vect hitbox, int vitesse, int vie, arme arme, int indice_image) {
  ennemi e;
  /* pos d'où le mettre? */
  e.hitbox.x = hitbox.x; e.hitbox.y = hitbox.y;
  e.vitesse = vitesse;
  e.vie = vie;
  e.arme = arme;
  e.image = indice_image;

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
