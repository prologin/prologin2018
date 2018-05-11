#include "position.hh"

#include <algorithm>
#include <array>
#include <queue>

#include "direction.hh"

using namespace std;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;

bool pos::is_valid(const position &position)
{
    return position.colonne >= 0
           && position.ligne >= 0
           && position.colonne < TAILLE_ICEBERG
           && position.ligne < TAILLE_ICEBERG;
}

bool pos::is_free(const position &position)
{
    return is_valid(position)
           && type_case(position) != MUR
           && agent_sur_case(position) == -1;
}

vector<action_hist> pos::shortest_path(position a, position b, int id_agent)
{
    min_queue<pair<int, position>> queue;
    queue.push({ 0, a });
    array<array<pair<action_hist, position>, TAILLE_ICEBERG>, TAILLE_ICEBERG> trace {};
    array<array<bool, TAILLE_ICEBERG>, TAILLE_ICEBERG> seen {};
    while(!queue.empty())
    {
        pair<int, position> current = queue.top();
        position cpos = current.second;
        queue.pop();
        if(cpos == b)
        {
            vector<action_hist> actions;
            while(cpos != a)
            {
                actions.push_back(trace[cpos.ligne][cpos.colonne].first);
                cpos = trace[cpos.ligne][cpos.colonne].second;
            }
            reverse(actions.begin(), actions.end());
            return actions;

        }
        for(direction dir : dir::all)
        {
            vector<tuple<position, action_type, int>> actions;
            actions.push_back({ dir::offset(cpos, dir), ACTION_DEPLACER, COUT_DEPLACEMENT });
            actions.push_back({ dir::slide(cpos, dir), ACTION_GLISSER, COUT_GLISSADE });
            for(const auto &action : actions)
            {
                position npos = get<0>(action);
                if(pos::is_free(npos) && !seen[npos.ligne][npos.colonne])
                {
                    seen[npos.ligne][npos.colonne] = true;
                    trace[npos.ligne][npos.colonne] = { { get<1>(action), id_agent, dir }, cpos };
                    queue.push({ current.first + get<2>(action), npos });
                };
            }
        }
    }
    return {};
}

vector<alien_info> pos::current_aliens()
{
    vector<alien_info> aliens;
    for(const alien_info &alien : liste_aliens())
        if(alien_sur_case(alien.pos))
            aliens.push_back(alien);
    return aliens;
}
