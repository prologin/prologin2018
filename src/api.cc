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

#include <stdlib.h>

#include "api.hh"
#include "actions.hh"

// global used in interface.cc
Api* api;

Api::Api(GameState* game_state, rules::Player_sptr player)
    : game_state_(game_state),
      player_(player)
{
    api = this;
}


/// Déplace l'agent ``id_agent`` sur la case donnée en paramètre.
erreur Api::deplacer(int id_agent, position dest)
{
    rules::IAction_sptr action(new ActionDeplacer(id_agent, dest, player_->id));

    erreur err;
    if ((err = static_cast<erreur>(action->check(game_state_))) != OK)
        return err;

    actions_.add(action);
    game_state_set(action->apply(game_state_));
    return OK;
}

/// Propulse l'agent ``id_agent`` dans la direction choisie jusqu'à ce qu'il heurte un obstacle, c'est-à-dire soit un mur soit un autre agent. Si au début de la glissade, il y a un autre agent sur une case adjacente dans cette direction, alors cet agent est poussé dans la direction jusqu'à ce qu'il rencontre un obstacle.
erreur Api::glisser(int id_agent, direction dir)
{
    rules::IAction_sptr action(new ActionGlisser(id_agent, dir, player_->id));

    erreur err;
    if ((err = static_cast<erreur>(action->check(game_state_))) != OK)
        return err;

    actions_.add(action);
    game_state_set(action->apply(game_state_));
    return OK;
}

/// Renvoie le type d'une case donnée.
case_type Api::type_case(position pos)
{
    // TODO
    abort();
}

/// Indique si un agent se trouve sur une case donnée. Renvoie faux si la position est invalide.
bool Api::agent_sur_case(position pos)
{
    // TODO
    abort();
}

/// Indique la position de l'agent sur l'iceberg désigné par le numéro ``id_agent``.
position Api::position_agent(int id_agent)
{
    // TODO
    abort();
}

/// Renvoie la liste de tous les agents du joueur désigné par le numéro ``id_joueur``.
std::vector<int> Api::liste_agents(int id_joueur)
{
    // TODO
    abort();
}

/// Renvoie la liste de tous les aliens présents sur l'iceberg.
std::vector<alien_info> Api::liste_aliens()
{
    // TODO
    abort();
}

/// Renvoie la liste des tours où se produisent une rafale.
std::vector<int> Api::liste_rafales()
{
    // TODO
    abort();
}

/// Renvoie la direction des rafales.
direction Api::direction_rafale()
{
    // TODO
    abort();
}

/// Renvoie la liste des actions effectuées par l’adversaire durant son tour, dans l'ordre chronologique.
std::vector<action_hist> Api::historique()
{
    // TODO
    abort();
}

/// Renvoie le score du joueur ``id_joueur``. Renvoie -1 si le joueur est invalide.
int Api::score(int id_joueur)
{
    // TODO
    abort();
}

/// Renvoie votre numéro de joueur.
int Api::moi()
{
    // TODO
    abort();
}

/// Renvoie le numéro de joueur de votre adversaire.
int Api::adversaire()
{
    // TODO
    abort();
}

/// Annule la dernière action. Renvoie ``false`` quand il n'y a pas d'action à annuler ce tour-ci.
bool Api::annuler()
{
    // TODO
    abort();
}

/// Retourne le numéro du tour actuel.
int Api::tour_actuel()
{
    // TODO
    abort();
}

/// Renvoie votre nombre de points d'action restants pour le tour.
int Api::points_action()
{
    // TODO
    abort();
}


