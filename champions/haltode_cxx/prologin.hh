// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2018 Association Prologin <info@prologin.org>

/// This file has been generated, if you wish to
/// modify it in a permanent way, please refer
/// to the script file : gen/generator_cxx.rb

#ifndef PROLOGIN_HH_
#define PROLOGIN_HH_

#include <functional>

#include <string>

#include <vector>

/// Taille de la banquise (longueur et largeur).
#define TAILLE_BANQUISE 25

/// Nombre de tours à jouer avant la fin de la partie.
#define NB_TOURS 100

/// Nombre de points d'action par tour par agent.
#define NB_POINTS_ACTION 8

/// Nombre de point d'action que coûte un déplacement.
#define COUT_DEPLACEMENT 1

/// Nombre de points d'action que coûte une glissade.
#define COUT_GLISSADE 3

/// Nombre de points d'action nécessaires pour pousser un agent.
#define COUT_POUSSER 5

/// Nombre d'agents par joueur.
#define NB_AGENTS 4

/// Nombre de tours nécessaires pour capturer un alien.
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
    OK,              /* <- L'action s'est effectuée avec succès. */
    PA_INSUFFISANTS, /* <- Votre agent ne possède pas assez de points d'action
                        pour réaliser cette action. */
    POSITION_INVALIDE, /* <- La position spécifiée n'est pas sur la banquise. */
    OBSTACLE_MUR,      /* <- La position spécifiée est un mur. */
    OBSTACLE_AGENT,    /* <- La position spécifiée est un agent. */
    DEPLACEMENT_HORS_LIMITES, /* <- Ce déplacement fait sortir un agent des
                                 limites de la banquise. */
    DIRECTION_INVALIDE,       /* <- La direction spécifiée n'existe pas. */
    ID_AGENT_INVALIDE,        /* <- L'agent spécifié n'existe pas. */
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

/// Position sur la banquise, donnée par deux coordonnées.
typedef struct position
{
    int ligne;   /* <- Coordonnée : ligne */
    int colonne; /* <- Coordonnée : colonne */
} position;

/// Alien à capturer durant la mission.
typedef struct alien_info
{
    position pos;       /* <- Position de l'alien */
    int points_capture; /* <- Nombre de points obtenus pour la capture de cet
                           alien */
    int tour_invasion;  /* <- Tour où l'alien débarque sur la banquise */
    int duree_invasion; /* <- Nombre de tours où l'alien reste sur la banquise
                           */
    int capture_en_cours; /* <- Nombre de tours de la capture en cours, l'alien
                             est considéré comme capturé si la variable atteint
                             NB_TOURS_CAPTURE */
} alien_info;

/// Action de déplacement représentée dans l'historique.
typedef struct action_hist
{
    action_type type; /* <- Type de l'action */
    int id_agent;     /* <- Numéro de l'agent concerné par l'action */
    direction dir; /* <- Direction visée par l'agent durant le déplacement */
} action_hist;

/// Déplace l'agent ``id_agent`` d'une case dans la direction choisie.
extern "C" erreur api_deplacer(int id_agent, direction dir);
static inline erreur deplacer(int id_agent, direction dir)
{
    return api_deplacer(id_agent, dir);
}

/// Propulse l'agent ``id_agent`` dans la direction choisie jusqu'à ce qu'il
/// heurte un obstacle, c'est-à-dire soit un mur soit un autre agent.
extern "C" erreur api_glisser(int id_agent, direction dir);
static inline erreur glisser(int id_agent, direction dir)
{
    return api_glisser(id_agent, dir);
}

/// L'agent ``id_agent`` pousse tout autre agent se trouvant sur la case
/// adjacente dans la direction indiquée. Ce dernier est propulsé jusqu'à ce
/// qu'il rencontre un obstacle, c'est-à-dire soit un mur soit un autre agent.
extern "C" erreur api_pousser(int id_agent, direction dir);
static inline erreur pousser(int id_agent, direction dir)
{
    return api_pousser(id_agent, dir);
}

/// Affiche le drapeau spécifié sur la case indiquée.
extern "C" erreur api_debug_afficher_drapeau(position pos,
                                             debug_drapeau drapeau);
