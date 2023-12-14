#include "headers/gamemanager.h"
#include "headers/creation.h"
#include "headers/types.h"
#include "headers/mouvement.h"
#include "headers/affichage.h"
#include "headers/manip_fich.h"
#include <MLV/MLV_all.h>
#include <string.h>

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
      /* printf("ESSAI D'AJOUT LA OU C'EST LIBRE en i = %d sur nb_balles = %d\n", i, n); */
      game -> balles[i] = *balle;
      return; /* pour ne pas continuer l'itération */
    }
  }
  
  /* sinon, tous les emplacements sont déjà pris, alors on en crée un */
  if (game -> n_balles < BALLES_MAX) {
    /* printf("nb balles: %d\n", game -> n_balles); */
    game -> balles[game -> n_balles] = *balle;
    (game -> n_balles)++; /* et on ajoute 1 à la taille du tableau balles */
  }
}

void creer_ennemi(ennemi* ennemi, game* game, vect pos) {
  int i, n;
  n = game -> n_ennemis;
  for (i=0; i < n; i++) { /* on itère le tableau ennemis */
    if (game -> ennemis[i].existe == 0) { /* jusqu'à en trouver un qui n'existe plus
					    (donc un emplacement libre) */
      game -> ennemis[i] = *ennemi;
      game -> ennemis[i].pos.x = pos.x; /* le créer à la position spécifiée */
      game -> ennemis[i].pos.y = pos.y;
      game -> ennemis[i].existe = 1;
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
    game -> armes_obj[game -> n_armes_obj].id_arme = game -> n_armes_obj;
    (game -> n_armes_obj)++;
}

void ajouter_ennemi_obj(game* game, ennemi ennemi) {
    game -> ennemis_obj[game -> n_ennemis_obj] = ennemi;
    (game -> n_ennemis_obj)++;
}

/* POUR TOUT CE QUI EST GERER PARTIE */
void init_partie(game* game, int nb_joueurs) {
  joueur joueur1, joueur2;

  /* réinitialiser une nouvelle partie */
  new_game(game);

  /* créer les joueurs */
  /* voir arme par défaut? */
  joueur1 = new_joueur(new_vect(150, 550), new_vect(0, 0), 5,
		       game -> armes_obj[0], VACHE_1);
  creer_joueur(&joueur1, game);
  if (nb_joueurs == 2) {
    joueur2 = new_joueur(new_vect(480, 550), new_vect(0, 0), 5,
			 game -> armes_obj[0], VACHE_2);
    creer_joueur(&joueur2, game);
  }

  reprendre_temps_game(game);
  game -> etat_ecran = 3; /* commencer la partie en basculant sur l'écran de jeu */
}

/* POUR LES SCORES */
void ajouter_score(game *game, int score) {
  game -> score_act.score += score;
}

void arreter_temps_game(game *game) {
  long diff;
  struct timespec t_fin_game;
  clock_gettime(CLOCK_REALTIME, &t_fin_game);
  
  /* fait directement la conversion */
  diff = (t_fin_game.tv_sec - (game -> score_act.t_debut_game.tv_sec));
  game -> score_act.second += diff;
}
void reprendre_temps_game(game *game) {
  clock_gettime(CLOCK_REALTIME, &(game -> score_act.t_debut_game));
}

/* POUR LES VAGUES D'ENNEMIS */

void gerer_waves(game *game, wave_instr waves[WAVES_MAX][WAVES_INSTR_MAX]) {
  wave_instr* instr_act;
  int i; /* pour itérer sur les joueurs */

  /* gestion de la mort */
  if (game -> n_joueurs == 0) {
    if (game -> wc < 0) {
      (game -> wc)++;
    } else {
      sauvegarde_highscore(game -> score_act.score, game -> score_act.second);
      game -> etat_ecran = 4;
    }
  }

  /* fin du jeu */
  if (game -> wave_act == 20) {
    if (game -> wc < 0) {
      (game -> wc)++;
    } else {
      sauvegarde_highscore(game -> score_act.score, game -> score_act.second);
      game -> etat_ecran = 4;
    }
  }
  else {
    
  if (game -> wave_act_est_finie) {
    /* on continue seulement si il n'y a plus d'ennemis (ils sont tous morts) */
    if (game -> n_ennemis == 0) {
      game -> w_i = 0;
      game -> wave_act_est_finie = 0;
      (game -> wave_act)++;
      game -> wc = NOM_WAVE_T; /* attend 100 frames en affichant le nom de la wave */
      printf("DEBUT WAVE %d ----------------------\n", game -> wave_act + 1);

      /* remettre les vies des joueurs au max à chaque changement de zone */
      if (game -> wave_act % 4 == 0 || game -> wave_act == 19) {
	for (i=0; i < game -> n_joueurs; i++) {
	  if (game -> joueurs[i].existe) {
	    game -> joueurs[i].vie = J_VIE_INIT;
	  }
	}
      }
    }
    return; /* mais sinon, on s'arrête là */
  }

  /* wave_act_est_finie = 0, donc on s'occupe de gérer la wave (spawns, attente...) */
  if (game -> wc == 0) {
      
    /* traiter l'évènement */
    /* printf("%d %d %d\n", game -> wc, game -> wave_act, game -> w_i); */
    switch (waves[game -> wave_act][game -> w_i].type_instr) {
    case 'S':
      /* spawn ennemi */
      printf("debut spawn (de la wave %d)\n", game -> wave_act + 1);
      instr_act = &(waves[game -> wave_act][game -> w_i]);
      creer_ennemi(&(instr_act -> ennemi),
		   game,
		   new_vect(instr_act -> pos_x, instr_act -> pos_y));
      printf("ennemi spawné\n");
      
      break;
    case 'W':
      printf("evenement wait %c\n", waves[game -> wave_act][game -> w_i].type_instr);
      game -> wc = waves[game -> wave_act][game -> w_i].pos_x; /* pos_x est aussi utilisé pour le temps */
      printf("wc = %d\n", game -> wc);
      break;
    case 'E':
      /* fin de la vague, on passe à la suivante */
      game -> wave_act_est_finie = 1; /* la wave actuelle a fini de s'exécuter: tout a spawn, tout a attendu */
      game -> w_i = 0;
      break;
    }

    /* printf("incrémente w_i\n"); */
    (game -> w_i)++; /* passer au prochain évènement */
  }
  else {
    /* on utilise le fait que (game -> wc) soit négatif pour afficher le nom de la wave */
    if (game -> wc < 0) {
      (game -> wc)++; /* on décrémente wc pour avancer */
    }
    else {
      (game -> wc)--; /* on décrémente wc pour avancer */
    }
  }

  }
}


/* analyser une ligne du fichier de vague .wv, et en obtenir des donnés que l'on place dans une wave_instr */
void analyser_ligne_suivante(char ligne[100], char *type_instr, int *pos_x, int *pos_y, ennemi *e, game *game) {
  int i; /* pour parcourir la ligne caractère par caractère */
  int partie_analyse = 2; /* numéro de la partie entre les ;
			     commence à 2 car le caractère d'instruction est
			     analysé au début, à part */
  int i_parse = 0; /* pour la chaîne de la partie analysée */
  int n_parse; /* longueur de la ligne */
  char parse_tmp[100]; /* pour la ligne */

  /* variables temporaires à utiliser pour la création de l'ennemi plus tard */
  int id_t_tmp = 0; /* 0 seulement pour éviter le warning */
  char mouvements_tmp[200];

  ennemi *e_base;

  /* printf("ligne reçue: %s", ligne); */

  /* analyse de la ligne */
  *type_instr = ligne[0]; /* instruction */
  n_parse = strlen(ligne) - 1; /* taille de la chaîne */
  for (i=2; i < n_parse; i++) {
    if (ligne[i] != ';') {
      parse_tmp[i_parse] = ligne[i];
      i_parse++;
    }
    else {
      parse_tmp[i_parse] = '\0'; /* terminer la chaîne */
      switch (partie_analyse) {
      case 2:
	id_t_tmp = atoi(parse_tmp);
	break;
      case 3:
	strcpy(mouvements_tmp, parse_tmp);
	break;
      case 4:
	/* printf("WAVE WAIT: %d\n", atoi(parse_tmp)); */
        *pos_x = atoi(parse_tmp);
	break;
      case 5:
	*pos_y = atoi(parse_tmp);
	break;
      }
      partie_analyse++;
      i_parse = 0;
    }
  }

  if (*type_instr == 'W') {
    *pos_x = id_t_tmp;
  }

  if (*type_instr != 'S') {
    return;
  }
  /* la suite s'occupe seulement de l'instruction spawn, avec les ennemis */

  /* printf("%d\n", id_t_tmp); */
  e_base = &(game -> ennemis_obj[id_t_tmp]);

  /* recopier le contenu de l'ennemi de base dans l'ennemi de l'instruction */
  e -> hitbox.x = e_base -> hitbox.x;
  e -> hitbox.y = e_base -> hitbox.y;
  e -> vitesse = e_base -> vitesse;
  e -> vie = e_base -> vie;
  e -> arme = e_base -> arme;
  e -> image = e_base -> image;
  e -> existe = 1;
  /* puis extraire ses mouvements à partir de la chaîne mouvements_tmp */
  charger_mouvement_ennemi(e, mouvements_tmp);

  /* printf("DEBUG ENNEMI\n");

  for (i=0; i < e -> n_mouvements; i++) {
    printf("%d: %c %d\n", i, e -> mouvements[i].movetype, e -> mouvements[i].duree);
    } */
}



void charger_waves_dans_tab(game *game, wave_instr waves[WAVES_MAX][WAVES_INSTR_MAX]) {
  int i_w = 0; /* index de l'instruction à charger dans la vague */
  int wave_act; /* index de la vague courante étant chargée */

  FILE * fich_wave;
  char chemin_fich_wave[16] = "waves/wave00.wv"; /* le chemin d'accès de la vague courante à analyser
						    commence à 00 pour pouvoir l'incrémenter juste après*/
  char ligne_tmp[200];

  printf("DEBUT CHARGER WAVES --------------\n");

  /* FORMAT A LIRE: instruction;id;mouvements;posx;posy; */

  /* NB_WAVES défini dans headers/gamemanager.h */
  for (wave_act = 0; wave_act < NB_WAVES; wave_act++) {
    /* génération du prochain chemin d'accès */
    printf("normal: %d %d\n", (wave_act + 1) / 10, (wave_act + 1) % 10);
    chemin_fich_wave[10] = '0' + (wave_act + 1) / 10;
    chemin_fich_wave[11] = '0' + (wave_act + 1) % 10;
    printf("chars: %c %c\n", chemin_fich_wave[10], chemin_fich_wave[11]);
    
    printf("wave_act = %d\n", wave_act);
    if ((fich_wave = fopen(chemin_fich_wave, "r")) == NULL){ /* chemin_fich_wave */
        printf("Erreur ouverture fichier de vague, fichier corrompu\n");
        exit(EXIT_FAILURE);
    }

    i_w = 0;
    while (fgets(ligne_tmp, 200, fich_wave)) { /* ATTENTION: il y a un \n à la fin */
      /* while (fscanf(fich_wave, "%c;%d;",
	 &type_instr_tmp, &id_t_tmp) >= 2) { */

      /* parse la chaîne obtenue */
      analyser_ligne_suivante(ligne_tmp, &waves[wave_act][i_w].type_instr,
			      &waves[wave_act][i_w].pos_x,
			      &waves[wave_act][i_w].pos_y,
			      &waves[wave_act][i_w].ennemi, game);
      
      printf("char: %c;pos_x: %d;pos_y: %d;\n", waves[wave_act][i_w].type_instr,
	 waves[wave_act][i_w].pos_x, waves[wave_act][i_w].pos_y);

      i_w++; /* on passe à la prochaine instruction */
    }

    printf("---> instructions chargées: %d dans waves[%d]\n", i_w, wave_act);

    fclose(fich_wave);
  }

  printf("GROS DEBUG\n");
  for (wave_act = 0; wave_act < NB_WAVES; wave_act++) {
    
  }

  /* on a obtenu toutes les instructions dans waves[][] */
  /* appliquer le mouvement? */

  printf("CHARGEMENT VAGUES TERMINE -------------\n");

  
  /* recopier les données de l'ennemi de la vague analysée dans e_act
  e_tmp = &(game -> ennemis_obj[i_e]);
  e.hitbox.x = hitbox.x; e.hitbox.y = hitbox.y;
  e.vitesse = vitesse;
  e.vie = vie;
  e.arme = arme;
  e.image = MLV_load_image(img_path);
  e_act = new_ennemi(e_tmp -> hitbox, e_tmp -> vitesse, e_tmp -> vie,
  e_tmp -> arme, e_tmp -> img_path); */
}



/* charge mouvements d'un ennemi à partir d'une chaîne de caractères */
void charger_mouvement_ennemi(ennemi *e, char* mouvements) {
  int i = 0;
  int n_mouvements = 0; /* nombre de mouvements différents, donc d'éléments dans e.mouvements */
  mouvement m_tmp; /* mouvement temporaire à insérer dans le tableau e.mouvements */
  char duree_tmp[3]; /* durée (2 chiffres, plus 1 pour le '\0') à extraire de mouvements */
  /* pos d'où le mettre? */

  /* la chaîne mouvements est sous la forme "R 10 L 30 U 10 R 40", c'est à dire
     un caractère et un entier. la suite de la fonction parcourt la chaîne.
     les abréviations sont: R = right, L = left; U = up; D = down */

  duree_tmp[2] = '\0'; /* terminer par '\0' au préalable, ce caractère ne sera pas changé */
  while (mouvements[i] != '\0') {
    /* char 1 = caractère symbolisant la direction du mouvement */
    m_tmp.movetype = mouvements[i];
    duree_tmp[0] = mouvements[i+2];
    duree_tmp[1] = mouvements[i+3];
    m_tmp.duree = atoi(duree_tmp);

    e -> mouvements[n_mouvements] = m_tmp;
    
    i += 5;
    n_mouvements++;
  }

  e -> n_mouvements = n_mouvements;

  e -> i_mouv_act = 0; /* mouvement actuel est le premier */
  
  e -> mouv_count = 0; /* initialiser le compteur à 0, aucun lien avec mouvements pour le moment */

  /* initialiser la direction au premier mouvement */
  e -> dir = dir_from_char_vit(e -> mouvements[0].movetype, e -> vitesse);
}
