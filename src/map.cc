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

void Map::load_map_cells(std::istream& stream)
{
    for (int l = 0; l < TAILLE_BANQUISE; l++)
    {
        std::string line;
        stream >> line;
        if (line.length() != (size_t)TAILLE_BANQUISE)
            FATAL("map: line %d is not the right length "
                  "(is %d long, should be %d)",
                  l, line.length(), TAILLE_BANQUISE);

        for (int c = 0; c < TAILLE_BANQUISE; c++)
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
                FATAL("Invalid cell type '%c' at (%d;%d)", line[c], l, c);
                break;
            }
        }
    }
}

void Map::load_agents_info(std::istream& stream)
{
    std::vector<position> seen_agent_pos;
    for (int player = 0; player < 2; player++)
    {
        for (int agent = 0; agent < NB_AGENTS; agent++)
        {
            int l, c;
            stream >> l >> c;
            position pos = {l, c};

            bool is_agent_already_here = false;
            for (auto prev : seen_agent_pos)
                if (prev == pos)
                    is_agent_already_here = true;

            std::string error = "";
            if (is_agent_already_here)
                error = "already taken";
            if (!inside_map(pos))
                error = "outside of map";
            if (is_wall(pos))
                error = "a wall";

            if (error != "")
                FATAL("starting position (%d;%d) for player %d agent %d is %s",
                      l, c, player + 1, agent, error.c_str());

            start_position_[player][agent] = pos;
            seen_agent_pos.push_back(pos);
        }
    }
}

void Map::load_aliens_info(std::istream& stream)
{
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

        bool is_alien_already_here = false;
        for (int id = 0; id < alien; id++)
            if (alien_[id].pos == pos)
                is_alien_already_here = true;

        std::string error = "";
        if (is_alien_already_here)
            error = "already taken";
        if (!inside_map(pos))
            error = "outside of map";
        if (is_wall(pos))
            error = "a wall";

        if (error != "")
            FATAL("starting position (%d;%d) for alien %d is %s", l, c, alien,
                  error.c_str());
        if (round_spawn < 0 || round_spawn >= NB_TOURS)
            FATAL("invalid spawn round %d for alien %d", round_spawn, alien);

        alien_[alien] = alien_info{pos, nb_point, round_spawn, round_span, 0};
        is_alien_on_map_[alien] = false;
    }
}

Map::Map(std::istream& stream)
{
    INFO("Loading map");

    load_map_cells(stream);
    load_agents_info(stream);
    load_aliens_info(stream);
}

case_type Map::get_cell_type(position pos) const
{
    if (inside_map(pos))
        return map_[pos.ligne][pos.colonne];
    else
        return ERREUR;
}

bool Map::is_wall(position pos) const
{
    return get_cell_type(pos) == MUR;
}

const std::array<position, NB_AGENTS>&
Map::get_start_position(int player_id) const
{
    assert(player_id >= 0 && player_id < 2);
    return start_position_[player_id];
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

bool Map::is_alien_on_position(position pos) const
{
    for (size_t id = 0; id < alien_.size(); id++)
        if (alien_[id].pos == pos && is_alien_on_map_[id])
            return true;
    return false;
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
    assert(alien_id >= 0 && alien_id < (int)alien_.size());
    return alien_[alien_id].capture_en_cours == NB_TOURS_CAPTURE;
}

void Map::increment_alien_capture_time(position pos)
{
    for (size_t id = 0; id < alien_.size(); id++)
    {
        if (alien_[id].pos == pos && is_alien_on_map_[id] &&
            !is_alien_captured(id))
        {
            alien_[id].capture_en_cours++;
            if (is_alien_captured(id))
                is_alien_on_map_[id] = false;
        }
    }
}

void Map::reset_alien_capture_time(position pos)
{
    for (size_t id = 0; id < alien_.size(); id++)
        if (alien_[id].pos == pos && !is_alien_captured(id))
            alien_[id].capture_en_cours = 0;
}
