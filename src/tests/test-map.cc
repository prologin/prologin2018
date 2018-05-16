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
    std::vector<direction> path1 =
        st->get_shortest_path({0, 0}, {-42, TAILLE_BANQUISE});
    std::vector<direction> path2 = st->get_shortest_path({0, 0}, TEST_WALL);
    std::vector<direction> path3 = st->get_shortest_path({0, 0}, TEST_AGENT);
    EXPECT_TRUE(path1.empty());
    EXPECT_TRUE(path2.empty());
    EXPECT_TRUE(path3.empty());

    // Start = dest
    std::vector<direction> path4 =
        st->get_shortest_path(TEST_EMPTY_CELL, TEST_EMPTY_CELL);
    EXPECT_TRUE(path4.empty());

    // Simple pathfinding
    std::vector<direction> path5 = st->get_shortest_path({2, 0}, {3, 3});
    std::vector<direction> expected_path5 = {EST, EST, SUD, EST};
    std::vector<direction> path6 = st->get_shortest_path({10, 10}, {15, 15});
    std::vector<direction> expected_path6 = {EST, EST, EST, EST, EST,
                                             SUD, SUD, SUD, SUD, SUD};
    EXPECT_EQ(expected_path5, path5);
    EXPECT_EQ(expected_path6, path6);

    // Go around agents/walls
    st->set_agent_position(PLAYER_1, 0, {5, 2});
    st->set_agent_position(PLAYER_1, 2, {5, 3});
    st->set_agent_position(PLAYER_2, 0, {5, 4});
    std::vector<direction> path7 = st->get_shortest_path({0, 3}, {6, 3});
    std::vector<direction> expected_path7 = {EST, EST, SUD, SUD,   SUD,
                                             SUD, SUD, SUD, OUEST, OUEST};
    EXPECT_EQ(expected_path7, path7);
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

    EXPECT_EQ(alien.points_capture, st->get_score(PLAYER_1));
    EXPECT_EQ(0, st->get_score(PLAYER_2));
}
