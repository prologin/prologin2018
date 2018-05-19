====================
FAQ Penguin in Black
====================

**Quelques conseils avant de poser une question**

1. Lire le sujet
2. Relire le sujet
3. Lire votre code
4. Relire votre code
5. Contacter un orga


Sujet
=====

Pourquoi la fonction ``chemin`` me renvoie-t-elle une liste vide ?
------------------------------------------------------------------

Si la position d'arrivée donnée en paramètre à la fonction ``chemin`` n'est pas
une case libre d'accès (un mur ou un agent) le chemin est considéré comme
invalide et la liste retournée est vide.

Quelle est la différence entre un pingouin et un manchot ?
----------------------------------------------------------

pingouin n.m. : Oiseau marin (alcidé) des régions arctiques, au corps massif,
aux pattes palmées, au bec comprimé et au plumage noir et blanc.

manchot n.m. : Oiseau marin (sphéniscidé) de l'hémisphère austral tout à fait
adapté à la vie aquatique, incapable de voler du fait de la transformation de
l'aile en organe de nage.

(Source : larousse.fr)

GUI
===

**Appuyez sur H avant de poser une question !**

Qui est le "Joueur 1" ?
-----------------------

Les manchots en bleus représentent les agents du joueur 1, tandis que ceux en
rouges les agents du joueur 2.

Pourquoi la GUI bloque l'exécution de mon programme ?
-----------------------------------------------------

Elle est en mode "pause" par défaut, il faut le désactiver en appuyant sur
Espace ou passer manuellement au tour suivant avec les flèches.

Erreurs fréquentes
==================

- Ne pas appeler les fonctions de l'API avant l'appel à ``partie_init``.
- **Ne pas modifier** les fichiers générés (``api.*``, ``interface.*``, ...)
    - Attention, ça ne fera pas d'erreurs en local mais cela ne marchera pas sur
      le serveur (donc pour les tournois).
- Si vous faites des fichiers annexes, n'oubliez pas de les mettre en plus dans
  le makefile après ``prologin.*`` dans ``champion-srcs``.


Problèmes de Java
=================

En Java, certains fichiers générés automatiquement dans vos /home peuvent être
incorrects. Pour les regénérer, utilisez ::

   stechec2-generator player prologin2018 joueur

Cela remplira le dossier "joueur" avec tous les codes à compléter pour tous les
langages. Java devrait marcher dans ces nouveaux fichiers générés.
