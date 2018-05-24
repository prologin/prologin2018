// SPDX-License-Identifier: GPL-2.0-or-later
/*
** This file is part of Prologin2018, a rules library for stechec2.
**
** Copyright (c) 2018 Association Prologin <info@prologin.org>
** Copyright (c) 2018 Thibault Allançon
**
** Prologin2018 is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Prologin2018.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ACTION_DEBUG_AFFICHER_DRAPEAU_HH
#define ACTION_DEBUG_AFFICHER_DRAPEAU_HH

#include <rules/action.hh>

#include "actions.hh"
#include "constant.hh"
#include "game_state.hh"

class ActionDebugAfficherDrapeau : public rules::Action<GameState>
{
public:
    ActionDebugAfficherDrapeau(position pos, debug_drapeau drapeau,
                               int player_id)
        : pos_(pos)
        , drapeau_(drapeau)
        , player_id_(player_id)
    {
    }
    ActionDebugAfficherDrapeau() {} // for register_action()

    int check(const GameState* st) const override;
    void apply_on(GameState* st) const override;

    void handle_buffer(utils::Buffer& buf) override
    {
        buf.handle(pos_);
        buf.handle(drapeau_);
        buf.handle(player_id_);
    }

    uint32_t player_id() const override { return player_id_; };
    uint32_t id() const override { return ID_ACTION_DEBUG_AFFICHER_DRAPEAU; }

private:
    position pos_;
    debug_drapeau drapeau_;
    int player_id_;
};

#endif // !ACTION_DEBUG_AFFICHER_DRAPEAU_HH
