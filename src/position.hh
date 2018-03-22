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
    return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const position& a, const position& b)
{
    return !(a == b);
}

inline bool operator<(const position& a, const position& b)
{
    return a.x < b.x && a.y < b.y;
}

inline position operator-(position a)
{
    return {-a.x, -a.y};
}

inline position& operator+=(position& lhs, position rhs)
{
    lhs.y += rhs.y;
    lhs.x += rhs.x;
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
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

inline bool inside_map(const position& pos)
{
    return pos.x >= 0 && pos.x < TAILLE_ICEBERG && pos.y >= 0 &&
           pos.y < TAILLE_ICEBERG;
}

// This is needed for old compilers
namespace std
{
template <> struct hash<position>
{
    std::size_t operator()(const position& p) const
    {
        std::size_t s = std::hash<int>()(p.y) + 0x9e3779b9;
        return s ^ (std::hash<int>()(p.x) + (s << 6) + (s >> 2));
    }
};
}

#endif
