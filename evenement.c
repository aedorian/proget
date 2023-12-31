#include "headers/evenement.h"
#include "headers/creation.h"
#include "headers/gamemanager.h"
#include "headers/types.h"
#include <MLV/MLV_all.h>
#include <math.h>

/* fonction générale pour obtenir et gérer tous les évènements clavier */
void gerer_evenements_clavier(game* game) {
    int n, i;
    n = game -> n_joueurs;

    for (i=0; i < n; i++) {
      if (game -> joueurs[i].existe) {
	update_cadence_arme(&(game -> joueurs[i].arme));
      
        obtenir_deplacement_joueur(&(game -> joueurs[i]), i+1); /* i+1 pour le numéro du joueur, 1 ou 2 */
        obtenir_tir_joueur(game, &(game -> joueurs[i]), i+1);
      }
    }

    /* si l'on veut être en pause */
    if (MLV_get_keyboard_state(PAUSE) == MLV_PRESSED) {
      arreter_temps_game(game);
      game -> etat_ecran = 2;
    }
}

/* Change dir de joueur en un vecteur orthonormé */
void obtenir_deplacement_joueur(joueur* joueur, int numJoueur) {
    if (numJoueur == 1) {
        if (MLV_get_keyboard_state(J1_UP) == MLV_PRESSED)
            joueur -> dir.y = 1;
        else
	  if (MLV_get_keyboard_state(J1_DOWN) == MLV_PRESSED)
            joueur -> dir.y = -1;
	  else
            joueur -> dir.y = 0;
	
        if (MLV_get_keyboard_state(J1_RIGHT) == MLV_PRESSED)
            joueur -> dir.x = 1;
        else
	  if (MLV_get_keyboard_state(J1_LEFT) == MLV_PRESSED)
            joueur -> dir.x = -1;
	  else
            joueur -> dir.x = 0;
        
        
    }
    else {  /* joueur 2 */
	    if (MLV_get_keyboard_state(J2_UP) == MLV_PRESSED)
            joueur -> dir.y = 1;
        else
	  if (MLV_get_keyboard_state(J2_DOWN) == MLV_PRESSED)
            joueur -> dir.y = -1;
	  else
            joueur -> dir.y = 0;
	
        if (MLV_get_keyboard_state(J2_RIGHT) == MLV_PRESSED)
            joueur -> dir.x = 1;
        else
	  if (MLV_get_keyboard_state(J2_LEFT) == MLV_PRESSED)
            joueur -> dir.x = -1;
	  else
            joueur -> dir.x = 0;
    }

    /* appliquer la vitesse */
    joueur -> dir.x *= joueur -> vitesse;
    joueur -> dir.y *= joueur -> vitesse;
}

void obtenir_tir_joueur(game* game, joueur* joueur, int numJoueur) {
    if (numJoueur == 1) {
        if (MLV_get_keyboard_state(J1_TIR) == MLV_PRESSED) {
            tirer_arme_joueur(game, joueur);
        }
    }
    if (numJoueur == 2) {
        if (MLV_get_keyboard_state(J2_TIR) == MLV_PRESSED) {
            tirer_arme_joueur(game, joueur);
        }
    }
}

void faire_tirer_ennemis(game* game) {
  int i, n;
  ennemi* e; /* ennemi courant dans la boucle */
  n = game -> n_ennemis;

  for (i=0; i < n; i++) {
    e = &(game -> ennemis[i]);

    if (e -> existe == 1) {
      tirer_arme_ennemi(game, &(game -> ennemis[i]));

      update_cadence_arme(&(game -> ennemis[i].arme));
    }
  }
}

/* faire descendre la cadence_act de 1 */
void update_cadence_arme(arme* arme) {
    if (arme -> cadence_act != 0) {
        (arme -> cadence_act)--;
    }
}

/* définit une direction pour la balle en fonction de sa vitesse et d'un vecteur normalisé */
void set_balle_dir(balle* balle, vect dir) {
    balle -> dir = dir;
    balle -> dir.x *= balle -> vitesse;
    balle -> dir.y *= balle -> vitesse;
}

