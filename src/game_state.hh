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

#ifndef GAME_STATE_HH
#define GAME_STATE_HH

#include <rules/game-state.hh>
#include <rules/player.hh>

#include <array>
#include <unordered_map>

#include "history.hh"
#include "map.hh"
#include "player_info.hh"

class GameState : public rules::GameState
{
public:
    GameState(std::istream& map_stream, const rules::Players& players);
    GameState* copy() const override;

    const auto& get_player_info() const { return player_info_; };

    std::vector<direction> get_shortest_path(position start,
                                             position dest) const;
    position slide_end_pos(position start, direction dir) const;
    case_type get_cell_type(position pos) const;
    bool is_obstacle(position pos) const;

    position get_agent_position(int player_id, int agent_id) const;
    std::pair<int, int> get_agent_id(position pos) const;
    void set_agent_position(int player_id, int agent_id, position pos);
    int agent_on_position(position pos) const;
    bool is_agent_on_position(position pos) const;

    bool is_alien_on_position(position pos) const;
    std::vector<alien_info> get_alien_info() const;
    alien_info get_alien_info(position pos) const;
    void reset_alien_capture_time(position pos);
    void check_presence_alien();
    void update_scores();

    int get_agent_action_points(int player_id, int agent_id) const;
    void decrease_agent_action_points(int player_id, int agent_id, int delta);
    void reset_action_points(int player_id);

    int opponent(int player) const;

    int get_score(int player_id) const;
    void increase_score(int player_id, int delta);

    void increment_round();
    int get_round() const;

    bool is_finished() const;

    const std::vector<internal_action>&
    get_internal_history(int player_id) const;
    const std::vector<action_hist> get_history(int player_id) const;
    void reset_internal_history(int player_id);
    void add_to_internal_history(int player_id, internal_action action);

private:
    GameState(const GameState& gs);

    std::unordered_map<int, PlayerInfo> player_info_;
    std::array<int, 2> player_ids_;

    std::shared_ptr<Map> map_;
    std::array<std::array<position, NB_AGENTS>, 2> agent_info_;
    int round_;
};

#endif /* !GAME_STATE_HH */
