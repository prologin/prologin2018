

===
API
===

..
   This file was generated using gen/make_sphinx.rsphinx
   Do not modify unless you are absolutely sure of what you are doing

Constantes
==========


.. c:var:: TAILLE_BANQUISE

  :Valeur: 25
  :Description:
    Taille de la banquise (longueur et largeur).

    

.. c:var:: NB_TOURS

  :Valeur: 100
  :Description:
    Nombre de tours à jouer avant la fin de la partie.

    

.. c:var:: NB_POINTS_ACTION

  :Valeur: 8
  :Description:
    Nombre de points d'action par tour par agent.

    

.. c:var:: COUT_DEPLACEMENT

  :Valeur: 1
  :Description:
    Nombre de point d'action que coûte un déplacement.

    

.. c:var:: COUT_GLISSADE

  :Valeur: 3
  :Description:
    Nombre de points d'action que coûte une glissade.

    

.. c:var:: COUT_POUSSER

  :Valeur: 5
  :Description:
    Nombre de points d'action nécessaires pour pousser un agent.

    

.. c:var:: NB_AGENTS

  :Valeur: 4
  :Description:
    Nombre d'agents par joueur.

    

.. c:var:: NB_TOURS_CAPTURE

  :Valeur: 3
  :Description:
    Nombre de tours nécessaires pour capturer un alien.

    


Énumérations
============



.. c:type:: case_type

  :Description:
      Types de cases
  :Valeurs:
    
      :LIBRE:
        Case libre

    
      :MUR:
        Mur

    
      :ERREUR:
        Erreur

    


.. c:type:: direction

  :Description:
      Points cardinaux
  :Valeurs:
    
      :NORD:
        Direction : nord

    
      :EST:
        Direction : est

    
      :SUD:
        Direction : sud

    
      :OUEST:
        Direction : ouest

    


.. c:type:: erreur

  :Description:
      Erreurs possibles
  :Valeurs:
    
      :OK:
        L'action s'est effectuée avec succès.

    
      :PA_INSUFFISANTS:
        Votre agent ne possède pas assez de points d'action pour réaliser cette action.

    
      :POSITION_INVALIDE:
        La position spécifiée n'est pas sur la banquise.

    
      :OBSTACLE_MUR:
        La position spécifiée est un mur.

    
      :OBSTACLE_AGENT:
        La position spécifiée est un agent.

    
      :DEPLACEMENT_HORS_LIMITES:
        Ce déplacement fait sortir un agent des limites de la banquise.

    
      :DIRECTION_INVALIDE:
        La direction spécifiée n'existe pas.

    
      :ID_AGENT_INVALIDE:
        L'agent spécifié n'existe pas.

    
      :RIEN_A_POUSSER:
        Aucun agent à pousser dans la direction indiquée.

    
      :DRAPEAU_INVALIDE:
        Le drapeau spécifié n'existe pas.

    


.. c:type:: action_type

  :Description:
      Types d'actions
  :Valeurs:
    
      :ACTION_DEPLACER:
        Action ``deplacer``

    
      :ACTION_GLISSER:
        Action ``glisser``

    
      :ACTION_POUSSER:
        Action ``pousser``

    


.. c:type:: debug_drapeau

  :Description:
      Types de drapeaux de débug
  :Valeurs:
    
      :AUCUN_DRAPEAU:
        Aucun drapeau, enlève le drapeau présent

    
      :DRAPEAU_BLEU:
        Drapeau bleu

    
      :DRAPEAU_VERT:
        Drapeau vert

    
      :DRAPEAU_ROUGE:
        Drapeau rouge

    


Structures
==========



.. c:type:: position

  .. code-block:: c

    struct position {
        int ligne;
        int colonne;
    };

  :Description: Position sur la banquise, donnée par deux coordonnées.

  :Champs:
    :ligne: Coordonnée : ligne
    :colonne: Coordonnée : colonne
    


.. c:type:: alien_info

  .. code-block:: c

    struct alien_info {
        position pos;
        int points_capture;
        int tour_invasion;
        int duree_invasion;
        int capture_en_cours;
    };

  :Description: Alien à capturer durant la mission.

  :Champs:
    :pos: Position de l'alien
    :points_capture: Nombre de points obtenus pour la capture de cet alien
    :tour_invasion: Tour où l'alien débarque sur la banquise
    :duree_invasion: Nombre de tours où l'alien reste sur la banquise
    :capture_en_cours: Nombre de tours de la capture en cours, l'alien est considéré comme capturé si la variable atteint NB_TOURS_CAPTURE
    


.. c:type:: action_hist

  .. code-block:: c

    struct action_hist {
        action_type atype;
        int id_agent;
        direction dir;
    };

  :Description: Action de déplacement représentée dans l'historique.

  :Champs:
    :atype: Type de l'action
    :id_agent: Numéro de l'agent concerné par l'action
    :dir: Direction visée par l'agent durant le déplacement
    


Fonctions
=========



