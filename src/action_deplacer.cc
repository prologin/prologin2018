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
    if (agent_id_ >= NB_AGENTS)
        return ID_AGENT_INVALIDE;
    if (!inside_map(dest_))
        return POSITION_INVALIDE;

    position start = st->get_agent_position(player_id_, agent_id_);
    unsigned int cost = distance(start, dest_) * COUT_DEPLACEMENT;
    if (cost > st->get_action_points(player_id_))
        return PA_INSUFFISANTS;

    return OK;
}

void ActionDeplacer::apply_on(GameState* st) const
{
    position start = st->get_agent_position(player_id_, agent_id_);
    unsigned int cost = distance(start, dest_) * COUT_DEPLACEMENT;

    st->decrease_action_points(player_id_, cost);
    st->set_agent_position(player_id_, agent_id_, dest_);
}
