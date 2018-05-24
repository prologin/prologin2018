// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2018 Association Prologin <info@prologin.org>

/// This file has been generated, if you wish to
/// modify it in a permanent way, please refer
/// to the script file : gen/generator_python.rb

#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <Python.h>
# include <vector>
# include <string>

/// Types de cases
typedef enum case_type {
  LIBRE, /* <- Case libre */
  MUR, /* <- Mur */
  ERREUR, /* <- Erreur */
} case_type;
// This is needed for old compilers
namespace std
{
  template <> struct hash<case_type> {
    size_t operator()(const case_type& v) const {
      return hash<int>()(static_cast<int>(v));
    }
  };
}

/// Points cardinaux
typedef enum direction {
  NORD, /* <- Direction : nord */
  EST, /* <- Direction : est */
  SUD, /* <- Direction : sud */
  OUEST, /* <- Direction : ouest */
} direction;
// This is needed for old compilers
namespace std
{
  template <> struct hash<direction> {
    size_t operator()(const direction& v) const {
      return hash<int>()(static_cast<int>(v));
    }
  };
}

/// Erreurs possibles
typedef enum erreur {
  OK, /* <- L'action s'est effectuée avec succès. */
  PA_INSUFFISANTS, /* <- Votre agent ne possède pas assez de points d'action pour réaliser cette action. */
  POSITION_INVALIDE, /* <- La position spécifiée n'est pas sur l'iceberg. */
  OBSTACLE_MUR, /* <- La position spécifiée est un mur. */
  OBSTACLE_AGENT, /* <- La position spécifiée est un agent. */
  DEPLACEMENT_HORS_LIMITES, /* <- Ce déplacement fait sortir un agent des limites de l'iceberg. */
  DIRECTION_INVALIDE, /* <- La direction spécifiée n'existe pas. */
  ID_AGENT_INVALIDE, /* <- L'agent spécifié n'existe pas. */
  RIEN_A_POUSSER, /* <- Aucun agent à pousser dans la direction indiquée. */
  DRAPEAU_INVALIDE, /* <- Le drapeau spécifié n'existe pas. */
} erreur;
// This is needed for old compilers
namespace std
{
  template <> struct hash<erreur> {
    size_t operator()(const erreur& v) const {
      return hash<int>()(static_cast<int>(v));
    }
  };
}

/// Types d'actions
typedef enum action_type {
  ACTION_DEPLACER, /* <- Action ``deplacer`` */
  ACTION_GLISSER, /* <- Action ``glisser`` */
  ACTION_POUSSER, /* <- Action ``pousser`` */
} action_type;
// This is needed for old compilers
namespace std
{
  template <> struct hash<action_type> {
    size_t operator()(const action_type& v) const {
      return hash<int>()(static_cast<int>(v));
    }
  };
}

/// Types de drapeaux de débug
typedef enum debug_drapeau {
  AUCUN_DRAPEAU, /* <- Aucun drapeau, enlève le drapeau présent */
  DRAPEAU_BLEU, /* <- Drapeau bleu */
  DRAPEAU_VERT, /* <- Drapeau vert */
  DRAPEAU_ROUGE, /* <- Drapeau rouge */
} debug_drapeau;
// This is needed for old compilers
namespace std
{
  template <> struct hash<debug_drapeau> {
    size_t operator()(const debug_drapeau& v) const {
      return hash<int>()(static_cast<int>(v));
    }
  };
}

/// Position sur l'iceberg, donnée par deux coordonnées.
typedef struct position {
  int ligne;  /* <- Coordonnée : ligne */
  int colonne;  /* <- Coordonnée : colonne */
} position;


/// Alien à capturer durant la mission.
typedef struct alien_info {
  position pos;  /* <- Position de l'alien */
  int points_capture;  /* <- Nombre de points obtenus pour la capture de cet alien */
  int tour_invasion;  /* <- Tour où l'alien débarque sur la banquise */
  int duree_invasion;  /* <- Nombre de tours où l'alien reste sur la banquise */
  int capture_en_cours;  /* <- Nombre de tours de la capture en cours, l'alien est considéré comme capturé si la variable atteint NB_TOURS_CAPTURE */
} alien_info;