.. c:function:: erreur deplacer(int id_agent, direction dir)

    Déplace l'agent ``id_agent`` d'une case dans la direction choisie.

    


    

    
      
    :param id_agent: Numéro de l'agent
      
    
      
    :param dir: Direction visée
      
    


  


.. c:function:: erreur glisser(int id_agent, direction dir)

    Propulse l'agent ``id_agent`` dans la direction choisie jusqu'à ce qu'il heurte un obstacle, c'est-à-dire soit un mur soit un autre agent.

    


    

    
      
    :param id_agent: Numéro de l'agent
      
    
      
    :param dir: Direction visée
      
    


  


.. c:function:: erreur pousser(int id_agent, direction dir)

    L'agent ``id_agent`` pousse tout autre agent se trouvant sur la case adjacente dans la direction indiquée. Ce dernier est propulsé jusqu'à ce qu'il rencontre un obstacle, c'est-à-dire soit un mur soit un autre agent.

    


    

    
      
    :param id_agent: Numéro de l'agent
      
    
      
    :param dir: Direction visée
      
    


  


.. c:function:: erreur debug_afficher_drapeau(position pos, debug_drapeau drapeau)

    Affiche le drapeau spécifié sur la case indiquée.

    


    

    
      
    :param pos: Case choisie
      
    
      
    :param drapeau: Drapeau à afficher sur la case
      
    


  


.. c:function:: int points_action_agent(int id_agent)

    Renvoie le nombre de points d'action de l'agent ``id_agent`` restants pour le tour. Si le numéro d'agent est invalide, la fonction renvoie -1.

    


    

    
      
    :param id_agent: Numéro de l'agent
      
    


  


.. c:function:: direction array chemin(position pos1, position pos2)

    Renvoie le plus court chemin entre deux positions de la banquise sous la forme d'une suite de direction à emprunter. Ce chemin ne contient pas de glissade, uniquement des déplacements simples. Si la position est invalide ou que le chemin n'existe pas, le chemin renvoyé est vide.

    


    

    
      
    :param pos1: Position de départ
      
    
      
    :param pos2: Position d'arrivée
      
    


  


.. c:function:: case_type type_case(position pos)

    Renvoie le type d'une case donnée.

    


    

    
      
    :param pos: Case choisie
      
    


  


.. c:function:: int agent_sur_case(position pos)

    Renvoie le numéro du joueur à qui appartient l'agent sur la case indiquée. Renvoie -1 s'il n'y a pas d'agent ou si la position est invalide.

    


    

    
      
    :param pos: Case choisie
      
    


  


.. c:function:: bool alien_sur_case(position pos)

    Indique si un alien se trouve sur une case donnée. Renvoie vrai si l'alien est en train d'envahir la banquise et qu'il n'a pas encore été capturé. Renvoie faux autremement, ou si la position est invalide.

    


    

    
      
    :param pos: Case choisie
      
    


  


.. c:function:: position position_agent(int id_joueur, int id_agent)

    Indique la position de l'agent sur la banquise désigné par le numéro ``id_agent`` appartenant au joueur ``id_joueur``. Si la description de l'agent est incorrecte, la position (-1, -1) est renvoyée.

    


    

    
      
    :param id_joueur: Numéro du joueur
      
    
      
    :param id_agent: Numéro de l'agent
      
    


  


.. c:function:: alien_info info_alien(position pos)

    Renvoie la description d'un alien en fonction d'une position donnée. Si l'alien n'est pas présent sur la carte, ou si la position est invalide, tous les membres de la structure ``alien_info`` renvoyée sont initialisés à -1.

    


    

    
      
    :param pos: Case choisie
      
    


  


.. c:function:: alien_info array liste_aliens()

    Renvoie la liste de tous les aliens présents durant la partie.

    



  


.. c:function:: action_hist array historique()

    Renvoie la liste des actions effectuées par l’adversaire durant son tour, dans l'ordre chronologique. Les actions de débug n'apparaissent pas dans cette liste.

    



  


.. c:function:: int score(int id_joueur)

    Renvoie le score du joueur ``id_joueur``. Renvoie -1 si le joueur est invalide.

    


    

    
      
    :param id_joueur: Numéro du joueur
      
    


  


.. c:function:: int moi()

    Renvoie votre numéro de joueur.

    



  


.. c:function:: int adversaire()

    Renvoie le numéro de joueur de votre adversaire.

    



  


.. c:function:: bool annuler()

    Annule la dernière action. Renvoie faux quand il n'y a pas d'action à annuler ce tour-ci.

    



  


.. c:function:: int tour_actuel()

    Retourne le numéro du tour actuel.

    



  


Fonctions utilisateur
=====================



.. c:function:: void partie_init()

    Fonction appelée au début de la partie.

    



  


.. c:function:: void jouer_tour()

    Fonction appelée à chaque tour.

    



  


.. c:function:: void partie_fin()

    Fonction appelée à la fin de la partie.

    



  

