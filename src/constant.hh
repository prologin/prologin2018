// SPDX-License-Identifier: GPL-2.0-or-later
/*
** This file is part of Prologin2018, a rules library for stechec2.
**
** Copyright (c) 2018 Association Prologin <info@prologin.org>
**
** Prologin2018 is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Prologin2018.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONSTANT_HH_
#define CONSTANT_HH_

#include <functional> // needed for std::hash

/// Taille de l'iceberg (longueur et largeur).
#define TAILLE_ICEBERG 31

/// Nombre de tours à jouer avant la fin de la partie.
#define NB_TOURS 100

/// Nombre de points d'action par tour.
#define NB_POINTS_ACTION 10

/// Nombre de point d'action que coûte un déplacement.
#define COUT_DEPLACEMENT 1

/// Nombre de points d'action que coûte une glissade.
#define COUT_GLISSADE 3

/// Nombre de points d'action nécessaires pour pousser un agent.
#define COUT_POUSSER 4

/// Nombre d'agents par joueur.
#define NB_AGENTS 4

/// Nombre de tours nécessaires pour capturer un objectif.
#define NB_TOURS_CAPTURE 3

/// Types de cases
typedef enum case_type {
    LIBRE,  /* <- Case libre */
    MUR,    /* <- Mur */
    ERREUR, /* <- Erreur */
} case_type;
// This is needed for old compilers
namespace std
{
template <> struct hash<case_type>
{
    size_t operator()(const case_type& v) const
    {
        return hash<int>()(static_cast<int>(v));
    }
};
}

/// Points cardinaux
typedef enum direction {
    NORD,  /* <- Direction : nord */
    EST,   /* <- Direction : est */
    SUD,   /* <- Direction : sud */
    OUEST, /* <- Direction : ouest */
} direction;
// This is needed for old compilers
namespace std
{
template <> struct hash<direction>
{
    size_t operator()(const direction& v) const
    {
        return hash<int>()(static_cast<int>(v));
    }
};
}

/// Erreurs possibles
typedef enum erreur {
    OK,                /* <- L'action s'est effectuée avec succès. */
    PA_INSUFFISANTS,   /* <- Vous ne possédez pas assez de points d'action pour
                          réaliser cette action. */
    POSITION_INVALIDE, /* <- La position spécifiée n'est pas sur l'iceberg. */
    OBSTACLE_MUR,      /* <- La position spécifiée est un mur. */
    OBSTACLE_AGENT,    /* <- La position spécifiée est un agent. */
    DIRECTION_INVALIDE, /* <- La direction spécifiée n'existe pas. */
    ID_AGENT_INVALIDE,  /* <- L'agent spécifié n'existe pas. */
    ID_JOUEUR_INVALIDE, /* <- Le joueur spécifié n'existe pas. */
    RIEN_A_POUSSER, /* <- Aucun agent à pousser dans la direction indiquée. */
    DRAPEAU_INVALIDE, /* <- Le drapeau spécifié n'existe pas. */
} erreur;
// This is needed for old compilers
namespace std
{
template <> struct hash<erreur>
{
    size_t operator()(const erreur& v) const
    {
        return hash<int>()(static_cast<int>(v));
    }
};
}

/// Types d'actions
typedef enum action_type {
    ACTION_DEPLACER, /* <- Action ``deplacer`` */
    ACTION_GLISSER,  /* <- Action ``glisser`` */
    ACTION_POUSSER,  /* <- Action ``pousser`` */
} action_type;
// This is needed for old compilers
namespace std
{
template <> struct hash<action_type>
{
    size_t operator()(const action_type& v) const
    {
        return hash<int>()(static_cast<int>(v));
    }
};
}

/// Types de drapeaux de débug
typedef enum debug_drapeau {
    AUCUN_DRAPEAU, /* <- Aucun drapeau, enlève le drapeau présent */
    DRAPEAU_BLEU,  /* <- Drapeau bleu */
    DRAPEAU_VERT,  /* <- Drapeau vert */
    DRAPEAU_ROUGE, /* <- Drapeau rouge */
} debug_drapeau;
// This is needed for old compilers
namespace std
{
template <> struct hash<debug_drapeau>
{
    size_t operator()(const debug_drapeau& v) const
    {
        return hash<int>()(static_cast<int>(v));
    }
};
}

/// Position sur l'iceberg, donnée par deux coordonnées.
typedef struct position
{
    int ligne;   /* <- Coordonnée : ligne */
    int colonne; /* <- Coordonnée : colonne */
} position;

/// Alien à capturer durant la mission.
typedef struct alien_info
{
    position pos;  /* <- Position de l'alien */
    int puissance; /* <- Nombre de points obtenus pour la capture de cet alien
                      */
    int tour_invasion;  /* <- Tour où l'alien débarque sur la banquise */
    int duree_invasion; /* <- Nombre de tours où l'alien reste sur la banquise
                           */
    int capture_en_cours; /* <- Nombre de tours de la capture en cours, l'alien
                                est considéré comme capturé si la variable
                                atteint NB_TOURS_CAPTURE */
} alien_info;

/// Action représentée dans l'historique.
typedef struct action_hist
{
    action_type type; /* <- Type de l'action */
    int id_agent;     /* <- Numéro de l'agent concerné par l'action */
    direction dir;    /* <- Direction visée par l'agent durant l'action */
} action_hist;

#endif // !CONSTANT_HH_
