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

#ifndef POSITION_HH
#define POSITION_HH

#include <cstdlib>
#include <functional>

#include "constant.hh"

inline bool operator==(const position& a, const position& b)
{
    return a.ligne == b.ligne && a.colonne == b.colonne;
}

inline bool operator!=(const position& a, const position& b)
{
    return !(a == b);
}

inline bool operator<(const position& a, const position& b)
{
    return a.ligne < b.ligne && a.colonne < b.colonne;
}

inline position operator-(position a)
{
    return {-a.ligne, -a.colonne};
}

inline position& operator+=(position& lhs, position rhs)
{
    lhs.colonne += rhs.colonne;
    lhs.ligne += rhs.ligne;
    return lhs;
}

inline position& operator-=(position& lhs, position rhs)
{
    return lhs += -rhs;
}

inline position operator+(position lhs, position rhs)
{
    return lhs += rhs;
}

inline position operator-(position lhs, position rhs)
{
    return lhs -= rhs;
}

inline int distance(const position& a, const position& b)
{
    return std::abs(a.ligne - b.ligne) + std::abs(a.colonne - b.colonne);
}

inline bool inside_map(const position& pos)
{
    return pos.ligne >= 0 && pos.ligne < TAILLE_BANQUISE && pos.colonne >= 0 &&
           pos.colonne < TAILLE_BANQUISE;
}

static const position offset[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

inline position get_position_offset(const position pos, const direction dir)
{
    return pos + offset[dir];
}

inline direction opposite_dir(direction dir)
{
    if (dir == NORD)
        return SUD;
    else if (dir == EST)
        return OUEST;
    else if (dir == SUD)
        return NORD;
    else
        return EST;
}

// This is needed for old compilers
namespace std
{
template <> struct hash<position>
{
    std::size_t operator()(const position& p) const
    {
        std::size_t s = std::hash<int>()(p.colonne) + 0x9e3779b9;
        return s ^ (std::hash<int>()(p.ligne) + (s << 6) + (s >> 2));
    }
};
}

#endif
