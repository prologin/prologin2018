// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2018 Paul Guénézan

#ifndef BFOR_CXX_POSITION_HH
#define BFOR_CXX_POSITION_HH

#include <vector>

#include "prologin.hh"

namespace pos
{
    bool is_valid(const position &position);
    bool is_free(const position &position);
    std::vector<action_hist> shortest_path(position a, position b, int id_agent);
    std::vector<alien_info> current_aliens();
}

#endif //BFOR_CXX_POSITION_HH
