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

#include <fstream>

#include "actions.hh"
#include "rules.hh"

Rules::Rules(const rules::Options opt)
    : TurnBasedRules(opt)
    , sandbox_(opt.time)
{
    if (!opt.champion_lib.empty())
    {
        champion_dll_ = std::make_unique<utils::DLL>(opt.champion_lib);

        champion_partie_init_ =
            champion_dll_->get<f_champion_partie_init>("partie_init");
        champion_jouer_tour_ =
            champion_dll_->get<f_champion_jouer_tour>("jouer_tour");
        champion_partie_fin_ =
            champion_dll_->get<f_champion_partie_fin>("partie_fin");
    }

    std::ifstream ifs(opt.map_file);
    if (!ifs.is_open())
        FATAL("Cannot open file: %s", opt.map_file.c_str());

    GameState* game_state = new GameState(ifs, opt.players);
    api_ = std::make_unique<Api>(game_state, opt.player);
    register_actions();
}

void Rules::register_actions()
{
    api_->actions()->register_action(
        ID_ACTION_DEPLACER,
        []() -> rules::IAction* { return new ActionDeplacer(); });
    api_->actions()->register_action(
        ID_ACTION_GLISSER,
        []() -> rules::IAction* { return new ActionGlisser(); });
    api_->actions()->register_action(
        ID_ACTION_POUSSER,
        []() -> rules::IAction* { return new ActionPousser(); });
    api_->actions()->register_action(
        ID_ACTION_DEBUG_AFFICHER_DRAPEAU,
        []() -> rules::IAction* { return new ActionDebugAfficherDrapeau(); });
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

void Rules::at_player_start(rules::ClientMessenger_sptr)
{
    try
    {
        sandbox_.execute(champion_partie_init_);
    }
    catch (utils::SandboxTimeout)
    {
        FATAL("player_start: timeout");
    }
}

void Rules::at_spectator_start(rules::ClientMessenger_sptr)
{
    champion_partie_init_();
}

void Rules::at_player_end(rules::ClientMessenger_sptr)
{
    try
    {
        sandbox_.execute(champion_partie_fin_);
    }
    catch (utils::SandboxTimeout)
    {
        FATAL("player_end: timeout");
    }
}

void Rules::at_spectator_end(rules::ClientMessenger_sptr)
{
    champion_partie_fin_();
}

void Rules::player_turn()
{
    try
    {
        sandbox_.execute(champion_jouer_tour_);
    }
    catch (utils::SandboxTimeout)
    {
        FATAL("player_turn: timeout");
    }
}

void Rules::spectator_turn()
{
    champion_jouer_tour_();
}

void Rules::start_of_player_turn(unsigned int player_id)
{
    api_->game_state()->reset_action_points(player_id);
    api_->game_state()->reset_internal_history(player_id);
}

void Rules::end_of_player_turn(unsigned int /* player_id */)
{
    // Clear the list of game states at the end of each turn (half-round)
    // We need the linked list of game states only for undo and history,
    // therefore old states are not needed anymore after the turn ends.
    api_->game_state()->clear_old_version();
}

// A round is made up of 2 turns, one for each player.
void Rules::start_of_round()
{
    api_->game_state()->check_presence_alien();
}

void Rules::end_of_round()
{
    api_->game_state()->update_scores();
    api_->game_state()->increment_round();
}

bool Rules::is_finished()
{
    return api_->game_state()->is_finished();
}

GameState* Rules::get_game_state() const
{
    return api_->game_state();
}
