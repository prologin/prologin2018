# coding: iso-8859-1
from _api import *

# Taille de l'iceberg (longueur et largeur).
TAILLE_ICEBERG = 25

# Nombre de tours à jouer avant la fin de la partie.
NB_TOURS = 100

# Nombre de points d'action par tour par agent.
NB_POINTS_ACTION = 8

# Nombre de point d'action que coûte un déplacement.
COUT_DEPLACEMENT = 1

# Nombre de points d'action que coûte une glissade.
COUT_GLISSADE = 3

# Nombre de points d'action nécessaires pour pousser un agent.
COUT_POUSSER = 5

# Nombre d'agents par joueur.
NB_AGENTS = 4

# Nombre de tours nécessaires pour capturer un objectif.
NB_TOURS_CAPTURE = 3


from enum import IntEnum

# Types de cases
class case_type(IntEnum):
    LIBRE = 0  # <- Case libre
    MUR = 1  # <- Mur
    ERREUR = 2  # <- Erreur


# Points cardinaux
class direction(IntEnum):
    NORD = 0  # <- Direction : nord
    EST = 1  # <- Direction : est
    SUD = 2  # <- Direction : sud
    OUEST = 3  # <- Direction : ouest


# Erreurs possibles
class erreur(IntEnum):
    OK = 0  # <- L'action s'est effectuée avec succès.
    PA_INSUFFISANTS = 1  # <- Votre agent ne possède pas assez de points d'action pour réaliser cette action.
    POSITION_INVALIDE = 2  # <- La position spécifiée n'est pas sur l'iceberg.
    OBSTACLE_MUR = 3  # <- La position spécifiée est un mur.
    OBSTACLE_AGENT = 4  # <- La position spécifiée est un agent.
    DEPLACEMENT_HORS_LIMITES = 5  # <- Ce déplacement fait sortir un agent des limites de l'iceberg.
    DIRECTION_INVALIDE = 6  # <- La direction spécifiée n'existe pas.
    ID_AGENT_INVALIDE = 7  # <- L'agent spécifié n'existe pas.
    RIEN_A_POUSSER = 8  # <- Aucun agent à pousser dans la direction indiquée.
    DRAPEAU_INVALIDE = 9  # <- Le drapeau spécifié n'existe pas.


# Types d'actions
class action_type(IntEnum):
    ACTION_DEPLACER = 0  # <- Action ``deplacer``
    ACTION_GLISSER = 1  # <- Action ``glisser``
    ACTION_POUSSER = 2  # <- Action ``pousser``


# Types de drapeaux de débug
class debug_drapeau(IntEnum):
    AUCUN_DRAPEAU = 0  # <- Aucun drapeau, enlève le drapeau présent
    DRAPEAU_BLEU = 1  # <- Drapeau bleu
    DRAPEAU_VERT = 2  # <- Drapeau vert
    DRAPEAU_ROUGE = 3  # <- Drapeau rouge


from collections import namedtuple

# Position sur l'iceberg, donnée par deux coordonnées.

# Alien à capturer durant la mission.
alien_info = namedtuple("alien_info",
    'pos ' # <- Position de l'alien
    'points_capture ' # <- Nombre de points obtenus pour la capture de cet alien
    'tour_invasion ' # <- Tour où l'alien débarque sur la banquise
    'duree_invasion ' # <- Nombre de tours où l'alien reste sur la banquise
    'capture_en_cours ' # <- Nombre de tours de la capture en cours, l'alien est considéré comme capturé si la variable atteint NB_TOURS_CAPTURE
)


# Action de déplacement représentée dans l'historique.
action_hist = namedtuple("action_hist",
    'type ' # <- Type de l'action
    'id_agent ' # <- Numéro de l'agent concerné par l'action
    'dir ' # <- Direction visée par l'agent durant le déplacement
)