/* définit la direction de la balle en fonction d'un angle entre 0 et 2*pi */
void set_balle_angle_dir(balle* balle, float angle) {
  balle -> dir = new_vect(floor(cos(angle) * balle -> vitesse),
			  floor(sin(angle) * balle -> vitesse));
}

void set_balle_vise_dir(balle* balle, ennemi* e, game* game) {
  joueur* j; /* joueur à viser */
  float angle;
  int x, y;
	
  /* sélectionner un joueur à viser */
  if (game -> n_joueurs == 1) {
    j = &(game -> joueurs[0]);
  } else {
    j = &(game -> joueurs[rand() % 2]); /* sélectionner le joueur 1 ou le joueur 2 */
  }

  y = (j -> pos.y + j -> hitbox.y / 2) - (e -> pos.y + e -> hitbox.y);
  x = (j -> pos.x + j -> hitbox.x / 2) - (e -> pos.x + e -> hitbox.x);
  angle = atan2(-y, x);

  set_balle_angle_dir(balle, angle);
}

void tirer_arme_joueur(game* game, joueur* joueur) {
  balle balle_arme;

    if (joueur -> arme.cadence_act <= 0) {
        joueur -> arme.cadence_act = joueur -> arme.cadence;
	    
	balle_arme.pos.x = joueur -> pos.x + 11;
	balle_arme.pos.y = joueur -> pos.y;
	balle_arme.hitbox.x = joueur -> arme.balle.hitbox.x;
	balle_arme.hitbox.y = joueur -> arme.balle.hitbox.y;
	balle_arme.damage = joueur -> arme.balle.damage;
	balle_arme.vitesse = joueur -> arme.balle.vitesse;
	balle_arme.estJoueur = 1;
	balle_arme.image = joueur -> arme.balle.image;
	balle_arme.powerup = 0;
	balle_arme.existe = 1;
	
        switch (joueur -> arme.type_tir) {
        case STRAIGHT:
            set_balle_dir(&balle_arme, new_vect(0, 1)); 
            creer_balle(&balle_arme, game);
            break;
        case CONE:
	    set_balle_dir(&balle_arme, new_vect(0, 1)); 
            creer_balle(&balle_arme, game);
	    set_balle_angle_dir(&balle_arme, 1.396);
            creer_balle(&balle_arme, game);
	    set_balle_angle_dir(&balle_arme, 1.645);
            creer_balle(&balle_arme, game);
            break;
	case DOUBLE:
	  balle_arme.pos.x -= 6;
	  set_balle_dir(&balle_arme, new_vect(0, 1)); 
	  creer_balle(&balle_arme, game);
	  balle_arme.pos.x += 12;
	  creer_balle(&balle_arme, game);
	  break;
	default:
	  break;
        }
    }
}

