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

#include "game_state.hh"

GameState::GameState(rules::Players_sptr players)
    : rules::GameState(),
      players_(players)
{
    // FIXME
}

GameState::GameState(const GameState& st)
    : rules::GameState(st)
    , players_(st.players_)
{
    // FIXME
}

rules::GameState* GameState::copy() const
{
    return new GameState(*this);
}

GameState::~GameState()
{
    // FIXME
}
