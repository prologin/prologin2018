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

#ifndef API_HH_
#define API_HH_

#include <rules/actions.hh>
#include <rules/game-state.hh>
#include <rules/player.hh>
#include <vector>

#include "constant.hh"
#include "game_state.hh"

/*!
** The methods of this class are exported through 'interface.cc'
** to be called by the clients
*/
class Api
{

public:
    Api(GameState* game_state, rules::Player_sptr player);
    virtual ~Api() {}

    const rules::Player_sptr player() const { return player_; }
    void player_set(rules::Player_sptr player) { player_ = player; }

    rules::Actions* actions() { return &actions_; }

    const GameState* game_state() const { return game_state_; }
    GameState* game_state() { return game_state_; }
    void game_state_set(rules::GameState* gs)
    {
        game_state_ = dynamic_cast<GameState*>(gs);
    }

private:
    GameState* game_state_;
    rules::Player_sptr player_;
    rules::Actions actions_;

public:
    /// Déplace l'agent ``id_agent`` sur la case donnée en paramètre.
    erreur deplacer(int id_agent, position dest);

    /// Propulse l'agent ``id_agent`` dans la direction choisie jusqu'à ce qu'il
    /// heurte un obstacle, c'est-à-dire soit un mur soit un autre agent. Si au
    /// début de la glissade, il y a un autre agent sur une case adjacente dans
    /// cette direction, alors cet agent est poussé dans la direction jusqu'à ce
    /// qu'il rencontre un obstacle.
    erreur glisser(int id_agent, direction dir);

    /// Renvoie le type d'une case donnée.
    case_type type_case(position pos);

    /// Indique si un agent se trouve sur une case donnée. Renvoie faux si la
    /// position est invalide.
    bool agent_sur_case(position pos);

    /// Indique la position de l'agent sur l'iceberg désigné par le numéro
    /// ``id_agent``.
    position position_agent(int id_agent);

    /// Renvoie la liste de tous les agents du joueur désigné par le numéro
    /// ``id_joueur``.
    std::vector<int> liste_agents(int id_joueur);

    /// Renvoie la liste de tous les aliens présents sur l'iceberg.
    std::vector<alien_info> liste_aliens();

    /// Renvoie la liste des tours où se produisent une rafale.
    std::vector<int> liste_rafales();

    /// Renvoie la direction des rafales.
    direction direction_rafale();

    /// Renvoie la liste des actions effectuées par l’adversaire durant son
    /// tour, dans l'ordre chronologique.
    std::vector<action_hist> historique();

    /// Renvoie le score du joueur ``id_joueur``. Renvoie -1 si le joueur est
    /// invalide.
    int score(int id_joueur);

    /// Renvoie votre numéro de joueur.
    int moi();

    /// Renvoie le numéro de joueur de votre adversaire.
    int adversaire();

    /// Annule la dernière action. Renvoie ``false`` quand il n'y a pas d'action
    /// à annuler ce tour-ci.
    bool annuler();

    /// Retourne le numéro du tour actuel.
    int tour_actuel();

    /// Renvoie votre nombre de points d'action restants pour le tour.
    int points_action();
};

#endif /* !API_HH_ */
