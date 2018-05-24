// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2018 Thibault Allançon

#include "common.hh"

alien_info solo_targets[NB_AGENTS];
bool has_targets[NB_AGENTS];

void play_solo_mode()
{
    init_solo_targets();
    for (int agent = 0; agent < NB_AGENTS; agent++)
    {
        if (is_coop_agent(agent))
            continue;
        position agent_pos = position_agent(moi(), agent);
        if (alien_sur_case(agent_pos))
        {
            push_around(agent);
            return;
        }

        alien_info target = solo_targets[agent];

        debug_afficher_drapeau(target.pos, DRAPEAU_ROUGE);

        move_agent(agent, target.pos);
        if (agent_sur_case(target.pos) == adversaire())
        {
            std::pair<position, direction> res =
                get_push_cell(agent, target.pos);
            if (res.first == (position){-1, -1})
                continue;
            move_agent(agent, res.first);
            pousser(agent, res.second);
        }
    }
}

void init_solo_targets()
{
    for (int id = 0; id < NB_AGENTS; id++)
        has_targets[id] = false;

    for (int id = 0; id < NB_AGENTS; id++)
    {
        if (is_coop_agent(id))
            continue;
        position agent_pos = position_agent(moi(), id);
        if (alien_sur_case(agent_pos))
            has_targets[id] = true;
    }

    const alien_info no_target = {{-1, -1}, -1, -1, -1, -1};
    alien_info possible_targets[2];
    possible_targets[0] = get_closest_alien(moi(), no_target);
    possible_targets[1] = get_closest_alien(moi(), possible_targets[0]);

    for (int agent = 0; agent < NB_AGENTS; agent++)
    {
        if (is_coop_agent(agent) || has_targets[agent])
            continue;
        for (int target = 0; target < 2; target++)
        {
            if (possible_targets[target] != no_target)
            {
                solo_targets[agent] = possible_targets[target];
                has_targets[agent] = true;
                possible_targets[target] = no_target;
                break;
            }
        }
    }
}
