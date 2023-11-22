#ifndef _TYPES_H_
#define _TYPES_H_

#include <MLV/MLV_all.h>

#define JOUEURS_MAX 2 /* joueurs max, taille maximale de la file associée */
#define BALLES_MAX 500 /* balles maximum affichables à l'écran */
#define ENNEMIS_MAX 100 /* ennemis maximum sur l'écran */
#define WAVES_MAX 20
#define WAVES_INSTR_MAX 30

/* couple de deux flottants */
/* utilisé pour pos, dir, dimensions de la hitbox... */
typedef struct {
  float x;
  float y;
} vect;

/* balle */
typedef struct {
  vect hitbox;
  vect pos;
  vect dir;
  int damage;
  int vitesse;
  int estJoueur; /* 1 si la balle provient d'un joueur, 0 si elle provient d'un ennemi */
  MLV_Image* image; /* image de la balle à afficher */
  int existe; /* 1 si la balle existe (affichée à l'écran et collisions gérées), 0 si elle a touché quelque chose et qu'elle n'existe plus */
} balle;

enum type_tir {
    STRAIGHT,
    CONE,
    BOMB,
    SIDES,
    THREE,
    VISE,
    RANDOM
};
typedef enum type_tir type_tir;

typedef struct {
    balle balle;
    type_tir type_tir;
    int cadence; /* en frames, temps à attendre avant de pouvoir tirer */
    int cadence_act; /* cadence actuelle */
} arme;

/* mouvement: couple char (représentant la direction) et durée en frames */
typedef struct {
  char movetype;
  int duree;
} mouvement;

/* ennemi */
typedef struct {
  vect hitbox;
  vect pos;
  vect dir;
  int vitesse;
  int vie;
  /* gère le mouvement: liste de directions avec une durée en frames */
  mouvement mouvements[20];
  int n_mouvements; /* taille du tableau mouvements */
  int mouv_count; /* compteur pour changer de type de mouvement */
  int i_mouv_act; /* indice du mouvement actuel dans le tableau de mouvements */
  arme arme;
  MLV_Image* image;
  int existe;
} ennemi;

/* joueur */
typedef struct {
  vect hitbox;
  vect pos;
  vect dir;
  int vitesse;
  int vie;
  arme arme;
  MLV_Image* image;
} joueur;

/* instruction dans un fichier de vague d'ennemis */
typedef struct {
  char type_instr; /* S pour créer un ennemi, ou W pour attendre */
  int pos_x; /* utilisé pour créer l'ennemi à telle position,
		mais aussi pour attendre si l'instruction est
		de type W (wait) */
  int pos_y;
  ennemi ennemi;
} wave_instr;

/* int id_t;
  char mouvements[100];
  int pos_x;
  int pos_y; */

/* menus */
typedef struct {
  int opt_act; /* option actuelle */
  int nb_opt; /* nombre d'options (option maximum, inclusive) */
  int type_menu; /* type du menu: 0 = écran titre,
		                  1 = high scores,
                                  2 = menu de pause */
} menu;

/* game, structure pour gérer les entités du jeu */
typedef struct {
  int score; /* score actuel */
  int debut_partie; /* en millisecondes, pour pouvoir calculer le temps de jeu */

  /* POUR LES WAVES */
  wave_instr waves[WAVES_MAX][WAVES_INSTR_MAX];
  int wc; /* wave compteur: compteur d'attente des vagues, utilisé dans gerer_waves() */
  int wave_act; /* identifiant de la vague actuelle
		   commence à 0 mais sera à wave_act + 1 dans l'affichage*/
  int w_i; /* instruction actuelle de la vague actuelle */
  int wave_act_est_finie;
  
  /* tableaux pour gérer les entités présentes dans le jeu */
  balle balles[BALLES_MAX];
  joueur joueurs[JOUEURS_MAX];
  ennemi ennemis[ENNEMIS_MAX];
  int n_balles; /* tailles de chacune des trois tableaux */
  int n_joueurs;
  int n_ennemis;
  
  /* objets possibles dans le jeu */
  balle balles_obj[50];
  arme armes_obj[50];
  ennemi ennemis_obj[50];
  int n_balles_obj;
  int n_armes_obj;
  int n_ennemis_obj;

  /* écran courant du jeu: menu, jeu, pause */
  int etat_ecran; /* 0 = écran titre, 1 = écran save, 2 = écran pause, 3 = jeu */
  int est_en_pause; /* 0 ou 1 */
  menu menu_titre; /* a type_menu = 0 */
  menu menu_save; /* a type_menu = 1 */
  menu menu_pause; /* a type_menu = 2 */
} game;

#endif /* _TYPES_H_ */
