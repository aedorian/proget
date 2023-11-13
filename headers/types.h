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
} balle;

/* ennemi */
typedef struct {
  vect hitbox;
  vect pos;
  vect dir;
  int vie;
  /* arme... */
} ennemi;

enum type_tir {
    STRAIGHT,
    CONE
};
typedef enum type_tir type_tir;

typedef struct {
    balle balle;
    type_tir type_tir;
    int cadence; /* en frames, temps à attendre avant de pouvoir tirer */
    int cadence_act; /* cadence actuelle */
} arme;

/* joueur */
typedef struct {
  vect hitbox;
  vect pos;
  vect dir;
  int vitesse;
  int vie;
    arme arme;
} joueur;

/* game, structure pour gérer les entités du jeu */
typedef struct {
    balle balles[BALLES_MAX]; /* files pour gérer les entités présentes dans le jeu */
    joueur joueurs[JOUEURS_MAX];
    ennemi ennemis[ENNEMIS_MAX];
    int n_balles; /* tailles de chacune des trois files */
    int n_joueurs;
    int n_ennemis;
    /* listes des places vides dans les listes des entités du jeu */
    int empty_balles[BALLES_MAX];
    int empty_ennemis[ENNEMIS_MAX];
    int n_empty_balles;
    int n_empty_ennemis;
    /* objets possibles dans le jeu */
    balle balles_obj[50];
    arme armes_obj[50];
    ennemi ennemi_obj[50];
    int n_balles_obj;
    int n_armes_obj;
    int n_ennemis_obj;
} game;

#endif /* _TYPES_H_ */