static inline erreur debug_afficher_drapeau(position pos, debug_drapeau drapeau)
{
    return api_debug_afficher_drapeau(pos, drapeau);
}

/// Renvoie le plus court chemin entre deux positions de la banquise sous la
/// forme
/// d'une suite de direction à emprunter. Ce chemin ne contient pas de glissade,
/// uniquement des déplacements simples. Si la position est invalide ou que le
/// chemin n'existe pas, le chemin renvoyé est vide.
extern "C" std::vector<direction> api_chemin(position pos1, position pos2);
static inline std::vector<direction> chemin(position pos1, position pos2)
{
    return api_chemin(pos1, pos2);
}

/// Renvoie le type d'une case donnée.
extern "C" case_type api_type_case(position pos);
static inline case_type type_case(position pos)
{
    return api_type_case(pos);
}

/// Renvoie le numéro du joueur à qui appartient l'agent sur la case indiquée.
/// Renvoie -1 s'il n'y a pas d'agent ou si la position est invalide.
extern "C" int api_agent_sur_case(position pos);
static inline int agent_sur_case(position pos)
{
    return api_agent_sur_case(pos);
}

/// Indique si un alien se trouve sur une case donnée. Renvoie vrai si l'alien
/// est en train d'envahir la banquise et qu'il n'a pas encore été capturé.
/// Renvoie faux autremement, ou si la position est invalide.
extern "C" bool api_alien_sur_case(position pos);
static inline bool alien_sur_case(position pos)
{
    return api_alien_sur_case(pos);
}

/// Indique la position de l'agent sur la banquise désigné par le numéro
/// ``id_agent`` appartenant au joueur ``id_joueur``. Si la description de
/// l'agent est incorrecte, la position (-1, -1) est renvoyée.
extern "C" position api_position_agent(int id_joueur, int id_agent);
static inline position position_agent(int id_joueur, int id_agent)
{
    return api_position_agent(id_joueur, id_agent);
}

/// Renvoie la description d'un alien en fonction d'une position donnée. Si
/// l'alien n'est pas présent sur la carte, ou si la position est invalide, tous
/// les membres de la structure ``alien_info`` renvoyée sont initialisés à -1.
extern "C" alien_info api_info_alien(position pos);
static inline alien_info info_alien(position pos)
{
    return api_info_alien(pos);
}

/// Renvoie la liste de tous les aliens présents durant la partie.
extern "C" std::vector<alien_info> api_liste_aliens();
static inline std::vector<alien_info> liste_aliens()
{
    return api_liste_aliens();
}

/// Renvoie la liste des actions effectuées par l’adversaire durant son tour,
/// dans l'ordre chronologique. Les actions de débug n'apparaissent pas dans
/// cette liste.
extern "C" std::vector<action_hist> api_historique();
static inline std::vector<action_hist> historique()
{
    return api_historique();
}

/// Renvoie le score du joueur ``id_joueur``. Renvoie -1 si le joueur est
/// invalide.
extern "C" int api_score(int id_joueur);
static inline int score(int id_joueur)
{
    return api_score(id_joueur);
}

/// Renvoie votre numéro de joueur.
extern "C" int api_moi();
static inline int moi()
{
    return api_moi();
}

/// Renvoie le numéro de joueur de votre adversaire.
extern "C" int api_adversaire();
static inline int adversaire()
{
    return api_adversaire();
}

/// Annule la dernière action. Renvoie faux quand il n'y a pas d'action à
/// annuler ce tour-ci.
extern "C" bool api_annuler();
static inline bool annuler()
{
    return api_annuler();
}

/// Retourne le numéro du tour actuel.
extern "C" int api_tour_actuel();
static inline int tour_actuel()
{
    return api_tour_actuel();
}

/// Renvoie le nombre de points d'action de l'agent ``id_agent`` restants pour
/// le tour. Si le numéro d'agent est invalide, la fonction renvoie -1.
extern "C" int api_points_action_agent(int id_agent);
static inline int points_action_agent(int id_agent)
{
    return api_points_action_agent(id_agent);
}

/// Affiche le contenu d'une valeur de type case_type
extern "C" void api_afficher_case_type(case_type v);
static inline void afficher_case_type(case_type v)
{
    api_afficher_case_type(v);
}

