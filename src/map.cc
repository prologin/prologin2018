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

#include <utils/log.hh>

#include <cassert>

#include "map.hh"

Map::Map(std::istream& stream)
{
    INFO("Loading map");

    for (int l = 0; l < TAILLE_ICEBERG; l++)
    {
        std::string line;
        stream >> line;
        if (line.length() != (size_t)TAILLE_ICEBERG)
            FATAL("map: line %d is not the right length "
                  "(is %d long, should be %d)",
                  l, line.length(), TAILLE_ICEBERG);

        for (int c = 0; c < TAILLE_ICEBERG; c++)
        {
            switch (line[c])
            {
            case '.':
                map_[l][c] = LIBRE;
                break;
            case 'X':
                map_[l][c] = MUR;
                break;
            default:
                FATAL("Invalid cell at (%d;%d)", l, c);
                break;
            }
        }
    }

    for (int player = 0; player < 2; player++)
    {
        for (int agent = 0; agent < NB_AGENTS; agent++)
        {
            int l, c;
            stream >> l >> c;
            position pos = {l, c};
            if (!inside_map(pos))
                FATAL("starting position (%d;%d) for player %d is invalid", l,
                      c, player + 1);
            start_position_[player][agent] = pos;
        }
    }

    int nb_alien;
    stream >> nb_alien;
    alien_.resize(nb_alien);
    for (int alien = 0; alien < nb_alien; alien++)
    {
        int l, c, p;
        stream >> l >> c >> p;
        position pos = {l, c};
        if (!inside_map(pos))
            FATAL("starting position (%d;%d) for alien %d is invalid", l, c,
                  alien + 1);
        alien_[alien] = alien_info{pos, p};
    }
}

case_type Map::get_cell_type(position pos) const
{
    if (inside_map(pos))
        return map_[pos.ligne][pos.colonne];
    else
        return case_type::ERREUR;
}

bool Map::is_empty(position pos) const
{
    return get_cell_type(pos) == LIBRE;
}

bool Map::is_wall(position pos) const
{
    return get_cell_type(pos) == MUR;
}

const std::array<position, NB_AGENTS>&
Map::get_start_position(unsigned int player_id) const
{
    assert(player_id < 2);
    return start_position_[player_id];
}

const std::vector<alien_info>& Map::get_alien_info() const
{
    return alien_;
}
