// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2018 Paul Guénézan

#ifndef BFOR_CXX_STATE_HH
#define BFOR_CXX_STATE_HH

#include "prologin.hh"

#include <set>

namespace state
{
    static std::set<position> goals;
    static bool agent_has_goal;

    void new_turn();
    void new_agent(int id_agent);
    bool is_goal_free(position goal);
    void check_is_on_goal(int id_agent);
};

#endif //BFOR_CXX_STATE_HH
