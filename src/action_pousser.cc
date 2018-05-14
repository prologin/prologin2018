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
#include "history.hh"

int ActionPousser::check(const GameState* st) const
{
    if (agent_id_ < 0 || agent_id_ >= NB_AGENTS)
        return ID_AGENT_INVALIDE;
    if (dir_ < 0 || dir_ > 3)
        return DIRECTION_INVALIDE;
    if (COUT_POUSSER > st->get_agent_action_points(player_id_, agent_id_))
        return PA_INSUFFISANTS;

    position pos = st->get_agent_position(player_id_, agent_id_);
    position adjacent = get_position_offset(pos, dir_);
    if (!st->is_agent_on_position(adjacent))
        return RIEN_A_POUSSER;

    return OK;
}

void ActionPousser::apply_on(GameState* st) const
{
    position agent = st->get_agent_position(player_id_, agent_id_);
    position start = get_position_offset(agent, dir_);
    position end = st->slide_end_pos(start, dir_);

    std::pair<int, int> agent_neigh = st->get_agent_id(start);
    int player_mv = agent_neigh.first;
    int agent_mv = agent_neigh.second;

    st->decrease_agent_action_points(player_id_, agent_id_, COUT_POUSSER);
    st->set_agent_position(player_mv, agent_mv, end);

    internal_action action;
    action.atype = ID_ACTION_POUSSER;
    action.move_action = (action_hist){ACTION_POUSSER, agent_id_, dir_};
    st->add_to_internal_history(player_id_, action);
}
