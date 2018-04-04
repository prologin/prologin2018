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

#ifndef STRUCT_HELPER_HH
#define STRUCT_HELPER_HH

#include "constant.hh"
#include "position.hh"

inline bool operator==(const alien_info& a, const alien_info& b)
{
    return a.pos == b.pos && a.puissance == b.puissance &&
           a.tour_invasion == b.tour_invasion &&
           a.duree_invasion == b.duree_invasion &&
           a.capture_en_cours == b.capture_en_cours;
}

inline bool operator==(const action_hist& a, const action_hist& b)
{
    return a.type == b.type && a.id_agent == b.id_agent && a.dir == b.dir;
}

#endif