/// Affiche le contenu d'une valeur de type direction
extern "C" void api_afficher_direction(direction v);
static inline void afficher_direction(direction v)
{
    api_afficher_direction(v);
}

/// Affiche le contenu d'une valeur de type erreur
extern "C" void api_afficher_erreur(erreur v);
static inline void afficher_erreur(erreur v)
{
    api_afficher_erreur(v);
}

/// Affiche le contenu d'une valeur de type action_type
extern "C" void api_afficher_action_type(action_type v);
static inline void afficher_action_type(action_type v)
{
    api_afficher_action_type(v);
}

/// Affiche le contenu d'une valeur de type debug_drapeau
extern "C" void api_afficher_debug_drapeau(debug_drapeau v);
static inline void afficher_debug_drapeau(debug_drapeau v)
{
    api_afficher_debug_drapeau(v);
}

/// Affiche le contenu d'une valeur de type position
extern "C" void api_afficher_position(position v);
static inline void afficher_position(position v)
{
    api_afficher_position(v);
}

/// Affiche le contenu d'une valeur de type alien_info
extern "C" void api_afficher_alien_info(alien_info v);
static inline void afficher_alien_info(alien_info v)
{
    api_afficher_alien_info(v);
}

/// Affiche le contenu d'une valeur de type action_hist
extern "C" void api_afficher_action_hist(action_hist v);
static inline void afficher_action_hist(action_hist v)
{
    api_afficher_action_hist(v);
}

// Les fonctions suivantes définissent les opérations de comparaison, d'égalité
// et de hachage sur les structures du sujet.

namespace std
{
template <typename T> struct hash<std::vector<T>>
{
    std::size_t operator()(const std::vector<T>& v)
    {
        std::size_t res = v.size();
        for (const auto& e : v)
            res ^= std::hash<T>()(e) + 0x9e3779b9 + (res << 6) + (res >> 2);
        return res;
    }
};
}

inline bool operator==(const position& a, const position& b)
{
    if (a.ligne != b.ligne)
        return false;
    if (a.colonne != b.colonne)
        return false;
    return true;
}

inline bool operator!=(const position& a, const position& b)
{
    if (a.ligne != b.ligne)
        return true;
    if (a.colonne != b.colonne)
        return true;
    return false;
}

inline bool operator<(const position& a, const position& b)
{
    if (a.ligne < b.ligne)
        return true;
    if (a.ligne > b.ligne)
        return false;
    if (a.colonne < b.colonne)
        return true;
    if (a.colonne > b.colonne)
        return false;
    return false;
}

inline bool operator>(const position& a, const position& b)
{
    if (a.ligne > b.ligne)
        return true;
    if (a.ligne < b.ligne)
        return false;
    if (a.colonne > b.colonne)
        return true;
    if (a.colonne < b.colonne)
        return false;
    return false;
}

namespace std
{
template <> struct hash<position>
{
    std::size_t operator()(const position& s)
    {
        std::size_t res = 0;
        res ^= 0x9e3779b9 + (res << 6) + (res >> 2) + std::hash<int>()(s.ligne);
        res ^=
            0x9e3779b9 + (res << 6) + (res >> 2) + std::hash<int>()(s.colonne);
        return res;
    }
};
}

inline bool operator==(const alien_info& a, const alien_info& b)
{
    if (a.pos != b.pos)
        return false;
    if (a.points_capture != b.points_capture)
        return false;
    if (a.tour_invasion != b.tour_invasion)
        return false;
    if (a.duree_invasion != b.duree_invasion)
        return false;
    if (a.capture_en_cours != b.capture_en_cours)
        return false;
    return true;
}

inline bool operator!=(const alien_info& a, const alien_info& b)
{
    if (a.pos != b.pos)
        return true;
    if (a.points_capture != b.points_capture)
        return true;
    if (a.tour_invasion != b.tour_invasion)
        return true;
    if (a.duree_invasion != b.duree_invasion)
        return true;
    if (a.capture_en_cours != b.capture_en_cours)
        return true;
    return false;
}

