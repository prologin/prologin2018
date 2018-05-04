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

#include "test-helpers.hh"

TEST_F(ActionTest, ActionGlisser_NotEnoughActionPoints)
{
    st->reset_action_points(PLAYER_1);
    st->decrease_agent_action_points(PLAYER_1, 0, NB_POINTS_ACTION);

    ActionGlisser act(0, NORD, PLAYER_1);
    EXPECT_EQ(PA_INSUFFISANTS, act.check(st));
}

TEST_F(ActionTest, ActionGlisser_InvalidDirection)
{
    ActionGlisser act(0, (direction)10, PLAYER_1);
    EXPECT_EQ(DIRECTION_INVALIDE, act.check(st));

    ActionGlisser act2(0, (direction)-1, PLAYER_1);
    EXPECT_EQ(DIRECTION_INVALIDE, act2.check(st));
}

TEST_F(ActionTest, ActionGlisser_InvalidAgentID)
{
    ActionGlisser act(NB_AGENTS + 5, NORD, PLAYER_1);
    EXPECT_EQ(ID_AGENT_INVALIDE, act.check(st));

    ActionGlisser act2(-42, NORD, PLAYER_1);
    EXPECT_EQ(ID_AGENT_INVALIDE, act2.check(st));
}

TEST_F(ActionTest, ActionGlisser_Valid)
{
    position dest1 = {9, 0};
    position dest2 = {TAILLE_ICEBERG - 1, 0};
    position dest3 = {1, 3};
    position dest4 = {10, TAILLE_ICEBERG - 1};

    ActionGlisser* act;
    act = new ActionGlisser(0, SUD, PLAYER_1);
    EXPECT_EQ(OK, act->check(st));
    act->apply_on(st);
    EXPECT_EQ(dest1, st->get_agent_position(PLAYER_1, 0));
    delete act;

    act = new ActionGlisser(0, SUD, PLAYER_2);
    EXPECT_EQ(OK, act->check(st));
    act->apply_on(st);
    EXPECT_EQ(dest2, st->get_agent_position(PLAYER_2, 0));
    delete act;

    act = new ActionGlisser(3, SUD, PLAYER_1);
    EXPECT_EQ(OK, act->check(st));
    act->apply_on(st);
    EXPECT_EQ(dest3, st->get_agent_position(PLAYER_1, 3));
    delete act;

    act = new ActionGlisser(3, EST, PLAYER_2);
    EXPECT_EQ(OK, act->check(st));
    act->apply_on(st);
    EXPECT_EQ(dest4, st->get_agent_position(PLAYER_2, 3));
    delete act;

    EXPECT_EQ(NB_POINTS_ACTION - COUT_GLISSADE,
              st->get_agent_action_points(PLAYER_1, 0));
    EXPECT_EQ(NB_POINTS_ACTION - COUT_GLISSADE,
              st->get_agent_action_points(PLAYER_1, 3));
    EXPECT_EQ(NB_POINTS_ACTION - COUT_GLISSADE,
              st->get_agent_action_points(PLAYER_2, 0));
    EXPECT_EQ(NB_POINTS_ACTION - COUT_GLISSADE,
              st->get_agent_action_points(PLAYER_2, 3));
}
