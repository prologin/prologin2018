/*
** Stechec project is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** The complete GNU General Public Licence Notice can be found as the
** `NOTICE' file in the root directory.
**
** Copyright (C) 2018 Prologin
*/

#ifndef CONSTANT_HH_
# define CONSTANT_HH_

#include <functional> // needed for std::hash

/// Taille de l'iceberg (longueur et largeur).
# define TAILLE_ICEBERG            20

/// Nombre de tours à jouer avant la fin de la partie.
# define NB_TOURS                  100

/// Nombre de points d'action par tour.
# define NB_POINTS_ACTION          10

/// Nombre de points d'action que coûte une glissade.
# define COUT_GLISSADE             3

/// Nombre de point d'action que coûte un déplacement.
# define COUT_DEPLACEMENT          1

/// Nombre d'agents par joueur.
# define NB_AGENTS                 4

/// Nombre de tours nécessaires pour capturer un objectif.
# define NB_TOURS_CAPTURE          3

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
  PA_INSUFFISANTS, /* <- Vous ne possédez pas assez de points d'action pour réaliser cette action. */
  POSITION_INVALIDE, /* <- La position spécifiée n'est pas sur l'iceberg. */
  DIRECTION_INVALIDE, /* <- La direction spécifiée n'existe pas. */
  ID_AGENT_INVALIDE, /* <- L'agent spécifié n'existe pas. */
  ID_JOUEUR_INVALIDE, /* <- Le joueur spécifié n'existe pas. */
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

/// Position sur l'iceberg, donnée par deux coordonnées.
typedef struct position {
  int x;  /* <- Coordonnée en X */
  int y;  /* <- Coordonnée en Y */
} position;


/// Alien à capturer durant la mission.
typedef struct alien_info {
  position pos;  /* <- Position de l'alien */
  int puissance;  /* <- Nombre de points obtenus pour la capture de cet alien */
  int tour_invasion;  /* <- Tour où l'alien débarque sur la banquise */
  int duree_invasion;  /* <- Nombre de tours où l'alien reste sur la banquise */
} alien_info;


/// Action représentée dans l'historique. L'action ``deplacer`` utilise ``id_agent`` et ``dest``. L'action ``glisser`` utilise ``id_agent`` et ``dir``.
typedef struct action_hist {
  action_type type;  /* <- Type de l'action */
  int id_agent;  /* <- Numéro de l'agent concerné par l'action */
  position dest;  /* <- Case de destination lors d'un déplacement de l'agent */
  direction dir;  /* <- Direction visée par l'agent durant une glissade */
} action_hist;



#endif // !CONSTANT_HH_
