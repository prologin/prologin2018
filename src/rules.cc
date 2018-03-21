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

#include "rules.hh"
#include "actions.hh"

Rules::Rules(const rules::Options opt)
    : TurnBasedRules(opt), sandbox_(opt.time)
{
    if (!opt.champion_lib.empty())
    {
        champion_dll_ = std::make_unique<utils::DLL>(opt.champion_lib);

        // FIXME: register user functions
    }

    GameState* game_state = new GameState(opt.players);
    api_ = std::make_unique<Api>(game_state, opt.player);
    register_actions();
}

void Rules::register_actions()
{
    api_->actions()->register_action(
        ID_ACTION_DEPLACER,
        []() -> rules::IAction* { return new ActionDeplacer(); }
        );
    api_->actions()->register_action(
        ID_ACTION_GLISSER,
        []() -> rules::IAction* { return new ActionGlisser(); }
        );
}

rules::Actions* Rules::get_actions()
{
    return api_->actions();
}

void Rules::apply_action(const rules::IAction_sptr& action)
{
    // When receiving an action, the API should have already checked that it
    // is valid. We recheck that for the current gamestate here to avoid weird
    // client/server desynchronizations and make sure the gamestate is always
    // consistent across the clients and the server.

    int err = action->check(api_->game_state());
    if (err)
        FATAL("Synchronization error: received action %d from player %d, but "
              "check() on current gamestate returned %d.",
              action->id(), action->player_id(), err);
    api_->game_state_set(action->apply(api_->game_state()));
}

bool Rules::is_finished()
{
    // FIXME
    return true;
}
