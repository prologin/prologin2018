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

#include "game_state.hh"
#include "constant.hh"

GameState::GameState(std::istream& map_stream, rules::Players_sptr players)
    : rules::GameState()
    , map_(new Map(map_stream))
    , turn_(0)
{
    int nb_player = 0;
    for (auto& player : players->players)
    {
        if (nb_player > 2)
            FATAL("This game does not support more than two players.");
        if (player->type == rules::PLAYER)
        {
            player_info_.emplace(
                std::make_pair(player->id, PlayerInfo(player)));
            player_ids_[nb_player] = player->id;
            nb_player++;
        }
    }
}

rules::GameState* GameState::copy() const
{
    return new GameState(*this);
}

case_type GameState::get_cell_type(position pos) const
{
    return map_->get_cell_type(pos);
}

bool GameState::is_obstacle(position pos) const
{
    return map_->is_wall(pos) || is_agent_on_position(pos);
}

position GameState::get_agent_position(unsigned int player_id,
                                       unsigned int agent_id) const
{
    assert(player_id < 2);
    assert(agent_id < NB_AGENTS);
    return agent_info_[player_id][agent_id];
}

std::pair<int, int> GameState::get_agent_id(position pos) const
{
    for (int player = 0; player < 2; player++)
        for (int agent = 0; agent < NB_AGENTS; agent++)
            if (get_agent_position(player, agent) == pos)
                return std::make_pair(player, agent);
    return std::make_pair(-1, -1);
}

void GameState::set_agent_position(unsigned int player_id,
                                   unsigned int agent_id, position pos)
{
    assert(player_id < 2);
    assert(agent_id < NB_AGENTS);
    agent_info_[player_id][agent_id] = pos;
}

bool GameState::is_agent_on_position(position pos) const
{
    for (int player = 0; player < 2; player++)
        for (int agent = 0; agent < NB_AGENTS; agent++)
            if (get_agent_position(player, agent) == pos)
                return true;
    return false;
}

const std::vector<alien_info>& GameState::get_alien_info() const
{
    return map_->get_alien_info();
}

unsigned int GameState::get_action_points(unsigned int player_id) const
{
    assert(player_info_.count(player_id) != 0);
    return player_info_.at(player_id).get_action_points();
}

void GameState::decrease_action_points(unsigned int player_id,
                                       unsigned int delta)
{
    assert(player_info_.count(player_id) != 0);
    player_info_.at(player_id).decrease_action_points(delta);
}

void GameState::reset_action_points(unsigned int player_id)
{
    assert(player_info_.count(player_id) != 0);
    player_info_.at(player_id).reset_action_points();
}

unsigned int GameState::opponent(unsigned int player) const
{
    return (player_ids_[0] == player) ? player_ids_[1] : player_ids_[0];
}

unsigned int GameState::get_score(unsigned int player_id) const
{
    assert(player_info_.count(player_id) != 0);
    return player_info_.at(player_id).get_score();
}

void GameState::increase_score(unsigned int player_id, unsigned int delta)
{
    assert(player_info_.count(player_id) != 0);
    player_info_.at(player_id).increase_score(delta);
}

void GameState::increment_turn()
{
    turn_++;
}

unsigned int GameState::get_turn() const
{
    return turn_;
}

bool GameState::is_finished() const
{
    return turn_ > NB_TOURS;
}

const std::vector<action_hist>&
GameState::get_history(unsigned int player_id) const
{
    assert(player_info_.count(player_id) != 0);
    return player_info_.at(player_id).get_actions();
}

void GameState::reset_history(unsigned int player_id)
{
    assert(player_info_.count(player_id) != 0);
    player_info_.at(player_id).reset_actions();
}

void GameState::add_to_history(unsigned int player_id, action_hist action)
{
    assert(player_info_.count(player_id) != 0);
    player_info_.at(player_id).add_action(action);
}
