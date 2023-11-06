### DOSSIER ###

proget
  [code .c]
  dossier .h?
  dossier images

### FICHIERS ###

"game manager" (manip save)
  charger game
  nouvelle game (retourne un game?)
  save game
  réorganiser_file(balle* file_balle[BALLES_MAX], int* taille_file)
  ajouter_balle_file(game* game, balle* balle);
  ajouter_joueur_file(game* game, joueur* joueur);
  ajouter_ennemi_file(game* game, ennemi* ennemi);

"affichage" CONVERTIR EN INT QUAND AFFICHER POS
  #define ECRAN_W 400
  #define ECRAN_H 600
  afficher joueurs
  afficher ennemi(s?)
  afficher balle(s?)
  debug collisions (afficher hitboxs)

"types" OU DOUBLE?
X typedef struct { float x; float y; } couple;

X struct game
  balle* balles[]   # ou deux listes?
  joueur* joueurs[]
  ennemi* ennemis[]
  int n_balles;
  int n_joueurs;
  int n_ennemis;

X struct ennemi
  int vie
  hitbox
  couple pos
  couple dir

X struct joueur
  transform transform
  int vie
  arme* arme;    # arme courante
  couple hitbox
  couple pos

X struct balle
  hitbox hitbox;
  couple pos
  couple dir
  int/float damage;
  int/float vitesse;
  int estJoueur?;
  MLV_Image* image; # stocker une seule fois dans la mémoire et fairre pointeur?

enum MODE_TIR { STRAIGHT, CONE, TRIPLE };    # forme du tir
enum TYPE_TIR { SINGLE, CONTINOUS };         # mode activation
struct arme
  balle* balle;
  MODE_TIR mode_tir;
  TYPE_TIR type_tir;
  int cadence; /* en frames */

"collisions"
  int hitbox_touche(hitbox* hb1, couple* pos1, hitbox* hb2, couple* pos2)

"évènements"
  void move_balles(game* game) {
    int n;
    int i;
    n = game -> n_balles;
    for (i=0; i < n; i++) {
      move_pos(game -> balles[i] -> pos, game -> balles[i] -> dir);
    }
    # utiliser même fonction plus longue pour bouger toutes les entités?
  }

"création"
  # FAIRE UNE NOUVELLE BALLE
  balle new_balle(int hitbox_w, int hitbox_h, int vitesse, int damage, MLV_Image image) {
    balle b;
    b.hitbox = new_couple(hitbox_w, hitbox_h);
    b.vitesse = vitesse;
    b.damage = damage;
    b.image = image;
    return b;
  }

  couple new_couple(int x, int y) {
    couple c;
    c.x = x; c.y = y;
    return c;
  }

"instantiation"
  #define BALLE_JOUEUR 1;
  #define BALLE_ENNEMI 0;
  void tirer_arme(game* game, arme* arme, couple* pos) {
    switch (arme -> type_tir) {
      case STRAIGHT: # voire en défaut
        instantiate_balle(game, arme -> balle, pos, new_couple(0, 1), BALLE_JOUEUR);
        break;
    }
  }

  # FAIRE UNE BALLE POUR AJOUTER A LA LISTE
  void instantiate_balle(game* game, balle* balle_base, couple* pos, couple* dir, int est_joueur) {
    balle b;
    b.hitbox = new_couple(balle_base -> hitbox.w, balle_base -> hitbox.h);
    b.vitesse = balle_base -> vitesse;
    b.damage = balle_base -> damage;
    b.image = balle_base -> image;

    b.pos = pos;
    b.dir = dir;
    b.est_joueur = est_joueur;

    ajouter_balle_file(game.balles, balle);
    # ou just game? prendre .balles dans la fonction?
  }

"interactions?"
  fonction pour avoir touches
  # regarder touches pressées
  # (dir à 0)
  # en fonction de ça on modifie le dir (ou avec 0 si rien)
  # appel fonction bouger plus tard

  void move_pos(couple pos*, couple dir*) { # utiliser dir pour changer de dir à chaque frame et update dir en fonction des touches
    pos -> x += dir -> x;
    if (pos -> x < 0 || pos -> x > ECRAN_W) {
        pos -> x -= dir -> x;
    }
    pos -> y += dir -> y;
    if (pos -> y < 0 || pos -> y > ECRAN_H) {
        pos -> y -= dir -> y;
    }
  }

"main"
#include <time.h>
#define FPS 25
#define NANOS_PAR_S 1000000000
#define MILLIS 1000000
int debut, fin;
int diff;
float tpf; /* temps par frame */
tpf = (1.0 * NANOS_PAR_S) / FPS;
clock_gettime(CLOCK_REALTIME, &debut ); /* gérer si -1 */
(trucs)
clock_gettime(CLOCK_REALTIME, &fin );
diff = fin - debut;
printf("temps:\t\t%d\tsoit%f%\nsur\t\t%d\n", diff, tpf, tpf/(diff*1.0));
if (diff < tpf) {
  MLV_wait_milliseconds(diff / MILLIS); /* pour avoir en millisecondes */
}

### TYPES D'EVENEMENTS ###

déplacement
  #define UP_J1 MLV_KEYBOARD_UP
  #define DOWN_J1 MLV_KEYBOARD_DOWN
  #define LEFT_J1 MLV_KEYBOARD_LEFT
  #define RIGHT_J1 MLV_KEYBOARD_RIGHT

  #define UP_J2 MLV_KEYBOARD_z
  #define DOWN_J2 MLV_KEYBOARD_s
  #define LEFT_J2 MLV_KEYBOARD_q
  #define RIGHT_J2 MLV_KEYBOARD_d

  MLV_get_keyboard_state
tir
  #define TIR_J1 MLV_KEYBOARD_KP0
  #define TIR_J2 MLV_KEYBOARD_SPACE
  touche appuyée (1 frame)
  touche continuellement appuyée
pause
  #define PAUSE MLV_KEYBOARD_ESCAPE

### MISC ###

loop collisions:
  si dans grille autour d'entité
    si balle ou ennemi
      mettre à 0 dans la file si la balle est dead
  appeler fonction réorganiser la file

# mettre format avec division et modulo dans un fichier binaire pour l'état?
# afficher petite icône arme sur le côté?

# directement struct entité (transform et hitbox)?

### QUESTIONS ###
# mieux de faire un struct couple pour hitboxs et pos et dir? ou chacun?
# mettre dans un transform?
# menu accessible en jeu? écran titre?
# .h dans dossier spécifique headers?
# possible de tirer et bouger en même temps? sens de "au plus un évènement clavier" (MLV ou touche pressée?)