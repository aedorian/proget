#ifndef _TYPES_H_
#define _TYPES_H_

#include <MLV/MLV_all.h>

#define JOUEURS_MAX 2 /* joueurs max, taille maximale de la file associée */
#define BALLES_MAX 500 /* balles maximum affichables à l'écran */
#define ENNEMIS_MAX 100 /* ennemis maximum sur l'écran */

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
    BOMB
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
  mouvement mouvements[50];
  int n_mouvements; /* taille du tableau mouvements */
  int mouv_count; /* compteur pour changer de type de mouvement */
  int i_mouv_act; /* indice du mouvement actuel */
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

/* game, structure pour gérer les entités du jeu */
typedef struct {
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

    /* listes des places vides dans les listes des entités du jeu */
    int libre_balles[BALLES_MAX];
    int libre_ennemis[ENNEMIS_MAX];
    int n_empty_balles;
    int n_empty_ennemis;
} game;

#endif /* _TYPES_H_ */
