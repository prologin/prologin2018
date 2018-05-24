// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2018 Paul Guénézan

#include "agent.hh"

#include "prologin.hh"

bool agent::on_alien(int id_agent)
{
    return alien_sur_case(position_agent(moi(), id_agent));
}

int agent::action_pts(int id_agent)
{
    return points_action_agent(id_agent);
}
