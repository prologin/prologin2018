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

#include "test-helpers.hh"

TEST_F(RulesTest, Rules_Finish)
{
    int round = 0;
    while (!rules->is_finished())
    {
        rules->start_of_round();

        rules->start_of_player_turn(PLAYER_ID_1);
        rules->end_of_player_turn(PLAYER_ID_1);

        EXPECT_FALSE(rules->is_finished());

        rules->start_of_player_turn(PLAYER_ID_2);
        rules->end_of_player_turn(PLAYER_ID_2);

        EXPECT_EQ(round, rules->game_state().get_round());
        rules->end_of_round();

        round++;
    }
    EXPECT_EQ(NB_TOURS, round);
}
