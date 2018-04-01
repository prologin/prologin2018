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

#include "actions.hh"

int ActionPousser::check(const GameState* st) const
{
    if (agent_id_ >= NB_AGENTS)
        return ID_AGENT_INVALIDE;
    if (dir_ < 0 || dir_ > 3)
        return DIRECTION_INVALIDE;
    if (COUT_POUSSER > st->get_action_points(player_id_))
        return PA_INSUFFISANTS;
    position pos = st->get_agent_position(player_id_, agent_id_);
    if (!st->is_agent_on_position(pos + offset[dir_]))
        return RIEN_A_POUSSER;
    return OK;
}

void ActionPousser::apply_on(GameState* st) const
{
    position start =
        st->get_agent_position(player_id_, agent_id_) + offset[dir_];
    position end = st->slide_end_pos(start, dir_);

    std::pair<int, int> agent_neigh = st->get_agent_id(start);
    int player_mv = agent_neigh.first;
    int agent_mv = agent_neigh.second;

    st->decrease_action_points(player_id_, COUT_POUSSER);
    st->set_agent_position(player_mv, agent_mv, end);
    if (start != end && st->is_alien_on_position(start))
        st->reset_alien_capture_time(start);

    action_hist action;
    action.type = ACTION_POUSSER;
    action.id_agent = agent_id_;
    action.dir = dir_;
    action.dest = position{0, 0}; // Not used, so initialized to 0
    st->add_to_history(player_id_, action);
}
