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

#ifndef PLAYER_INFO_HH
#define PLAYER_INFO_HH

#include <rules/player.hh>

#include <string>
#include <vector>

#include "constant.hh"
#include "history.hh"
#include "position.hh"

class PlayerInfo
{
public:
    PlayerInfo(rules::Player_sptr player, int internal_id);

    int get_internal_id() const;

    int get_agent_action_points(int agent_id) const;
    void decrease_agent_action_points(int agent_id, int delta);
    void reset_action_points();

    int get_score() const;
    void increase_score(int delta);

    const std::string& get_name() const;
    void set_name(const std::string& name);

    const std::vector<internal_action>& get_internal_history() const;
    void reset_internal_history();
    void add_internal_action(internal_action action);

private:
    rules::Player_sptr player_;
    std::vector<internal_action> internal_hist_;
    std::array<int, NB_AGENTS> action_points_;
    int internal_id_;
};

#endif
