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
    position init_pos =
        st->get_agent_position(player_id_, agent_id_) + offset[dir_];
    std::pair<int, int> agent_neigh = st->get_agent_id(init_pos);
    int player_mv = agent_neigh.first;
    int agent_mv = agent_neigh.second;

    position pos = init_pos, next_pos = init_pos;
    do
    {
        pos = next_pos;
        next_pos += offset[dir_];
    } while (inside_map(next_pos) && !st->is_obstacle(next_pos));

    st->decrease_action_points(player_id_, COUT_POUSSER);
    st->set_agent_position(player_mv, agent_mv, pos);
    if (init_pos != pos && st->is_alien_on_position(init_pos))
        st->reset_alien_capture_time(init_pos);

    action_hist action;
    action.type = ACTION_POUSSER;
    action.id_agent = agent_id_;
    action.dir = dir_;
    st->add_to_history(player_id_, action);
}
