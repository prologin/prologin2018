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

#ifndef MAP_HH
#define MAP_HH

#include <array>
#include <istream>
#include <vector>

#include "constant.hh"
#include "position.hh"

class Map
{
public:
    Map(std::istream& stream);

    bool is_empty(position pos) const;
    bool is_wall(position pos) const;

    const std::array<position, NB_AGENTS>&
    get_start_position(unsigned int player_id) const;
    const std::vector<alien_info>& get_alien_info() const;

private:
    std::array<std::array<case_type, TAILLE_ICEBERG>, TAILLE_ICEBERG> map_;

    std::array<std::array<position, NB_AGENTS>, 2> start_position_;
    std::vector<alien_info> alien_;
};

#endif