void tirer_arme_ennemi(game* game, ennemi* ennemi) {
    balle balle_arme = ennemi -> arme.balle;

    if (ennemi -> arme.cadence_act == 0) {
        ennemi -> arme.cadence_act = ennemi -> arme.cadence;

	balle_arme.pos.x = ennemi -> pos.x + (ennemi -> hitbox.x)/2;
	balle_arme.pos.y = ennemi -> pos.y + (ennemi -> hitbox.y)/2;
	balle_arme.hitbox.x = ennemi -> arme.balle.hitbox.x;
	balle_arme.hitbox.y = ennemi -> arme.balle.hitbox.y;
	balle_arme.damage = ennemi -> arme.balle.damage;
	balle_arme.vitesse = ennemi -> arme.balle.vitesse;
	balle_arme.estJoueur = 0;
	balle_arme.image = ennemi -> arme.balle.image;
	balle_arme.powerup = ennemi -> arme.balle.powerup;
	balle_arme.existe = 1;
	
        switch (ennemi -> arme.type_tir) {
        case STRAIGHT:
            set_balle_dir(&balle_arme, new_vect(0, -1)); 
            creer_balle(&balle_arme, game);
            break;
        case BOMB:
            set_balle_dir(&balle_arme, new_vect(1, 0)); 
            creer_balle(&balle_arme, game);
            set_balle_dir(&balle_arme, new_vect(1, 1)); 
            creer_balle(&balle_arme, game);
	    set_balle_dir(&balle_arme, new_vect(0, 1)); 
            creer_balle(&balle_arme, game);
	    set_balle_dir(&balle_arme, new_vect(-1, 1)); 
            creer_balle(&balle_arme, game);
	    set_balle_dir(&balle_arme, new_vect(-1, 0)); 
            creer_balle(&balle_arme, game);
	    set_balle_dir(&balle_arme, new_vect(-1, -1)); 
            creer_balle(&balle_arme, game);
	    set_balle_dir(&balle_arme, new_vect(0, -1)); 
            creer_balle(&balle_arme, game);
	    set_balle_dir(&balle_arme, new_vect(1, -1)); 
            creer_balle(&balle_arme, game);
            break;
	case SIDES:
	  set_balle_dir(&balle_arme, new_vect(-1, 0)); 
            creer_balle(&balle_arme, game);
	    set_balle_dir(&balle_arme, new_vect(1, 0)); 
            creer_balle(&balle_arme, game);
	    break;
	case CROSS:
	  set_balle_dir(&balle_arme, new_vect(-1, 0)); 
            creer_balle(&balle_arme, game);
	    set_balle_dir(&balle_arme, new_vect(1, 0)); 
            creer_balle(&balle_arme, game);
	    set_balle_dir(&balle_arme, new_vect(0, 1)); 
            creer_balle(&balle_arme, game);
	    set_balle_dir(&balle_arme, new_vect(0, -1)); 
            creer_balle(&balle_arme, game);
	    break;
	case THREE:
	  set_balle_dir(&balle_arme, new_vect(-1, -1)); 
            creer_balle(&balle_arme, game);
	    set_balle_dir(&balle_arme, new_vect(0, -1)); 
            creer_balle(&balle_arme, game);
	    set_balle_dir(&balle_arme, new_vect(1, -1)); 
            creer_balle(&balle_arme, game);
	    break;
	case RANDOWN:
	  set_balle_angle_dir(&balle_arme,
			      (rand() % (314) + 314) * 0.01);
	  creer_balle(&balle_arme, game);
	  break;

	case RANDOM:
	  set_balle_angle_dir(&balle_arme,
			      (rand() % (628)) * 0.01);
	  creer_balle(&balle_arme, game);
	  break;

	case VISE:
	  set_balle_vise_dir(&balle_arme, ennemi, game);
	  creer_balle(&balle_arme, game);
	  break;

	case PUMP:
	  set_balle_angle_dir(&balle_arme, 4.712);
	  creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 4.512);
	  creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 4.312);
	  creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 4.912);
	  creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 5.112);
	  creer_balle(&balle_arme, game);
	  break;

	case MULTI:
	  set_balle_angle_dir(&balle_arme, 0.0); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 0.392); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 0.785); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 1.177); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 1.570); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 1.963); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 2.355); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 2.748); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 3.141); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 3.533); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 3.926); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 4.318); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 4.711); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 5.104); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 5.496); creer_balle(&balle_arme, game);
	  set_balle_angle_dir(&balle_arme, 5.889); creer_balle(&balle_arme, game);
	  
	default:
	  break;
        }
    }
}

void drop_powerup(game *game, int x, int y) {
  int random;
  balle powerup;
  random = rand() % 10; /* entre 0 et 9 */
  if (random > 5) {
    if (random < 8) {
      powerup = game -> balles_obj[19]; /* plus de vie */
      powerup.powerup = 1;
    } else {
      powerup = game -> balles_obj[20]; /* arme aléatoire */
      powerup.powerup = 2;
    }
    powerup.pos.x = x + 8;
    powerup.pos.y = y + 8;
    powerup.dir = new_vect(0, -3);
    creer_balle(&powerup, game);
  }
}
