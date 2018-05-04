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

#include "player_info.hh"

PlayerInfo::PlayerInfo(rules::Player_sptr player, int internal_id)
    : player_(std::move(player))
    , internal_id_(internal_id)
{
    assert(player_);
    player_->score = 0;
    reset_action_points();
}

int PlayerInfo::get_internal_id() const
{
    return internal_id_;
}

int PlayerInfo::get_agent_action_points(int agent_id) const
{
    assert(agent_id >= 0 && agent_id < NB_AGENTS);
    return action_points_[agent_id];
}

void PlayerInfo::decrease_agent_action_points(int agent_id, int delta)
{
    assert(agent_id >= 0 && agent_id < NB_AGENTS);
    assert(action_points_[agent_id] >= delta);
    action_points_[agent_id] -= delta;
}

void PlayerInfo::reset_action_points()
{
    for (int agent = 0; agent < NB_AGENTS; agent++)
        action_points_[agent] = NB_POINTS_ACTION;
}

int PlayerInfo::get_score() const
{
    return player_->score;
}

void PlayerInfo::increase_score(int delta)
{
    player_->score += delta;
}

const std::string& PlayerInfo::get_name() const
{
    return player_->name;
}

void PlayerInfo::set_name(const std::string& name)
{
    player_->name = name;
}

const std::vector<internal_action>& PlayerInfo::get_internal_history() const
{
    return internal_hist_;
}

void PlayerInfo::reset_internal_history()
{
    internal_hist_.clear();
}

void PlayerInfo::add_internal_action(internal_action action)
{
    internal_hist_.push_back(action);
}
