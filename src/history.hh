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

#ifndef HISTORY_HH
#define HISTORY_HH

#include "constant.hh"

typedef struct debug_flag_info
{
    debug_drapeau ftype;
    position pos;
} debug_flag_info;

// We do not want unused debug flag info to appear in the public API, so using
// only action_hist is not enough to store the complete internal history.
typedef struct internal_action
{
    int atype;
    union {
        debug_flag_info debug_flag;
        action_hist move_action;
    };
} internal_action;

#endif
