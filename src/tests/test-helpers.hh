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

#ifndef TEST_HELPERS_HH
#define TEST_HELPERS_HH

#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

#include "../api.hh"
#include "../constant.hh"
#include "../game_state.hh"
#include "../position.hh"
#include "../rules.hh"

static const std::string test_map = "...............................\n"
                                    "...............................\n"
                                    "...X............X..............\n"
                                    "...............................\n"
                                    ".........XX....................\n"
                                    ".........XX....................\n"
                                    "...............................\n"
                                    "...X............X..............\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "...............................\n"
                                    "0 0\n" // Player 1 agents
                                    "0 1\n"
                                    "0 2\n"
                                    "0 3\n"
                                    "10 0\n" // Player 2 agents
                                    "10 1\n"
                                    "10 2\n"
                                    "10 3\n"
                                    "1\n" // Aliens
                                    "5 5 3 10 20\n";
static const position TEST_WALL = {2, 3};
static const position TEST_AGENT = {0, 1};
static const position TEST_EMPTY_CELL = {1, 1};

static rules::Players_sptr make_players(int id1, int id2)
{
    // Create two players (no spectator)
    return rules::Players_sptr(
        new rules::Players{std::vector<rules::Player_sptr>{
            rules::Player_sptr(new rules::Player(id1, rules::PLAYER)),
            rules::Player_sptr(new rules::Player(id2, rules::PLAYER)),
        }});
}

static GameState* make_test_gamestate(std::string map,
                                      const rules::Players_sptr& players)
{
    std::istringstream map_stream(map);
    return new GameState(map_stream, players);
}

class ActionTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        utils::Logger::get().level() = utils::Logger::DEBUG_LEVEL;
        st = make_test_gamestate(test_map, make_players(PLAYER_1, PLAYER_2));
    }

    virtual void TearDown() { delete st; }

    GameState* st;

    const int PLAYER_1 = 0;
    const int PLAYER_2 = 1;
};

class ApiTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        // Players values are not 0 and 1, because that would be too simple
        int player_id_1 = 1337;
        int player_id_2 = 42;
        utils::Logger::get().level() = utils::Logger::DEBUG_LEVEL;
        auto players_ptr = make_players(player_id_1, player_id_2);
        st = make_test_gamestate(test_map, players_ptr);
        players[0].id = player_id_1;
        players[0].api = new Api(st, players_ptr->players[0]);
        players[1].id = player_id_2;
        players[1].api = new Api(st, players_ptr->players[1]);
    }

    virtual void TearDown()
    {
        delete players[0].api;
        delete players[1].api;
    }

    GameState* st;

    struct Player
    {
        int id;
        Api* api;
    };
    std::array<Player, 2> players;
};

class RulesTest : public ::testing::Test
{
protected:
    constexpr static int PLAYER_ID_1 = 1;
    constexpr static int PLAYER_ID_2 = 2;

    virtual void SetUp()
    {
        utils::Logger::get().level() = utils::Logger::DEBUG_LEVEL;
        auto players_ptr = make_players(PLAYER_ID_1, PLAYER_ID_2);
        rules::Options opt;
        if (!std::ifstream("map.txt").good())
        {
            std::ofstream map("map.txt");
            map << test_map;
        }
        opt.map_file = "map.txt";
        opt.players = std::move(players_ptr);
        rules.reset(new Rules(opt));
    }

    std::unique_ptr<Rules> rules;
};

#endif