inline bool operator<(const alien_info& a, const alien_info& b)
{
    if (a.pos < b.pos)
        return true;
    if (a.pos > b.pos)
        return false;
    if (a.points_capture < b.points_capture)
        return true;
    if (a.points_capture > b.points_capture)
        return false;
    if (a.tour_invasion < b.tour_invasion)
        return true;
    if (a.tour_invasion > b.tour_invasion)
        return false;
    if (a.duree_invasion < b.duree_invasion)
        return true;
    if (a.duree_invasion > b.duree_invasion)
        return false;
    if (a.capture_en_cours < b.capture_en_cours)
        return true;
    if (a.capture_en_cours > b.capture_en_cours)
        return false;
    return false;
}

inline bool operator>(const alien_info& a, const alien_info& b)
{
    if (a.pos > b.pos)
        return true;
    if (a.pos < b.pos)
        return false;
    if (a.points_capture > b.points_capture)
        return true;
    if (a.points_capture < b.points_capture)
        return false;
    if (a.tour_invasion > b.tour_invasion)
        return true;
    if (a.tour_invasion < b.tour_invasion)
        return false;
    if (a.duree_invasion > b.duree_invasion)
        return true;
    if (a.duree_invasion < b.duree_invasion)
        return false;
    if (a.capture_en_cours > b.capture_en_cours)
        return true;
    if (a.capture_en_cours < b.capture_en_cours)
        return false;
    return false;
}

namespace std
{
template <> struct hash<alien_info>
{
    std::size_t operator()(const alien_info& s)
    {
        std::size_t res = 0;
        res ^=
            0x9e3779b9 + (res << 6) + (res >> 2) + std::hash<position>()(s.pos);
        res ^= 0x9e3779b9 + (res << 6) + (res >> 2) +
               std::hash<int>()(s.points_capture);
        res ^= 0x9e3779b9 + (res << 6) + (res >> 2) +
               std::hash<int>()(s.tour_invasion);
        res ^= 0x9e3779b9 + (res << 6) + (res >> 2) +
               std::hash<int>()(s.duree_invasion);
        res ^= 0x9e3779b9 + (res << 6) + (res >> 2) +
               std::hash<int>()(s.capture_en_cours);
        return res;
    }
};
}

inline bool operator==(const action_hist& a, const action_hist& b)
{
    if (a.type != b.type)
        return false;
    if (a.id_agent != b.id_agent)
        return false;
    if (a.dir != b.dir)
        return false;
    return true;
}

inline bool operator!=(const action_hist& a, const action_hist& b)
{
    if (a.type != b.type)
        return true;
    if (a.id_agent != b.id_agent)
        return true;
    if (a.dir != b.dir)
        return true;
    return false;
}

inline bool operator<(const action_hist& a, const action_hist& b)
{
    if (a.type < b.type)
        return true;
    if (a.type > b.type)
        return false;
    if (a.id_agent < b.id_agent)
        return true;
    if (a.id_agent > b.id_agent)
        return false;
    if (a.dir < b.dir)
        return true;
    if (a.dir > b.dir)
        return false;
    return false;
}

inline bool operator>(const action_hist& a, const action_hist& b)
{
    if (a.type > b.type)
        return true;
    if (a.type < b.type)
        return false;
    if (a.id_agent > b.id_agent)
        return true;
    if (a.id_agent < b.id_agent)
        return false;
    if (a.dir > b.dir)
        return true;
    if (a.dir < b.dir)
        return false;
    return false;
}

namespace std
{
template <> struct hash<action_hist>
{
    std::size_t operator()(const action_hist& s)
    {
        std::size_t res = 0;
        res ^= 0x9e3779b9 + (res << 6) + (res >> 2) +
               std::hash<action_type>()(s.type);
        res ^=
            0x9e3779b9 + (res << 6) + (res >> 2) + std::hash<int>()(s.id_agent);
        res ^= 0x9e3779b9 + (res << 6) + (res >> 2) +
               std::hash<direction>()(s.dir);
        return res;
    }
};
}

extern "C" {

/// Fonction appelée au début de la partie.
void partie_init();

/// Fonction appelée à chaque tour.
void jouer_tour();

/// Fonction appelée à la fin de la partie.
void partie_fin();
}
#endif
