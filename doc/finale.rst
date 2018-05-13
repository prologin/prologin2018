=======================
Instructions de mission
=======================

FIXME: ajouter des images de l'interface de jeu (case libre, mur, agents,
aliens, actions, drapeau débug, etc.)

-------
Iceberg
-------

Dans le cadre de votre mission, vous serez envoyé au Pôle Sud, plus exactement
sur cet iceberg, où nos services de renseignements ont indiqué que les premiers
repérages aliens auront lieu. L'iceberg est représenté par une grille carrée de
25 cases de côté.

.. image:: ../subject/img/map.png

Cases
=====

Chaque case de l'iceberg est soit libre, soit un mur de glace. Les murs sont des
obstacles et bloquent tout déplacement sur la case.

Une case libre peut contenir un alien ainsi qu'un agent. À noter qu'il est
impossible d'avoir plusieurs agents ou aliens sur une même case.

Agents
======

Les deux recrues PiB ont à leur disposition quatre agents, numérotés de 0 à 3.
Ces derniers sont considérés comme des obstacles, et bloquent donc tout
déplacement sur la case.

Aliens
======

Des aliens débarqueront sur l'iceberg à des positions précises de la carte,
pendant un certain nombre de tours afin d'accomplir leur mission de
reconnaissance, avant de repartir sur leur planète d'origine. De plus, les
aliens n'envahissent jamais plusieurs fois au même endroit sur l'iceberg.

Pour capturer un alien, un agent doit être sur la case pendant au moins 3 tours.
L'alien capturé disparaît de l'iceberg, et des échantillons d'analyse sont
envoyés instantanément au QG des PiB, l'agent peut donc continuer sa mission.
Si l'agent quitte la case, ne serait-ce qu'un instant (en se déplaçant ou alors
en étant poussé par un agent), la capture devra reprendre de **zéro**.

Les aliens ne sont pas assez habitués à la glace pour se déplacer sur l'iceberg.
Ils se contenteront donc pour leur mission de repérage de rester fixes par
rapport à leurs lieux d'invasion. En revanche, les aliens ne sont pas des
obstacles : faisant des efforts admirables pour éviter les agents -
contrairement aux murs, qui sont davantage récalcitrants - ils se
contorsionneront et esquiveront de leur mieux : ils ne bloquent donc pas le
déplacement des agents.

---------------------
Déroulement d'un tour
---------------------

Il y a 100 tours par partie, numérotés de 0 à 99. Pendant un tour les recrues
jouent alternativement. Les invasions ou désistements aliens ont toujours lieu
en début de tour avant les actions des joueurs. Par exemple, si un alien envahit
l'iceberg au tour 10, pour une durée de 3 tours, alors il sera présent aux tours
10, 11 et 12 et repartira au tout début du tour 13. En revanche, la capture des
aliens se fait toujours à la fin du tour, lorsque les deux recrues ont fini de
jouer.

Tous les agents se voient attribuer 8 points d'action au début de chaque tour.
Ces points ne sont utilisables que durant ce tour et sont spécifiques à un agent
(il est donc impossible de transférer des points d'un agent à un autre). Les
points vous permettent d'effectuer les actions ci-dessous.

Actions
=======

Déplacer
--------

Vous pouvez déplacer un agent vers une case adjacente dans la direction de votre
choix. Cette action coûte 1 point d'action à l'agent.

Glisser
-------

Un agent peut s'élancer fougueusement sur l'iceberg, directement sur le ventre,
dans une certaine direction, ce qui le propulse jusqu'à ce qu'il heurte un
obstacle (un autre agent ou un mur). L'action coûte 3 points d'action.

Pousser
-------

Il est possible de pousser un autre agent si ce dernier est sur une case
adjacente à l'un de vos propres agents. Le pousser dans une direction le fait
glisser jusqu'à ce qu'il rencontre un obstacle. Pousser un agent coûte 5 points
d'action.

À nouveau, les aliens font tout leur possible pour esquiver les agents, vous ne
pouvez donc pas les pousser (ce n'est pas pour rien qu'il faut 3 tours pour les
capturer !).

Débug
-----

Pour vous permettre de débugger votre intelligence artificielle, il est possible
de placer des drapeaux de débug sur la carte que vous pourrez ainsi voir dans
l'interface de jeu. Cette action ne coûte aucun point d'action.

Score
=====

Chaque alien capturé vous rapporte un certain nombre de points en fonction de
l'alien, selon son espèce, le danger brut qu'il représente, et ses opinions
politiques. La recrue ayant accumulé le plus de points à la fin de la partie
rejoindra les rangs des Prologin in Black pour lutter contre les invasions
intergalactiques.

Format de la carte
==================

La carte de l'iceberg est représentée dans un fichier texte qui suit le format
suivant :

::

  iceberg ASCII
  positions depart agents joueur 1
  positions depart agents joueur 2
  description aliens

La représentation ASCII de l'iceberg est constituée de ``.`` pour une case libre
et ``X`` pour un mur.

Pour chaque joueur, quatre lignes, une par agent, indiquent la position de
départ d'un agent sous la forme ``ligne colonne``.

La description des aliens commence par un nombre sur une seule ligne indiquant
le nombre d'aliens qui envahiront l'iceberg durant la partie. Chaque ligne
précise ensuite les caractéristiques d'un alien :
``position_ligne position_colonne points_capture tour_invasion duree_invasion``
