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

#ifndef GAME_STATE_HH
#define GAME_STATE_HH

#include <rules/game-state.hh>
#include <rules/player.hh>

#include <array>
#include <unordered_map>

#include "map.hh"
#include "player_info.hh"

class GameState : public rules::GameState
{
public:
    GameState(std::istream& map_stream, rules::Players_sptr players);
    rules::GameState* copy() const override;

    int shortest_path(position start, position dest) const;
    case_type get_cell_type(position pos) const;
    bool is_obstacle(position pos) const;

    position get_agent_position(int player_id, int agent_id) const;
    std::pair<int, int> get_agent_id(position pos) const;
    void set_agent_position(int player_id, int agent_id, position pos);
    bool is_agent_on_position(position pos) const;

    bool is_alien_on_position(position pos) const;
    std::vector<alien_info> get_alien_info() const;
    alien_info get_alien_info(position pos) const;
    void reset_alien_capture_time(position pos);
    void check_presence_alien();
    void update_scores();

    int get_action_points(int player_id) const;
    void decrease_action_points(int player_id, int delta);
    void reset_action_points(int player_id);

    int opponent(int player) const;

    int get_score(int player_id) const;
    void increase_score(int player_id, int delta);

    void increment_round();
    int get_round() const;

    bool is_finished() const;

    const std::vector<action_hist>& get_history(int player_id) const;
    void reset_history(int player_id);
    void add_to_history(int player_id, action_hist action);

private:
    std::unordered_map<int, PlayerInfo> player_info_;
    std::array<int, 2> player_ids_;

    Map* map_;
    std::array<std::array<position, NB_AGENTS>, 2> agent_info_;
    int round_;
};

#endif /* !GAME_STATE_HH */
