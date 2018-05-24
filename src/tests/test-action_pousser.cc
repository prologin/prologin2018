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

#include "../actions.hh"

#include "test-helpers.hh"

TEST_F(ActionTest, ActionPousser_NotEnoughActionPoints)
{
    st->reset_action_points(PLAYER_1);
    st->decrease_agent_action_points(PLAYER_1, 0, NB_POINTS_ACTION);

    ActionPousser act(0, EST, PLAYER_1);
    EXPECT_EQ(PA_INSUFFISANTS, act.check(st));
}

TEST_F(ActionTest, ActionPousser_InvalidDirection)
{
    ActionPousser act(0, (direction)10, PLAYER_1);
    EXPECT_EQ(DIRECTION_INVALIDE, act.check(st));

    ActionPousser act2(0, (direction)-10, PLAYER_1);
    EXPECT_EQ(DIRECTION_INVALIDE, act2.check(st));
}

TEST_F(ActionTest, ActionPousser_InvalidAgentID)
{
    ActionPousser act(NB_AGENTS + 5, NORD, PLAYER_1);
    EXPECT_EQ(ID_AGENT_INVALIDE, act.check(st));

    ActionPousser act2(-1337, NORD, PLAYER_1);
    EXPECT_EQ(ID_AGENT_INVALIDE, act2.check(st));
}

TEST_F(ActionTest, ActionPousser_NothingToPush)
{
    ActionPousser act(0, NORD, PLAYER_1);
    EXPECT_EQ(RIEN_A_POUSSER, act.check(st));

    st->set_agent_position(PLAYER_1, 0, TEST_EMPTY_CELL);
    ActionPousser act2(0, EST, PLAYER_1);
    EXPECT_EQ(RIEN_A_POUSSER, act2.check(st));
}

TEST_F(ActionTest, ActionPousser_Valid)
{
    position dest1 = {9, 0};
    position dest2 = {TAILLE_BANQUISE - 1, 0};
    position dest3 = get_position_offset(dest1, EST);
    position dest4 = {9, TAILLE_BANQUISE - 1};

    st->set_agent_position(PLAYER_1, 0, dest1);

    ActionPousser* act;
    act = new ActionPousser(0, SUD, PLAYER_1);
    EXPECT_EQ(OK, act->check(st));
    act->apply_on(st);
    EXPECT_EQ(dest1, st->get_agent_position(PLAYER_1, 0));
    EXPECT_EQ(dest2, st->get_agent_position(PLAYER_2, 0));
    delete act;
    EXPECT_EQ(NB_POINTS_ACTION - COUT_POUSSER,
              st->get_agent_action_points(PLAYER_1, 0));

    st->set_agent_position(PLAYER_2, 1, dest3);
    st->reset_action_points(PLAYER_1);

    act = new ActionPousser(0, EST, PLAYER_1);
    EXPECT_EQ(OK, act->check(st));
    act->apply_on(st);
    EXPECT_EQ(dest1, st->get_agent_position(PLAYER_1, 0));
    EXPECT_EQ(dest4, st->get_agent_position(PLAYER_2, 1));
    delete act;

    EXPECT_EQ(NB_POINTS_ACTION - COUT_POUSSER,
              st->get_agent_action_points(PLAYER_1, 0));
}
