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

#include "../actions.hh"
#include "../constant.hh"
#include "../struct_helper.hh"

#include "test-helpers.hh"

TEST_F(ActionTest, ActionDebugAfficherDrapeau_InvalidPosition)
{
    ActionDebugAfficherDrapeau act({-42, 27}, DRAPEAU_BLEU, PLAYER_1);
    EXPECT_EQ(POSITION_INVALIDE, act.check(st));
}

TEST_F(ActionTest, ActionDebugAfficherDrapeau_InvalidFlag)
{
    ActionDebugAfficherDrapeau act({0, 0}, (debug_drapeau)42, PLAYER_1);
    EXPECT_EQ(DRAPEAU_INVALIDE, act.check(st));

    ActionDebugAfficherDrapeau act2({0, 0}, (debug_drapeau)-42, PLAYER_2);
    EXPECT_EQ(DRAPEAU_INVALIDE, act2.check(st));
}

// This action should only appear in the internal history
TEST_F(ActionTest, ActionDebugAfficherDrapeau_InternalHistory)
{
    std::vector<internal_action> expected_hist_p1;
    std::vector<internal_action> expected_hist_p2;

    ActionDebugAfficherDrapeau* act;
    act = new ActionDebugAfficherDrapeau({0, 0}, DRAPEAU_BLEU, PLAYER_1);
    EXPECT_EQ(OK, act->check(st));
    act->apply_on(st);
    expected_hist_p1.push_back(
        {ID_ACTION_DEBUG_AFFICHER_DRAPEAU, {DRAPEAU_BLEU, {0, 0}}});
    delete act;

    act = new ActionDebugAfficherDrapeau({0, 1}, DRAPEAU_ROUGE, PLAYER_2);
    EXPECT_EQ(OK, act->check(st));
    act->apply_on(st);
    expected_hist_p2.push_back(
        {ID_ACTION_DEBUG_AFFICHER_DRAPEAU, {DRAPEAU_ROUGE, {0, 1}}});
    delete act;

    act = new ActionDebugAfficherDrapeau({0, 2}, DRAPEAU_VERT, PLAYER_1);
    EXPECT_EQ(OK, act->check(st));
    act->apply_on(st);
    expected_hist_p1.push_back(
        {ID_ACTION_DEBUG_AFFICHER_DRAPEAU, {DRAPEAU_VERT, {0, 2}}});
    delete act;

    act = new ActionDebugAfficherDrapeau({0, 2}, AUCUN_DRAPEAU, PLAYER_1);
    EXPECT_EQ(OK, act->check(st));
    act->apply_on(st);
    expected_hist_p1.push_back(
        {ID_ACTION_DEBUG_AFFICHER_DRAPEAU, {AUCUN_DRAPEAU, {0, 2}}});
    delete act;

    // The API's history function should not keep track of this action
    EXPECT_TRUE(st->get_history(PLAYER_1).empty());
    EXPECT_TRUE(st->get_history(PLAYER_2).empty());
}
