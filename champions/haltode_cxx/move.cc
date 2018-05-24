// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2018 Thibault Allançon

#include "common.hh"

void do_actions(int agent_id, std::vector<action_hist> actions)
{
    for (auto action : actions)
    {
        erreur error = OK;
        if (action.type == ACTION_DEPLACER)
            error = deplacer(agent_id, action.dir);
        else if (action.type == ACTION_GLISSER)
            error = glisser(agent_id, action.dir);
        if (error != OK)
            break;
    }
}

void move_agent(int agent_id, position dest)
{
    position start = position_agent(moi(), agent_id);
    if (start == dest)
        return;
    std::vector<action_hist> actions = get_shortest_path(start, dest);
    do_actions(agent_id, actions);
}

void move_agent_radius(int agent_id, position dest, int radius)
{
    position start = position_agent(moi(), agent_id);
    position close_dest = get_empty_cell_radius(start, dest, radius);
    move_agent(agent_id, close_dest);
}

position simulate_slide(position start, direction dir)
{
    position pos = start, next_pos = start;
    do
    {
        pos = next_pos;
        next_pos = get_position_offset(next_pos, dir);
    } while (inside_map(next_pos) && !is_obstacle(next_pos));
    return pos;
}

int cost_action_points(std::vector<action_hist> path)
{
    int total = 0;
    for (auto action : path)
        total += cost_single_action(action);
    return total;
}

int cost_move(position start, position dest)
{
    std::vector<action_hist> path = get_shortest_path(start, dest);
    return cost_action_points(path);
}

int cost_turn(position start, position dest)
{
    std::vector<action_hist> path = get_shortest_path(start, dest);
    int turn = 0;
    int sum = 0;
    for (auto action : path)
    {
        int next = cost_single_action(action);
        if (sum + next > NB_POINTS_ACTION)
        {
            turn++;
            sum = 0;
        }
        sum += next;
    }
    return turn;
}

int cost_turn_with_push(position start, position dest)
{
    std::vector<action_hist> path = get_shortest_path(start, dest);
    int turn = 0;
    int sum = 0;
    for (auto action : path)
    {
        int next = cost_single_action(action);
        if (sum + next > NB_POINTS_ACTION)
        {
            turn++;
            sum = 0;
        }
        sum += next;
    }
    if (sum + COUT_POUSSER > NB_POINTS_ACTION)
        turn++;
    return turn;
}
