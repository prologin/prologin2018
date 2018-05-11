#include "common.hh"

std::pair<position, direction> get_push_cell(int agent_id, position target)
{
    // TODO: check for action points
    std::vector<std::pair<int, direction>> possible;
    for (int idir = 0; idir < 4; idir++)
    {
        direction dir = (direction)idir;
        position off = get_position_offset(target, dir);
        int dist = manhattan_dist(target, simulate_slide(off, dir));
        if (dist >= 1 && !is_obstacle(off))
            possible.push_back({dist, dir});
    }

    std::sort(possible.begin(), possible.end(),
              std::greater<std::pair<int, direction>>());

    int min_dist = INF;
    direction best_dir;
    for (auto p : possible)
    {
        direction push_dir = p.second;
        position push_cell =
            get_position_offset(target, opposite_dir(push_dir));

        position agent_pos = position_agent(moi(), agent_id);
        int dist = cost_move(agent_pos, push_cell);
        int action_points = points_action_agent(agent_id);
        if (dist + COUT_POUSSER <= action_points)
        {
            if (dist < min_dist)
            {
                min_dist = dist;
                best_dir = p.second;
            }
        }
    }

    if (min_dist == INF)
    {
        position invalid = {-1, -1};
        return std::make_pair(invalid, NORD);
    }

    position push_cell = get_position_offset(target, opposite_dir(best_dir));
    return {push_cell, best_dir};
}

void push_around(int agent_id)
{
    position agent_pos = position_agent(moi(), agent_id);
    int max_dist = 0;
    int best_dir = -1;
    for (int idir = 0; idir < 4; idir++)
    {
        direction dir = (direction)idir;
        position adjacent = get_position_offset(agent_pos, dir);
        if (agent_sur_case(adjacent) == adversaire())
        {
            int dist = manhattan_dist(agent_pos, simulate_slide(adjacent, dir));
            if (dist > max_dist)
            {
                max_dist = dist;
                best_dir = idir;
            }
        }
    }

    if (best_dir == -1)
        return;

    direction dir = (direction)best_dir;
    pousser(agent_id, dir);
}
