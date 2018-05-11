#include "common.hh"

int get_closest_agent(int player_id, position dest)
{
    int min_dist = INF;
    int closest_agent = -1;
    for (int agent_id = 0; agent_id < NB_AGENTS; agent_id++)
    {
        if (player_id == moi() && is_coop_agent(agent_id))
            continue;
        position agent_pos = position_agent(player_id, agent_id);
        if (player_id == moi() && alien_sur_case(agent_pos))
            continue;
        int dist = cost_move(agent_pos, dest);
        if (dist < min_dist)
        {
            min_dist = dist;
            closest_agent = agent_id;
        }
    }
    return closest_agent;
}

alien_info get_closest_alien(int player_id, alien_info last_target)
{
    int round = tour_actuel();
    std::vector<alien_info> aliens = liste_aliens();
    sort_aliens_by_time(aliens);

    size_t next_to_spawn = 0;
    alien_info closest_alien{};
    int min_dist = INF;

    for (auto alien : aliens)
    {
        if (alien_sur_case(alien.pos) && alien != last_target &&
            !is_coop_target(alien) && agent_sur_case(alien.pos) != moi())
        {
            int closest_agent = get_closest_agent(player_id, alien.pos);
            if (closest_agent != -1)
            {
                position agent_pos = position_agent(player_id, closest_agent);
                int dist = cost_move(agent_pos, alien.pos);

                if (dist < min_dist)
                {
                    min_dist = dist;
                    closest_alien = alien;
                }
            }
        }

        if (round > alien.tour_invasion)
            next_to_spawn++;
    }

    if (min_dist == INF && next_to_spawn < aliens.size())
        closest_alien = aliens[next_to_spawn];
    return closest_alien;
}

position get_empty_cell_radius(position start, position dest, int radius)
{
    std::queue<std::pair<position, int>> q;
    std::array<std::array<bool, TAILLE_ICEBERG>, TAILLE_ICEBERG> seen{};
    int min_dist = INF;
    position best_cell = {-1, -1};
    q.push({dest, 0});
    while (!q.empty())
    {
        std::pair<position, int> cur = q.front();
        q.pop();
        if (cur.second == radius)
        {
            int dist = cost_move(start, cur.first);
            if (dist < min_dist)
            {
                min_dist = dist;
                best_cell = cur.first;
            }
            continue;
        }

        for (int dir = 0; dir < 4; dir++)
        {
            position neighbor = get_position_offset(cur.first, (direction)dir);
            if (inside_map(neighbor) && !is_obstacle(neighbor) &&
                !seen[neighbor.ligne][neighbor.colonne])
            {
                seen[neighbor.ligne][neighbor.colonne] = true;
                q.push({neighbor, cur.second + 1});
            }
        }
    }
    return best_cell;
}