/// Action de déplacement représentée dans l'historique.
typedef struct action_hist {
  action_type type;  /* <- Type de l'action */
  int id_agent;  /* <- Numéro de l'agent concerné par l'action */
  direction dir;  /* <- Direction visée par l'agent durant le déplacement */
} action_hist;



extern "C" {

/// Déplace l'agent ``id_agent`` d'une case dans la direction choisie.
erreur api_deplacer(int id_agent, direction dir);

/// Propulse l'agent ``id_agent`` dans la direction choisie jusqu'à ce qu'il heurte un obstacle, c'est-à-dire soit un mur soit un autre agent.
erreur api_glisser(int id_agent, direction dir);

/// L'agent ``id_agent`` pousse tout autre agent se trouvant sur la case adjacente dans la direction indiquée. Ce dernier est propulsé jusqu'à ce qu'il rencontre un obstacle, c'est-à-dire soit un mur soit un autre agent.
erreur api_pousser(int id_agent, direction dir);

/// Affiche le drapeau spécifié sur la case indiquée.
erreur api_debug_afficher_drapeau(position pos, debug_drapeau drapeau);

/// Renvoie le plus court chemin entre deux positions de l'iceberg sous la forme d'une suite de direction à emprunter. Ce chemin ne contient pas de glissade, uniquement des déplacements simples. Si la position est invalide ou que le chemin n'existe pas, le chemin renvoyé est vide.
std::vector<direction> api_chemin(position pos1, position pos2);

/// Renvoie le type d'une case donnée.
case_type api_type_case(position pos);

/// Renvoie le numéro du joueur à qui appartient l'agent sur la case indiquée. Renvoie -1 s'il n'y a pas d'agent ou si la position est invalide.
int api_agent_sur_case(position pos);

/// Indique si un alien se trouve sur une case donnée. Renvoie vrai si l'alien est en train d'envahir l'iceberg et qu'il n'a pas encore été capturé. Renvoie faux autremement, ou si la position est invalide.
bool api_alien_sur_case(position pos);

/// Indique la position de l'agent sur l'iceberg désigné par le numéro ``id_agent`` appartenant au joueur ``id_joueur``. Si la description de l'agent est incorrecte, la position (-1, -1) est renvoyée.
position api_position_agent(int id_joueur, int id_agent);

/// Renvoie la description d'un alien en fonction d'une position donnée. Si l'alien n'est pas présent sur la carte, ou si la position est invalide, tous les membres de la structure ``alien_info`` renvoyée sont initialisés à -1.
alien_info api_info_alien(position pos);

/// Renvoie la liste de tous les aliens présents durant la partie.
std::vector<alien_info> api_liste_aliens();

/// Renvoie la liste des actions effectuées par l’adversaire durant son tour, dans l'ordre chronologique. Les actions de débug n'apparaissent pas dans cette liste.
std::vector<action_hist> api_historique();

/// Renvoie le score du joueur ``id_joueur``. Renvoie -1 si le joueur est invalide.
int api_score(int id_joueur);

/// Renvoie votre numéro de joueur.
int api_moi();

/// Renvoie le numéro de joueur de votre adversaire.
int api_adversaire();

/// Annule la dernière action. Renvoie faux quand il n'y a pas d'action à annuler ce tour-ci.
bool api_annuler();

/// Retourne le numéro du tour actuel.
int api_tour_actuel();

/// Renvoie le nombre de points d'action de l'agent ``id_agent`` restants pour le tour. Si le numéro d'agent est invalide, la fonction renvoie -1.
int api_points_action_agent(int id_agent);

/// Affiche le contenu d'une valeur de type case_type
void api_afficher_case_type(case_type v);

/// Affiche le contenu d'une valeur de type direction
void api_afficher_direction(direction v);

/// Affiche le contenu d'une valeur de type erreur
void api_afficher_erreur(erreur v);

/// Affiche le contenu d'une valeur de type action_type
void api_afficher_action_type(action_type v);

/// Affiche le contenu d'une valeur de type debug_drapeau
void api_afficher_debug_drapeau(debug_drapeau v);

/// Affiche le contenu d'une valeur de type position
void api_afficher_position(position v);

/// Affiche le contenu d'une valeur de type alien_info
void api_afficher_alien_info(alien_info v);

/// Affiche le contenu d'une valeur de type action_hist
void api_afficher_action_hist(action_hist v);

}

#endif // !INTERFACE_HH_
