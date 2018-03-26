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
    st->decrease_action_points(PLAYER_1, NB_POINTS_ACTION);

    ActionGlisser act(0, NORD, PLAYER_1);
    EXPECT_EQ(PA_INSUFFISANTS, act.check(st));
}

TEST_F(ActionTest, ActionGlisser_InvalidDirection)
{
    ActionGlisser act(0, (direction)10, PLAYER_1);
    EXPECT_EQ(DIRECTION_INVALIDE, act.check(st));
}

TEST_F(ActionTest, ActionGlisser_InvalidAgentID)
{
    ActionGlisser act(NB_AGENTS + 5, NORD, PLAYER_1);
    EXPECT_EQ(ID_AGENT_INVALIDE, act.check(st));
}
