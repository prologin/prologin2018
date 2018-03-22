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

void GameState::reset_action_points()
{
    for (auto& player : player_info_)
        player.second.reset_action_points();
}

unsigned int GameState::opponent(unsigned int player) const
{
    return (player_ids_[0] == player) ? player_ids_[1] : player_ids_[0];
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

void GameState::reset_history(unsigned int player_id)
{
    assert(player_info_.count(player_id) != 0);
    player_info_.at(player_id).reset_actions();
}
