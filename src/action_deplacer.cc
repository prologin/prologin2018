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

int ActionDeplacer::check(const GameState* st) const
{
    if (agent_id_ < 0 || agent_id_ >= NB_AGENTS)
        return ID_AGENT_INVALIDE;
    if (!inside_map(dest_))
        return POSITION_INVALIDE;
    if (st->get_cell_type(dest_) == case_type::MUR)
        return OBSTACLE_MUR;
    if (st->is_agent_on_position(dest_))
        return OBSTACLE_AGENT;

    int action_points = st->get_action_points(player_id_);
    position start = st->get_agent_position(player_id_, agent_id_);
    int cost = st->shortest_path(start, dest_);
    if (cost > action_points)
        return PA_INSUFFISANTS;
    if (cost == -1)
        return POSITION_INVALIDE;

    return OK;
}

void ActionDeplacer::apply_on(GameState* st) const
{
    position start = st->get_agent_position(player_id_, agent_id_);
    int cost = st->shortest_path(start, dest_);

    st->decrease_action_points(player_id_, cost);
    st->set_agent_position(player_id_, agent_id_, dest_);

    action_hist action;
    action.type = ACTION_DEPLACER;
    action.id_agent = agent_id_;
    action.dest = dest_;
    action.dir = (direction)0; // Not used, so initialized to 0
    st->add_to_history(player_id_, action);
}
