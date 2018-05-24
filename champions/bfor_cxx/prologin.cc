// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2018 Paul Guénézan

#include "prologin.hh"

#include "action.hh"
#include "agent.hh"
#include "state.hh"

void partie_init()
{
}
void jouer_tour()
{
    state::new_turn();
    for(int id_agent = 0; id_agent < NB_AGENTS; ++id_agent)
    {
        state::new_agent(id_agent);
        if(agent::on_alien(id_agent))
        {
            continue;
        }
        action::attack(id_agent, agent::action_pts(id_agent));
        action::capture(id_agent);
        if(!agent::on_alien(id_agent))
            action::attack(id_agent, agent::action_pts(id_agent));
    }
}
void partie_fin()
{
}
