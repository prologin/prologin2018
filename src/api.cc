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

#include <stdlib.h>

#include "actions.hh"
#include "api.hh"

// global used in interface.cc
Api* api;

Api::Api(GameState* game_state, rules::Player_sptr player)
    : game_state_(game_state)
    , player_(player)
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

/// Propulse l'agent ``id_agent`` dans la direction choisie jusqu'à ce qu'il
/// heurte un obstacle, c'est-à-dire soit un mur soit un autre agent.
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

/// L'agent ``id_agent`` pousse tout autre agent se trouvant sur la case
/// adjacente dans la direction indiquée. Ce dernier est propulsé jusqu'à ce
/// qu'il rencontre un obstacle, c'est-à-dire soit un mur soit un autre agent.
erreur Api::pousser(int id_agent, direction dir)
{
    rules::IAction_sptr action(new ActionPousser(id_agent, dir, player_->id));

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
    return game_state_->get_cell_type(pos);
}

/// Indique si un agent se trouve sur une case donnée. Renvoie faux si la
/// position est invalide.
bool Api::agent_sur_case(position pos)
{
    return game_state_->is_agent_on_position(pos);
}

/// Indique si un alien se trouve sur une case donnée. Renvoie faux si la
/// position est invalide.
bool Api::alien_sur_case(position pos)
{
    return game_state_->is_alien_on_position(pos);
}

/// Indique la position de l'agent sur l'iceberg désigné par le numéro
/// ``id_agent`` appartenant au joueur ``id_joueur``.
position Api::position_agent(int id_joueur, int id_agent)
{
    return game_state_->get_agent_position(id_joueur, id_agent);
}

/// Renvoie la description d'un alien en fonction d'une position donnée.
alien_info Api::info_alien(position pos)
{
    return game_state_->get_alien_info(pos);
}

/// Renvoie la liste de tous les aliens présents sur l'iceberg.
std::vector<alien_info> Api::liste_aliens()
{
    return game_state_->get_alien_info();
}

/// Renvoie la liste des tours où se produisent une tempête.
std::vector<int> Api::liste_tempetes()
{
    // TODO
    abort();
}

/// Renvoie la direction des tempêtes.
direction Api::direction_tempete()
{
    // TODO
    abort();
}

/// Renvoie la liste des actions effectuées par l’adversaire durant son tour,
/// dans l'ordre chronologique.
std::vector<action_hist> Api::historique()
{
    return game_state_->get_history(adversaire());
}

/// Renvoie le score du joueur ``id_joueur``. Renvoie -1 si le joueur est
/// invalide.
int Api::score(int id_joueur)
{
    if (id_joueur == moi() || id_joueur == adversaire())
        return game_state_->get_score(id_joueur);
    else
        return -1;
}

/// Renvoie votre numéro de joueur.
int Api::moi()
{
    return player_->id;
}

/// Renvoie le numéro de joueur de votre adversaire.
int Api::adversaire()
{
    return game_state_->opponent(moi());
}

/// Annule la dernière action. Renvoie ``false`` quand il n'y a pas d'action à
/// annuler ce tour-ci.
bool Api::annuler()
{
    if (!game_state_->can_cancel())
        return false;
    actions_.cancel();
    game_state_ = rules::cancel(game_state_);
    return true;
}

/// Retourne le numéro du tour actuel.
int Api::tour_actuel()
{
    return game_state_->get_round();
}

/// Renvoie votre nombre de points d'action restants pour le tour.
int Api::points_action()
{
    return game_state_->get_action_points(moi());
}
