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

#include "../api.hh"

#include "test-helpers.hh"

TEST_F(ApiTest, Api_TypeCase)
{
    EXPECT_EQ(LIBRE, players[0].api->type_case({0, 0}));
    EXPECT_EQ(MUR, players[0].api->type_case(TEST_WALL));
}

TEST_F(ApiTest, Api_AgentSurCase)
{
    for (auto& player : players)
    {
        for (int agent_id = 0; agent_id < NB_AGENTS; agent_id++)
        {
            position agent_pos =
                player.api->position_agent(player.id, agent_id);
            EXPECT_EQ(agent_pos, st->get_agent_position(player.id, agent_id));
            EXPECT_TRUE(player.api->agent_sur_case(agent_pos));
        }
    }

    EXPECT_FALSE(players[0].api->agent_sur_case(TEST_EMPTY_CELL));
}

TEST_F(ApiTest, Api_AlienSurCase)
{
    std::vector<alien_info> aliens = st->get_alien_info();
    for (auto& player : players)
        for (auto& alien : aliens)
            EXPECT_TRUE(player.api->alien_sur_case(alien.pos));
    EXPECT_FALSE(players[0].api->alien_sur_case(TEST_EMPTY_CELL));
}

TEST_F(ApiTest, Api_PositionAgent)
{
    for (auto& player : players)
    {
        for (int agent_id = 0; agent_id < NB_AGENTS; agent_id++)
        {
            position agent_pos = st->get_agent_position(player.id, agent_id);
            EXPECT_EQ(agent_pos,
                      player.api->position_agent(player.id, agent_id));
        }
    }
}

TEST_F(ApiTest, Api_InfoAlien)
{
    std::vector<alien_info> aliens = st->get_alien_info();
    for (auto& player : players)
    {
        for (auto& expected : aliens)
        {
            alien_info alien = player.api->info_alien(expected.pos);
            EXPECT_EQ(expected, alien);
        }
    }
}

TEST_F(ApiTest, Api_ListeAliens)
{
    std::vector<alien_info> aliens = st->get_alien_info();
    for (auto& player : players)
        EXPECT_EQ(aliens, player.api->liste_aliens());
}

TEST_F(ApiTest, Api_ListeRafales)
{
}

TEST_F(ApiTest, Api_DirectionRafale)
{
}

TEST_F(ApiTest, Api_Historique)
{
    for (auto& player : players)
    {
        position agent_pos = player.api->position_agent(player.id, 0);
        agent_pos += offset[SUD];
        EXPECT_EQ(OK, player.api->deplacer(0, agent_pos));
        action_hist act1 = {ACTION_DEPLACER, 0, agent_pos, (direction)0};

        EXPECT_EQ(OK, player.api->glisser(1, SUD));
        action_hist act2 = {ACTION_GLISSER, 1, {0, 0}, SUD};

        EXPECT_EQ(OK, player.api->pousser(2, EST));
        action_hist act3 = {ACTION_POUSSER, 2, {0, 0}, EST};

        std::vector<action_hist> hist = {act1, act2, act3};
        std::vector<action_hist> expected =
            player.api->game_state()->get_history(player.id);
        EXPECT_EQ(expected, hist);
    }
}

TEST_F(ApiTest, Api_Score)
{
    std::vector<alien_info> aliens = st->get_alien_info();
    alien_info test_alien = aliens[0];
    st->set_agent_position(players[0].id, 0, test_alien.pos);
    for (int round = 0; round < NB_TOURS; round++)
    {
        st->increment_round();
        st->check_presence_alien();
        st->update_scores();
    }
    EXPECT_EQ(test_alien.puissance, players[0].api->score(players[0].id));
    EXPECT_EQ(0, players[1].api->score(players[1].id));
}

TEST_F(ApiTest, Api_Moi)
{
    for (auto& player : players)
        EXPECT_EQ(player.id, player.api->moi());
}

TEST_F(ApiTest, Api_Adversaire)
{
    for (int player_id = 0; player_id < 2; player_id++)
    {
        int expected = players[(player_id + 1) % 2].id;
        EXPECT_EQ(expected, players[player_id].api->adversaire());
    }
}

TEST_F(ApiTest, Api_Annuler)
{
    for (auto& player : players)
    {
        EXPECT_FALSE(player.api->annuler());

        position init = player.api->position_agent(player.id, 0);
        position pos{5, 5};
        EXPECT_EQ(OK, player.api->deplacer(0, pos));
        EXPECT_EQ(pos, player.api->position_agent(player.id, 0));
        EXPECT_TRUE(player.api->annuler());
        EXPECT_EQ(init, player.api->position_agent(player.id, 0));
    }
}

TEST_F(ApiTest, Api_TourActuel)
{
    for (int round = 0; round < NB_TOURS; round++)
    {
        for (auto& player : players)
            EXPECT_EQ(round, player.api->tour_actuel());
        st->increment_round();
    }
}

TEST_F(ApiTest, Api_PointsAction)
{
    for (auto& player : players)
    {
        for (int value : {0, 7, 10, 15, 36, 42})
        {
            st->reset_action_points(player.id);
            st->decrease_action_points(player.id, NB_POINTS_ACTION - value);
            EXPECT_EQ(value, player.api->points_action());
            EXPECT_EQ(value, st->get_action_points(player.id));
        }
    }
}
