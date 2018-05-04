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

#include <algorithm>
#include <queue>

#include "actions.hh"
#include "constant.hh"
#include "game_state.hh"

GameState::GameState(std::istream& map_stream, rules::Players_sptr players)
    : rules::GameState()
    , map_(new Map(map_stream))
    , round_(0)
{
    int id = 0;
    for (auto& player : players->players)
    {
        if (id > 2)
            FATAL("This game does not support more than two players.");
        if (player->type == rules::PLAYER)
        {
            player_info_.emplace(
                std::make_pair(player->id, PlayerInfo(player, id)));
            player_ids_[id] = player->id;
            id++;
        }
    }

    for (int player = 0; player < 2; player++)
        agent_info_[player] = map_->get_start_position(player);
}

rules::GameState* GameState::copy() const
{
    return new GameState(*this);
}

std::vector<direction> GameState::get_shortest_path(position start,
                                                    position dest) const
{
    std::queue<position> q;
    std::array<std::array<bool, TAILLE_ICEBERG>, TAILLE_ICEBERG> seen{};
    std::array<std::array<direction, TAILLE_ICEBERG>, TAILLE_ICEBERG>
        backtrace{};

    q.push(start);
    while (!q.empty())
    {
        position cur = q.front();
        q.pop();
        if (cur == dest)
        {
            // Extract path from backtrace
            std::vector<direction> path;
            while (cur != start)
            {
                direction dir = backtrace[cur.ligne][cur.colonne];
                path.push_back(dir);
                cur = get_position_offset(cur, opposite_dir(dir));
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (int dir = 0; dir < 4; dir++)
        {
            position next_pos = get_position_offset(cur, (direction)dir);
            if (inside_map(next_pos) &&
                !seen[next_pos.ligne][next_pos.colonne] &&
                !is_obstacle(next_pos))
            {
                seen[next_pos.ligne][next_pos.colonne] = true;
                backtrace[next_pos.ligne][next_pos.colonne] = (direction)dir;
                q.push(next_pos);
            }
        }
    }

    return {};
}

position GameState::slide_end_pos(position start, direction dir) const
{
    position pos = start, next_pos = start;
    do
    {
        pos = next_pos;
        next_pos = get_position_offset(next_pos, dir);
    } while (inside_map(next_pos) && !is_obstacle(next_pos));
    return pos;
}

case_type GameState::get_cell_type(position pos) const
{
    return map_->get_cell_type(pos);
}

bool GameState::is_obstacle(position pos) const
{
    return map_->is_wall(pos) || is_agent_on_position(pos);
}

std::pair<int, int> GameState::get_agent_id(position pos) const
{
    for (auto player : player_ids_)
        for (int agent = 0; agent < NB_AGENTS; agent++)
            if (get_agent_position(player, agent) == pos)
                return std::make_pair(player, agent);
    return std::make_pair(-1, -1);
}

position GameState::get_agent_position(int player_id, int agent_id) const
{
    assert(agent_id >= 0 && agent_id < NB_AGENTS);
    assert(player_info_.count(player_id) != 0);

    int internal_player_id = player_info_.at(player_id).get_internal_id();
    return agent_info_[internal_player_id][agent_id];
}

void GameState::set_agent_position(int player_id, int agent_id, position pos)
{
    assert(agent_id >= 0 && agent_id < NB_AGENTS);
    assert(player_info_.count(player_id) != 0);

    int internal_player_id = player_info_.at(player_id).get_internal_id();
    position old_pos = agent_info_[internal_player_id][agent_id];
    agent_info_[internal_player_id][agent_id] = pos;

    if (old_pos != pos && is_alien_on_position(old_pos))
        reset_alien_capture_time(old_pos);
}

int GameState::agent_on_position(position pos) const
{
    for (auto player : player_ids_)
        for (int agent = 0; agent < NB_AGENTS; agent++)
            if (get_agent_position(player, agent) == pos)
                return player;
    return -1;
}

bool GameState::is_agent_on_position(position pos) const
{
    return agent_on_position(pos) != -1;
}

bool GameState::is_alien_on_position(position pos) const
{
    return map_->is_alien_on_position(pos);
}

std::vector<alien_info> GameState::get_alien_info() const
{
    return map_->get_alien_info();
}

alien_info GameState::get_alien_info(position pos) const
{
    return map_->get_alien_info(pos);
}

void GameState::reset_alien_capture_time(position pos)
{
    map_->reset_alien_capture_time(pos);
}

void GameState::check_presence_alien()
{
    map_->check_presence_alien(round_);
}

void GameState::update_scores()
{
    for (auto player : player_ids_)
    {
        for (int agent = 0; agent < NB_AGENTS; agent++)
        {
            position agent_pos = get_agent_position(player, agent);
            if (is_alien_on_position(agent_pos))
            {
                map_->increment_alien_capture_time(agent_pos);
                alien_info alien = map_->get_alien_info(agent_pos);
                if (alien.capture_en_cours == NB_TOURS_CAPTURE)
                    increase_score(player, alien.points_capture);
            }
        }
    }
}

int GameState::get_agent_action_points(int player_id, int agent_id) const
{
    assert(player_info_.count(player_id) != 0);
    return player_info_.at(player_id).get_agent_action_points(agent_id);
}

void GameState::decrease_agent_action_points(int player_id, int agent_id,
                                             int delta)
{
    assert(player_info_.count(player_id) != 0);
    player_info_.at(player_id).decrease_agent_action_points(agent_id, delta);
}

void GameState::reset_action_points(int player_id)
{
    assert(player_info_.count(player_id) != 0);
    player_info_.at(player_id).reset_action_points();
}

int GameState::opponent(int player) const
{
    return (player_ids_[0] == player) ? player_ids_[1] : player_ids_[0];
}

int GameState::get_score(int player_id) const
{
    assert(player_info_.count(player_id) != 0);
    return player_info_.at(player_id).get_score();
}

void GameState::increase_score(int player_id, int delta)
{
    assert(player_info_.count(player_id) != 0);
    player_info_.at(player_id).increase_score(delta);
}

void GameState::increment_round()
{
    round_++;
}

int GameState::get_round() const
{
    return round_;
}

bool GameState::is_finished() const
{
    return round_ >= NB_TOURS;
}

const std::vector<internal_action>&
GameState::get_internal_history(int player_id) const
{
    assert(player_info_.count(player_id) != 0);
    return player_info_.at(player_id).get_internal_history();
}

const std::vector<action_hist> GameState::get_history(int player_id) const
{
    std::vector<internal_action> internal_hist =
        get_internal_history(player_id);
    std::vector<action_hist> hist;
    for (auto action : internal_hist)
        if (action.type != ID_ACTION_DEBUG_AFFICHER_DRAPEAU)
            hist.push_back(action.move_action);
    return hist;
}

void GameState::reset_internal_history(int player_id)
{
    assert(player_info_.count(player_id) != 0);
    player_info_.at(player_id).reset_internal_history();
}

void GameState::add_to_internal_history(int player_id, internal_action action)
{
    assert(player_info_.count(player_id) != 0);
    player_info_.at(player_id).add_internal_action(action);
}
