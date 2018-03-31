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

#include "test-helpers.hh"

TEST_F(ActionTest, ActionDeplacer_NotEnoughActionPoints)
{
    st->reset_action_points(PLAYER_1);
    st->decrease_action_points(PLAYER_1, NB_POINTS_ACTION);

    ActionDeplacer act(0, {TAILLE_ICEBERG - 1, TAILLE_ICEBERG - 1}, PLAYER_1);
    EXPECT_EQ(PA_INSUFFISANTS, act.check(st));
}

TEST_F(ActionTest, ActionDeplacer_InvalidPosition)
{
    ActionDeplacer act(0, {-42, TAILLE_ICEBERG + 1337}, PLAYER_1);
    EXPECT_EQ(POSITION_INVALIDE, act.check(st));
}

TEST_F(ActionTest, ActionDeplacer_ObstacleWall)
{
    position wall = {2, 3};
    ActionDeplacer act(0, wall, PLAYER_1);
    EXPECT_EQ(case_type::MUR, st->get_cell_type(wall));
    EXPECT_EQ(OBSTACLE_MUR, act.check(st));
}

TEST_F(ActionTest, ActionDeplacer_ObstacleAgent)
{
    position agent = {0, 1};
    ActionDeplacer act(0, agent, PLAYER_1);
    EXPECT_EQ(true, st->is_agent_on_position(agent));
    EXPECT_EQ(OBSTACLE_AGENT, act.check(st));
}

TEST_F(ActionTest, ActionDeplacer_InvalidAgentID)
{
    ActionDeplacer act(NB_AGENTS + 5, {0, 0}, PLAYER_1);
    EXPECT_EQ(ID_AGENT_INVALIDE, act.check(st));
}

TEST_F(ActionTest, ActionDeplacer_Valid)
{
    position pos1 = {5, 0};
    position pos2 = {5, 3};
    position pos3 = {1, 1};
    int dist = 0;

    ActionDeplacer* act;
    act = new ActionDeplacer(0, pos1, PLAYER_1);
    EXPECT_EQ(OK, act->check(st));
    dist += st->shortest_path(st->get_agent_position(PLAYER_1, 0), pos1);
    act->apply_on(st);
    EXPECT_EQ(pos1, st->get_agent_position(PLAYER_1, 0));
    delete act;

    act = new ActionDeplacer(0, pos2, PLAYER_1);
    EXPECT_EQ(OK, act->check(st));
    dist += st->shortest_path(st->get_agent_position(PLAYER_1, 0), pos2);
    act->apply_on(st);
    EXPECT_EQ(pos2, st->get_agent_position(PLAYER_1, 0));
    delete act;

    act = new ActionDeplacer(2, pos3, PLAYER_1);
    EXPECT_EQ(OK, act->check(st));
    dist += st->shortest_path(st->get_agent_position(PLAYER_1, 2), pos3);
    act->apply_on(st);
    EXPECT_EQ(pos3, st->get_agent_position(PLAYER_1, 2));
    delete act;

    EXPECT_EQ(NB_POINTS_ACTION - dist * COUT_DEPLACEMENT,
              st->get_action_points(PLAYER_1));
}
