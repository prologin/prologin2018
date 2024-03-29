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
    Map(const Map& map);

    case_type get_cell_type(position pos) const;
    bool is_empty(position pos) const;
    bool is_wall(position pos) const;

    const std::array<position, NB_AGENTS>&
    get_start_position(int player_id) const;

    std::vector<alien_info> get_alien_info() const;
    alien_info get_alien_info(position pos) const;
    bool is_alien_on_position(position pos) const;
    void check_presence_alien(int round);
    bool is_alien_captured(int alien_id) const;
    void increment_alien_capture_time(position pos);
    void reset_alien_capture_time(position pos);

private:
    void load_map_cells(std::istream& stream);
    void load_agents_info(std::istream& stream);
    void load_aliens_info(std::istream& stream);

    std::array<std::array<case_type, TAILLE_BANQUISE>, TAILLE_BANQUISE> map_;

    std::array<std::array<position, NB_AGENTS>, 2> start_position_;

    std::vector<alien_info> alien_;
    std::vector<bool> is_alien_on_map_;
};

#endif
