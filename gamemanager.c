#include "headers/gamemanager.h"
#include "headers/creation.h"
#include "headers/types.h"
#include <MLV/MLV_all.h>

/* crée vraiment un joueur et le crée dans le game */
void creer_joueur(joueur* joueur, game* game) {
  game -> joueurs[game -> n_joueurs] = *joueur; /* l'ajouter à la fin du tableau */
  (game -> n_joueurs)++; /* il y a un joueur de plus */
}

void creer_balle(balle* balle, game* game) {
  int i, n;
  n = game -> n_balles;
  for (i=0; i < n; i++) { /* on itère balles */
    if (game -> balles[i].existe == 0) { /* jusqu'à en trouver une qui n'existe plus
					    (donc un emplacement libre) */
      game -> balles[i] = *balle;
      return; /* pour ne pas continuer l'itération */
    }
  }
  /* sinon, tous les emplacements sont déjà pris, alors on en crée un */

  if (game -> n_balles < BALLES_MAX) {
    printf("nb balles: %d\n", game -> n_balles);
    game -> balles[game -> n_balles] = *balle;
    (game -> n_balles)++; /* et on ajoute 1 à la taille du tableau balles */
  }
}

void creer_ennemi(ennemi* ennemi, game* game, vect pos) {
  int i, n;
  n = game -> n_ennemis;
  for (i=0; i < n; i++) { /* on itère balles */
    if (game -> ennemis[i].existe == 0) { /* jusqu'à en trouver une qui n'existe plus
					    (donc un emplacement libre) */
      game -> ennemis[i] = *ennemi;
      game -> ennemis[i].pos.x = pos.x; /* le créer à la position spécifiée */
      game -> ennemis[i].pos.y = pos.y;
      return; /* pour ne plus itérer */
    }
  }
  /* sinon, tous les emplacements sont déjà pris, alors on en crée un */
  
  game -> ennemis[game -> n_ennemis] = *ennemi;
  game -> ennemis[game -> n_ennemis].pos.x = pos.x; /* le créer à la position spécifiée */
  game -> ennemis[game -> n_ennemis].pos.y = pos.y;
  (game -> n_ennemis)++;
}

/* DEPLACER DANS CREATION.C? */
void ajouter_balle_obj(game* game, balle balle) {
    game -> balles_obj[game -> n_balles_obj] = balle;
    (game -> n_balles_obj)++;
}

void ajouter_arme_obj(game* game, arme arme) {
    game -> armes_obj[game -> n_armes_obj] = arme;
    (game -> n_armes_obj)++;
}

void ajouter_ennemi_obj(game* game, ennemi ennemi) {
    game -> ennemis_obj[game -> n_ennemis_obj] = ennemi;
    (game -> n_ennemis_obj)++;
}

/* POUR TOUT CE QUI EST GERER PARTIE */
void init_partie(game* game, int nb_joueurs) {
  joueur joueur1, joueur2;

  /* *game = new_game(); */

  /* créer les joueurs */
  /* voir arme par défaut? */
  joueur1 = new_joueur(new_vect(150, 550), new_vect(0, 0), 5,
		       game -> armes_obj[0], "img/vache.png");
  creer_joueur(&joueur1, game);
  if (nb_joueurs == 2) {
    joueur2 = new_joueur(new_vect(480, 550), new_vect(0, 0), 5,
			 game -> armes_obj[0], "img/vache.png");
    creer_joueur(&joueur2, game);
  }

  game -> etat_ecran = 3; /* commencer la partie en basculant sur l'écran de jeu */
}
