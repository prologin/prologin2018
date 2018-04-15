=======================
Instructions de mission
=======================

-------
Iceberg
-------

L'invasion alien se déroulera sur un iceberg représenté par une grille carrée de
``TAILLE_ICEBERG`` cases de côté.

.. image:: ../subject/img/map.png

Cases
=====

Chaque case de l'iceberg est soit libre, soit un mur de glace. Les murs sont des
obstacles et bloquent tout déplacement sur la case.

Une case libre peut contenir un alien ainsi qu'un agent. À noter qu'il est
impossible d'avoir plusieurs agents sur une même case.

Agents
======

FIXME: utiliser un autre mot que 'joueur' pour coller au thème ? (ex: recrue)

Les deux recrues PiB ont à leurs dispositions ``NB_AGENTS`` agents. Ces derniers
sont considérés comme des obstacles, et bloquent donc tout déplacement sur la
case.

Aliens
======

Des aliens envahiront l'iceberg à des positions précises de la carte, pendant un
certain nombres de tour. Pour capturer un alien, un agent doit être sur la case
pendant au moins ``NB_TOURS_CAPTURE`` tours, si l'agent se déplace de cette
case, la capture recommence depuis le début.

Les aliens ne sont pas des obstacles, ils ne bloquent donc pas les déplacements
des agents.

FIXME: meilleure justification pour "les aliens ne sont pas des obstacles"

Tempête de neige
================

Durant la partie, des tempêtes de neige viendront perturber les agents en les
emportant dans une direction donnée jusqu'à ce qu'ils rencontrent un obstacle
(un mur ou un autre agent). Sur une même carte, les tempêtes seront toutes dans
la même direction.

---------------------
Déroulement d'un tour
---------------------

Les deux joueurs se voient attribuer ``NB_POINTS_ACTION`` au début de chaque
tour. Le joueur peut dépenser ses points d'action comme il le souhaite sur ses
différents agents. Ces points ne sont utilisables que durant ce tour et vous
permettent d'effectuer les actions ci-dessous.

Actions
=======

Déplacer
--------

Vous pouvez déplacer un agent d'une case dans la direction de votre choix. Cette
action vous coûte ``COUT_DEPLACEMENT`` points d'action.

Glisser
-------

Un agent peut glisser sur l'iceberg dans une certaine direction, ce qui le
propulse jusqu'à ce qu'il heurte un obstacle (un autre agent ou un mur).
L'action coûte ``COUT_GLISSADE`` points d'action.

Pousser
-------

Il est possible de pousser un autre agent si ce dernier est sur une case
adjacente à l'un de vos propres agents. Le pousser dans une direction le fait
glisser jusqu'à ce qu'il rencontre un obstacle. Pousser un agent coûte
``COUT_POUSSER`` points d'action.

Débug
-----

Pour vous permettre de débugger votre intelligence artificielle, il est possible
de placer des drapeaux de débug sur la carte que vous pourrez ainsi voir dans
l'interface de jeu. Cette action ne coûte aucun point d'action.

Score
=====

Chaque alien capturé vous rapporte un certain nombre de points en fonction de
l'alien. La recrue ayant accumulé le plus de points à la fin de la partie sera
déclarée vainqueure.

Format de la carte
==================

La carte de l'iceberg est représentée dans un fichier texte qui suit le format
suivant :

::

  iceberg ASCII
  positions depart agents joueur 1
  positions depart agents joueur 2
  description aliens
  description tempetes

La représentation ASCII de l'iceberg est constituée de ``.`` pour une case libre
et ``X`` pour un mur.

Pour chaque joueur, ``NB_AGENTS`` lignes indiquent la position de départ d'un
agent sous la forme ``ligne colonne``.

La description des aliens commencent par un nombre sur une seule ligne indiquant
le nombre d'aliens qui envahiront l'iceberg durant la partie. Chaque ligne
précise ensuite les caractéristiques d'un alien :
``position_ligne position_colonne points_capture tour_invasion duree_invasion``

Enfin, la description des tempêtes indique sur la première ligne le nombre de
tempêtes durant la partie, puis sur une même ligne les tours où chaque tempête a
lieu. La dernière ligne précise la direction des tempêtes (toutes les tempêtes
sont dans une même direction).
