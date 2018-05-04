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
    st->decrease_agent_action_points(PLAYER_1, 0, NB_POINTS_ACTION);

    ActionDeplacer act(0, SUD, PLAYER_1);
    EXPECT_EQ(PA_INSUFFISANTS, act.check(st));
}

TEST_F(ActionTest, ActionDeplacer_InvalidDirection)
{
    ActionDeplacer act(0, (direction)-2, PLAYER_1);
    EXPECT_EQ(DIRECTION_INVALIDE, act.check(st));

    ActionDeplacer act2(0, (direction)12, PLAYER_1);
    EXPECT_EQ(DIRECTION_INVALIDE, act2.check(st));
}

TEST_F(ActionTest, ActionDeplacer_ObstacleWall)
{
    position next_to_wall = get_position_offset(TEST_WALL, SUD);
    st->set_agent_position(PLAYER_1, 0, next_to_wall);
    ActionDeplacer act(0, NORD, PLAYER_1);
    EXPECT_EQ(OBSTACLE_MUR, act.check(st));
}

TEST_F(ActionTest, ActionDeplacer_ObstacleAgent)
{
    position next_to_agent = get_position_offset(TEST_AGENT, SUD);
    st->set_agent_position(PLAYER_1, 0, next_to_agent);
    ActionDeplacer act(0, NORD, PLAYER_1);
    EXPECT_EQ(OBSTACLE_AGENT, act.check(st));
}

TEST_F(ActionTest, ActionDeplacer_MoveOutsideMap)
{
    st->set_agent_position(PLAYER_1, 0, {0, 0});
    ActionDeplacer act(0, NORD, PLAYER_1);
    EXPECT_EQ(DEPLACEMENT_HORS_LIMITES, act.check(st));
}

TEST_F(ActionTest, ActionDeplacer_InvalidAgentID)
{
    ActionDeplacer act(NB_AGENTS + 5, NORD, PLAYER_1);
    EXPECT_EQ(ID_AGENT_INVALIDE, act.check(st));

    ActionDeplacer act2(-3, NORD, PLAYER_2);
    EXPECT_EQ(ID_AGENT_INVALIDE, act2.check(st));
}

TEST_F(ActionTest, ActionDeplacer_Valid)
{
    std::vector<direction> test_path = {SUD, EST, EST, SUD, OUEST, NORD};
    position cur = st->get_agent_position(PLAYER_1, 0);

    for (auto& dir : test_path)
    {
        ActionDeplacer act(0, dir, PLAYER_1);
        EXPECT_EQ(OK, act.check(st));

        act.apply_on(st);
        cur = get_position_offset(cur, dir);
        EXPECT_EQ(cur, st->get_agent_position(PLAYER_1, 0));
    }

    int total_cost = (int)test_path.size() * COUT_DEPLACEMENT;
    EXPECT_EQ(NB_POINTS_ACTION - total_cost,
              st->get_agent_action_points(PLAYER_1, 0));
}
