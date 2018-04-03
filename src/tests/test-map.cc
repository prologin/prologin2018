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

#include "../game_state.hh"

#include "test-helpers.hh"

TEST_F(ActionTest, Map_ShortestPath)
{
    // Invalid position
    EXPECT_EQ(-1, st->shortest_path({0, 0}, {-42, TAILLE_ICEBERG}));
    EXPECT_EQ(-1, st->shortest_path({0, 0}, TEST_WALL));
    EXPECT_EQ(-1, st->shortest_path({0, 0}, TEST_AGENT));

    // Simple pathfinding
    EXPECT_EQ(4, st->shortest_path({2, 0}, {3, 3}));
    EXPECT_EQ(10, st->shortest_path({10, 10}, {15, 15}));

    // Go around agents/walls
    st->set_agent_position(PLAYER_1, 0, {5, 2});
    st->set_agent_position(PLAYER_1, 2, {5, 3});
    st->set_agent_position(PLAYER_2, 0, {5, 4});
    EXPECT_EQ(10, st->shortest_path({0, 3}, {6, 3}));
}

TEST_F(ActionTest, Map_AlienSpawning)
{
    alien_info alien = st->get_alien_info(TEST_ALIEN);

    // We don't want to capture the alien while testing
    ASSERT_FALSE(st->is_agent_on_position(alien.pos));

    for (int round = 0; round < NB_TOURS; round++)
    {
        st->check_presence_alien();
        if (round >= alien.tour_invasion &&
            round < alien.tour_invasion + alien.duree_invasion)
            EXPECT_TRUE(st->is_alien_on_position(alien.pos));
        else
            EXPECT_FALSE(st->is_alien_on_position(alien.pos));
        st->increment_round();
    }
}

TEST_F(ActionTest, Map_AlienInvalidCaptureBecauseMove)
{
    EXPECT_EQ(0, st->get_score(PLAYER_1));
    EXPECT_EQ(0, st->get_score(PLAYER_2));

    alien_info alien = st->get_alien_info(TEST_ALIEN);
    int capture_time = 0;
    st->set_agent_position(PLAYER_1, 0, alien.pos);

    for (int round = 0; round < NB_TOURS; round++)
    {
        st->check_presence_alien();

        if (round >= alien.tour_invasion &&
            round < alien.tour_invasion + alien.duree_invasion)
        {
            // Move the agent one round before capturing the alien
            if (capture_time + 1 == NB_TOURS_CAPTURE)
            {
                st->set_agent_position(PLAYER_1, 0, TEST_EMPTY_CELL);
                EXPECT_EQ(0, st->get_alien_info(alien.pos).capture_en_cours);
                capture_time = 0;
            }
            else
            {
                // Move the agent back to the alien position to test reset
                if (st->get_agent_position(PLAYER_1, 0) == TEST_EMPTY_CELL)
                {
                    EXPECT_EQ(0,
                              st->get_alien_info(alien.pos).capture_en_cours);
                    st->set_agent_position(PLAYER_1, 0, alien.pos);
                }

                EXPECT_TRUE(st->is_alien_on_position(alien.pos));
                EXPECT_EQ(capture_time,
                          st->get_alien_info(alien.pos).capture_en_cours);
                capture_time++;
            }
        }
        else
            EXPECT_FALSE(st->is_alien_on_position(alien.pos));

        st->update_scores();
        st->increment_round();
    }

    EXPECT_EQ(0, st->get_score(PLAYER_1));
    EXPECT_EQ(0, st->get_score(PLAYER_2));
}

TEST_F(ActionTest, Map_AlienInvalidCaptureBecauseDespawn)
{
    EXPECT_EQ(0, st->get_score(PLAYER_1));
    EXPECT_EQ(0, st->get_score(PLAYER_2));

    alien_info alien = st->get_alien_info(TEST_ALIEN);
    int last_alien_round = alien.tour_invasion + alien.duree_invasion;
    int capture_time = 0;

    for (int round = 0; round < NB_TOURS; round++)
    {
        st->check_presence_alien();

        // We start the capture one round too late to test alien despawn
        if (round >= last_alien_round - NB_TOURS_CAPTURE + 1 &&
            round < last_alien_round)
        {
            st->set_agent_position(PLAYER_1, 0, alien.pos);
            EXPECT_TRUE(st->is_alien_on_position(alien.pos));
            EXPECT_EQ(capture_time,
                      st->get_alien_info(alien.pos).capture_en_cours);
            capture_time++;
        }
        else if (round >= alien.tour_invasion && round < last_alien_round)
            EXPECT_TRUE(st->is_alien_on_position(alien.pos));
        else
            EXPECT_FALSE(st->is_alien_on_position(alien.pos));

        st->update_scores();
        st->increment_round();
    }

    EXPECT_EQ(0, st->get_score(PLAYER_1));
    EXPECT_EQ(0, st->get_score(PLAYER_2));
}

TEST_F(ActionTest, Map_AlienValidCapture)
{
    EXPECT_EQ(0, st->get_score(PLAYER_1));
    EXPECT_EQ(0, st->get_score(PLAYER_2));

    alien_info alien = st->get_alien_info(TEST_ALIEN);
    int capture_time = 0;
    st->set_agent_position(PLAYER_1, 0, alien.pos);

    for (int round = 0; round < NB_TOURS; round++)
    {
        st->check_presence_alien();

        if (round >= alien.tour_invasion &&
            round < alien.tour_invasion + alien.duree_invasion)
        {
            if (capture_time == NB_TOURS_CAPTURE)
            {
                EXPECT_FALSE(st->is_alien_on_position(alien.pos));
            }
            else
            {
                EXPECT_TRUE(st->is_alien_on_position(alien.pos));
                EXPECT_EQ(capture_time,
                          st->get_alien_info(alien.pos).capture_en_cours);
                capture_time++;
            }
        }
        else
            EXPECT_FALSE(st->is_alien_on_position(alien.pos));

        st->update_scores();
        st->increment_round();
    }

    EXPECT_EQ(alien.puissance, st->get_score(PLAYER_1));
    EXPECT_EQ(0, st->get_score(PLAYER_2));
}
