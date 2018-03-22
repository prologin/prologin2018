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

int ActionGlisser::check(const GameState* st) const
{
    if (agent_id_ >= NB_AGENTS)
        return ID_AGENT_INVALIDE;
    if (dir_ < 0 || dir_ > 3)
        return DIRECTION_INVALIDE;
    if (COUT_GLISSADE > st->get_action_points(player_id_))
        return PA_INSUFFISANTS;
    return OK;
}

void ActionGlisser::apply_on(GameState* st) const
{
    position init_pos = st->get_agent_position(player_id_, agent_id_);
    int player_mv = player_id_;
    int agent_mv = agent_id_;
    std::pair<int, int> agent_neigh = st->get_agent_id(init_pos + offset[dir_]);

    // Adjacent agent when sliding => push the other agent until obstacle
    if (agent_neigh.first != -1)
    {
        player_mv = agent_neigh.first;
        agent_mv = agent_neigh.second;
        init_pos += offset[dir_];
    }

    position pos = init_pos, next_pos = init_pos;
    do
    {
        pos = next_pos;
        next_pos += offset[dir_];
    } while (inside_map(next_pos) && !st->is_obstacle(next_pos));

    st->decrease_action_points(player_id_, COUT_GLISSADE);
    st->set_agent_position(player_mv, agent_mv, pos);

    action_hist action;
    action.type = ACTION_GLISSER;
    action.id_agent = agent_id_;
    action.dir = dir_;
    st->add_to_history(player_id_, action);
}
