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
