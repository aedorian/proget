#ifndef _TYPES_H_
#define _TYPES_H_

#include <MLV/MLV_all.h>
#include <time.h>

#define JOUEURS_MAX 2 /* joueurs max, taille maximale de la file associée */
#define BALLES_MAX 250 /* balles maximum affichables à l'écran */
#define ENNEMIS_MAX 20 /* ennemis maximum sur l'écran */
#define WAVES_MAX 30
#define WAVES_INSTR_MAX 30
#define IMAGE_MAX 30 /* maximum d'images différentes pour un type d'image (balles, ennemis...) */

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
  int image; /* identifiant de l'image dans la liste des images balles */

  int existe; /* 1 si la balle existe (affichée à l'écran et collisions gérées), 0 si elle a touché quelque chose et qu'elle n'existe plus */
  int powerup; /* 0 si ce n'est pas une balle, 1 si c'est un coeur, 2 une arme */
} balle;

enum type_tir {
    STRAIGHT,
    CONE,
    BOMB,
    SIDES,
    THREE,
    VISE,
    RANDOM,
    RANDOWN,
    CROSS,
    DOUBLE,
    PUMP,
    MULTI
};
typedef enum type_tir type_tir;

typedef struct {
    balle balle;
    type_tir type_tir;
    int cadence; /* en frames, temps à attendre avant de pouvoir tirer */
    int cadence_act; /* cadence actuelle */
    int id_arme; /* juste utilisé pour savoir si on change sur la même arme ou non */
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
  int image; /* identifiant de l'image dans la liste des images ennemis */
  
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
  int image; /* identifiant de l'image dans la liste des images joueurs */
  
  int existe;
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

/* définit un type pour un score: est utilisé comme le score actuel */
typedef struct {
  int second; /* temps en secondes de la durée de la partie */
  int score;
  
  /* pour compter la durée totale d'une portion de la partie:
     à chaque fois que l'on met en pause ou qu'on meurt, on recalcule t_fin_game
     et on ajoute (t_fin_game - t_debut_game) à second dans score_act.
     on recalcule t_debut_game à chaque fois qu'on reprend la partie */
  struct timespec t_debut_game;
} highscore;

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
  balle balles_obj[30];
  arme armes_obj[20];
  ennemi ennemis_obj[20];
  int n_balles_obj;
  int n_armes_obj;
  int n_ennemis_obj;

  /* écran courant du jeu: menu, jeu, pause */
  int etat_ecran; /* 0 = écran titre, 1 = écran save, 2 = écran pause, 3 = jeu */
  int etat_ecran_precedent; /* l'état d'écran précédent, avant qu'on change le menu */
  int est_en_pause; /* 0 ou 1 */
  menu menu_titre; /* a type_menu = 0 */
  menu menu_save; /* a type_menu = 1 */
  menu menu_pause; /* a type_menu = 2 */
  MLV_Font* police_nom_wave; /* police d'affichage de la wave actuelle */
  MLV_Font* police_score; /* police d'affichage du score */
  MLV_Image* img_fonds[10]; /* fonds à afficher */

  highscore score_act; /* score actuel */
} game;

#endif /* _TYPES_H_ */
