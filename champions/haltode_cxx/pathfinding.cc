#include "common.hh"

template <class T>
using min_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

std::vector<action_hist> get_shortest_path(position start, position dest)
{
    min_queue<std::pair<int, position>> q;
    std::array<std::array<bool, TAILLE_ICEBERG>, TAILLE_ICEBERG> seen{};
    std::array<std::array<std::pair<action_hist, position>, TAILLE_ICEBERG>,
               TAILLE_ICEBERG>
        backtrace{};

    q.push({0, start});
    while (!q.empty())
    {
        std::pair<int, position> cur = q.top();
        position pos = cur.second;
        q.pop();

        for (int idir = 0; idir < 4; idir++)
        {
            direction dir = (direction)idir;
            // Two possible actions: move to adjacent cell or slide
            std::array<std::pair<position, std::pair<action_type, int>>, 2>
                actions;
            actions[0] = {get_position_offset(pos, dir),
                          {ACTION_DEPLACER, COUT_DEPLACEMENT}};
            actions[1] = {simulate_slide(pos, dir),
                          {ACTION_GLISSER, COUT_GLISSADE}};
            for (int act = 0; act < 2; act++)
            {
                position next_pos = actions[act].first;
                action_type type = actions[act].second.first;
                int cost = actions[act].second.second;

                // We do not care if there is an agent on position
                if (next_pos == dest)
                {
                    action_hist action = {type, 0, dir};
                    backtrace[next_pos.ligne][next_pos.colonne] = {action, pos};
                    // Extract path from backtrace
                    std::vector<action_hist> path;
                    while (next_pos != start)
                    {
                        action_hist action =
                            backtrace[next_pos.ligne][next_pos.colonne].first;
                        next_pos =
                            backtrace[next_pos.ligne][next_pos.colonne].second;
                        path.push_back(action);
                    }
                    std::reverse(path.begin(), path.end());
                    return path;
                }

                if (inside_map(next_pos) &&
                    !seen[next_pos.ligne][next_pos.colonne] &&
                    !is_obstacle(next_pos))
                {
                    seen[next_pos.ligne][next_pos.colonne] = true;
                    action_hist action = {type, 0, dir};
                    backtrace[next_pos.ligne][next_pos.colonne] = {action, pos};
                    q.push({cur.first + cost, next_pos});
                }
            }
        }
    }

    return {};
}
