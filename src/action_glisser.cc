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
    if (agent_id_ < 0 || agent_id_ >= NB_AGENTS)
        return ID_AGENT_INVALIDE;
    if (dir_ < 0 || dir_ > 3)
        return DIRECTION_INVALIDE;
    if (COUT_GLISSADE > st->get_action_points(player_id_))
        return PA_INSUFFISANTS;
    return OK;
}

void ActionGlisser::apply_on(GameState* st) const
{
    position start = st->get_agent_position(player_id_, agent_id_);
    position end = st->slide_end_pos(start, dir_);

    st->decrease_action_points(player_id_, COUT_GLISSADE);
    st->set_agent_position(player_id_, agent_id_, end);

    action_hist action;
    action.type = ACTION_GLISSER;
    action.id_agent = agent_id_;
    action.dir = dir_;
    action.dest = position{0, 0}; // Not used, so initialized to 0
    st->add_to_history(player_id_, action);
}
