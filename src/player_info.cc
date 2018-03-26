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

PlayerInfo::PlayerInfo(rules::Player_sptr player)
    : player_(std::move(player))
{
    assert(player_);
    player_->score = 0;
}

int PlayerInfo::get_action_points() const
{
    return action_points_;
}

void PlayerInfo::decrease_action_points(int delta)
{
    action_points_ -= delta;
}

void PlayerInfo::reset_action_points()
{
    action_points_ = NB_POINTS_ACTION;
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

const std::vector<action_hist>& PlayerInfo::get_actions() const
{
    return actions_;
}

void PlayerInfo::reset_actions()
{
    actions_.clear();
}

void PlayerInfo::add_action(action_hist action)
{
    actions_.push_back(action);
}
