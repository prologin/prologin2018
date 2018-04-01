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

    // Map
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

    // Agents
    for (int player = 0; player < 2; player++)
    {
        for (int agent = 0; agent < NB_AGENTS; agent++)
        {
            int l, c;
            stream >> l >> c;
            position pos = {l, c};
            if (!inside_map(pos) || is_wall(pos))
                FATAL("starting position (%d;%d) for player %d is invalid", l,
                      c, player + 1);
            start_position_[player][agent] = pos;
        }
    }

    // Aliens
    int nb_alien;
    stream >> nb_alien;
    alien_.resize(nb_alien);
    is_alien_on_map_.resize(nb_alien);
    for (int alien = 0; alien < nb_alien; alien++)
    {
        int l, c;
        int nb_point;
        int round_spawn, round_span;
        stream >> l >> c >> nb_point >> round_spawn >> round_span;
        position pos = {l, c};
        if (!inside_map(pos) || is_wall(pos))
            FATAL("starting position (%d;%d) for alien %d is invalid", l, c,
                  alien + 1);
        alien_[alien] = alien_info{pos, nb_point, round_spawn, round_span, 0};
        is_alien_on_map_[alien] = false;
    }

    // Storms
    int nb_storm;
    stream >> nb_storm;
    storm_round_.resize(nb_storm);
    for (int storm = 0; storm < nb_storm; storm++)
    {
        stream >> storm_round_[storm];
        if (storm_round_[storm] < 0 || storm_round_[storm] >= NB_TOURS)
            FATAL("invalid storm round %d", storm_round_[storm]);
    }
    std::string dir;
    stream >> dir;
    if (dir == "NORD")
        storm_dir_ = direction::NORD;
    else if (dir == "EST")
        storm_dir_ = direction::EST;
    else if (dir == "SUD")
        storm_dir_ = direction::SUD;
    else if (dir == "OUEST")
        storm_dir_ = direction::OUEST;
    else
        FATAL("unknown direction %s", dir);
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

std::array<position, NB_AGENTS> Map::get_start_position(int player_id) const
{
    assert(player_id < 2);
    return start_position_[player_id];
}

bool Map::is_alien_on_position(position pos) const
{
    for (auto alien : alien_)
        if (alien.pos == pos)
            return true;
    return false;
}

std::vector<alien_info> Map::get_alien_info() const
{
    return alien_;
}

alien_info Map::get_alien_info(position pos) const
{
    for (auto alien : alien_)
        if (alien.pos == pos)
            return alien;
    return alien_info{};
}

void Map::check_presence_alien(int round)
{
    for (size_t id = 0; id < alien_.size(); id++)
    {
        if (alien_[id].tour_invasion == round)
            is_alien_on_map_[id] = true;
        else if (alien_[id].tour_invasion + alien_[id].duree_invasion == round)
            is_alien_on_map_[id] = false;
    }
}

bool Map::is_alien_captured(int alien_id) const
{
    assert(alien_id < (int)alien_.size());
    return alien_[alien_id].capture_en_cours == NB_TOURS_CAPTURE;
}

std::vector<alien_info> Map::get_captured_alien()
{
    std::vector<alien_info> captured_alien;
    for (size_t id = 0; id < alien_.size(); id++)
        if (is_alien_on_map_[id] && !is_alien_captured(id))
        {
            alien_[id].capture_en_cours++;
            if (is_alien_captured(id))
            {
                is_alien_on_map_[id] = false;
                captured_alien.emplace_back(alien_[id]);
            }
        }
    return captured_alien;
}

void Map::reset_alien_capture_time(position pos)
{
    for (size_t id = 0; id < alien_.size(); id++)
        if (alien_[id].pos == pos && !is_alien_captured(id))
            alien_[id].capture_en_cours = 0;
}

std::vector<int> Map::get_storm_info() const
{
    return storm_round_;
}

direction Map::get_storm_dir() const
{
    return storm_dir_;
}

bool Map::is_storm_round(int round) const
{
    for (size_t id = 0; id < storm_round_.size(); id++)
        if (storm_round_[id] == round)
            return true;
    return false;
}
