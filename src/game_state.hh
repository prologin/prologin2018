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

#ifndef GAME_STATE_HH
#define GAME_STATE_HH

#include <rules/game-state.hh>
#include <rules/player.hh>

class GameState : public rules::GameState
{
    public:
        // FIXME
        // additional parameters? for instance map
        GameState(rules::Players_sptr players);
        GameState(const GameState& st);
        rules::GameState* copy() const override;
        ~GameState();

    private:
        rules::Players_sptr players_;
};

#endif /* !GAME_STATE_HH */

