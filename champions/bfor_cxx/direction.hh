// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2018 Paul Guénézan

#ifndef BFOR_CXX_DIRECTION_HH
#define BFOR_CXX_DIRECTION_HH

#include "prologin.hh"

namespace dir
{
    const direction all[4] { NORD, EST, SUD, OUEST };
    position offset(position position, const direction &direction);
    position slide(position position, const direction &direction);
    int slide_distance(position position, const direction &direction);
    direction get(const position &a, const position &b);
}

#endif //BFOR_CXX_DIRECTION_HH
