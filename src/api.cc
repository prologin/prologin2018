// SPDX-License-Identifier: GPL-2.0-or-later
/*
** This file is part of Prologin2018, a rules library for stechec2.
**
** Copyright (c) 2018 Association Prologin <info@prologin.org>
** Copyright (c) 2018 Thibault Allançon
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

Api::Api(std::unique_ptr<GameState> game_state,
         std::shared_ptr<rules::Player> player)
    : rules::Api<GameState, erreur>(std::move(game_state), player)
{
    api = this;
}

/// Renvoie le nombre de points d'action de l'agent ``id_agent`` restants pour
/// le tour. Si le numéro d'agent est invalide, la fonction renvoie -1.
int Api::points_action_agent(int id_agent)
{
    if (id_agent >= 0 && id_agent < NB_AGENTS)
        return game_state_->get_agent_action_points(moi(), id_agent);
    else
        return -1;
}

/// Renvoie le plus court chemin entre deux positions de la banquise sous la
/// forme
/// d'une suite de direction à emprunter. Ce chemin ne contient pas de glissade,
/// uniquement des déplacements simples. Si la position est invalide ou que le
/// chemin n'existe pas, le chemin renvoyé est vide.
std::vector<direction> Api::chemin(position pos1, position pos2)
{
    return game_state_->get_shortest_path(pos1, pos2);
}

/// Renvoie le type d'une case donnée.
case_type Api::type_case(position pos)
{
    return game_state_->get_cell_type(pos);
}

/// Renvoie le numéro du joueur à qui appartient l'agent sur la case indiquée.
/// Renvoie -1 s'il n'y a pas d'agent ou si la position est invalide.
int Api::agent_sur_case(position pos)
{
    return game_state_->agent_on_position(pos);
}

/// Indique si un alien se trouve sur une case donnée. Renvoie vrai si
/// l'alien est en train d'envahir la banquise et qu'il n'a pas encore été
/// capturé. Renvoie faux autremement, ou si la position est invalide.
bool Api::alien_sur_case(position pos)
{
    return game_state_->is_alien_on_position(pos);
}

/// Indique la position de l'agent sur la banquise désigné par le numéro
/// ``id_agent`` appartenant au joueur ``id_joueur``. Si la description de
/// l'agent est incorrecte, la position (-1, -1) est renvoyée.
position Api::position_agent(int id_joueur, int id_agent)
{
    if ((id_joueur == moi() || id_joueur == adversaire()) && id_agent >= 0 &&
        id_agent < NB_AGENTS)
        return game_state_->get_agent_position(id_joueur, id_agent);
    else
        return {-1, -1};
}

/// Renvoie la description d'un alien en fonction d'une position donnée. Si
/// l'alien n'est pas présent sur la carte, ou si la position est invalide, tous
/// les membres de la structure ``alien_info`` renvoyée sont initialisés à -1.
alien_info Api::info_alien(position pos)
{
    if (game_state_->is_alien_on_position(pos))
        return game_state_->get_alien_info(pos);
    else
        return {{-1, -1}, -1, -1, -1, -1};
}

/// Renvoie la liste de tous les aliens présents durant la partie.
std::vector<alien_info> Api::liste_aliens()
{
    return game_state_->get_alien_info();
}

/// Renvoie la liste des actions effectuées par l’adversaire durant son tour,
/// dans l'ordre chronologique. Les actions de débug n'apparaissent pas dans
/// cette liste.
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

/// Annule la dernière action. Renvoie faux quand il n'y a pas d'action à
/// annuler ce tour-ci.
bool Api::annuler()
{
    if (!game_state_.can_cancel())
        return false;
    actions_.cancel();
    game_state_.cancel();
    return true;
}

/// Retourne le numéro du tour actuel.
int Api::tour_actuel()
{
    return game_state_->get_round();
}
