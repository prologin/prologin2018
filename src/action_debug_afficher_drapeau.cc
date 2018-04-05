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

int ActionDebugAfficherDrapeau::check(const GameState* /*st*/) const
{
    if (!inside_map(pos_))
        return POSITION_INVALIDE;
    if (drapeau_ < 0 || drapeau_ > 3)
        return DRAPEAU_INVALIDE;

    return OK;
}

void ActionDebugAfficherDrapeau::apply_on(GameState* st) const
{
    action_hist action{ACTION_DEBUG, 0, (direction)0, drapeau_};
    st->add_to_history(player_id_, action);
}
