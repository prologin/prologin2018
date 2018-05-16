#include "action.hh"

#include "direction.hh"
#include "position.hh"
#include "state.hh"

using namespace std;

erreur action::execute(const action_hist &action)
{
    if(action.type == ACTION_DEPLACER)
        return deplacer(action.id_agent, action.dir);
    if(action.type == ACTION_GLISSER)
        return glisser(action.id_agent, action.dir);
    return pousser(action.id_agent, action.dir);
}

erreur action::execute(const vector<action_hist> &actions)
{
    for(const action_hist &action : actions)
    {
        erreur error = execute(action);
        if(error != OK)
            return error;
    }
    return OK;
}

int action::cost(const action_hist &action)
{
    if(action.type == ACTION_DEPLACER)
        return COUT_DEPLACEMENT;
    if(action.type == ACTION_GLISSER)
        return COUT_GLISSADE;
    return COUT_POUSSER;
}

int action::cost(const vector<action_hist> &actions)
{
    int sum = 0;
    for(const action_hist &action : actions)
        sum += cost(action);
    return sum;
}

void action::attack(int id_agent, int max_cost)
{
    int max_score = 0;
    bool has_action = false;
    vector<action_hist> best_actions;
    for(int id_foe = 0; id_foe < NB_AGENTS; ++id_foe)
        for(direction dir : dir::all)
        {
            position pos_foe = position_agent(adversaire(), id_foe);
            position goal = dir::offset(pos_foe, dir);
            if(!pos::is_free(goal))
                continue;
            position my_pos = position_agent(moi(), id_agent);
            vector<action_hist> actions = pos::shortest_path(my_pos, goal, id_agent);
            if(cost(actions) <= max_cost - COUT_POUSSER)
            {
                direction push_dir = dir::get(goal, pos_foe);
                int foe_push = dir::slide_distance(pos_foe, push_dir);
                if(max_score < foe_push)
                {
                    max_score = foe_push;
                    best_actions = actions;
                    best_actions.push_back({ ACTION_POUSSER, id_agent, push_dir });
                    has_action = true;
                }
            }
        }
    if(has_action)
    {
        execute(best_actions);
        state::check_is_on_goal(id_agent);
    }
}

void action::capture(int id_agent)
{
    position my_pos = position_agent(moi(), id_agent);
    vector<action_hist> best_actions;
    bool has_action = false;
    int max_score = 0;
    for(alien_info alien : pos::current_aliens())
        if(state::is_goal_free(alien.pos))
        {
            vector<action_hist> actions = pos::shortest_path(my_pos, alien.pos, id_agent);
            if(actions.size() == 0)
                continue;
            int score = alien.points_capture * TAILLE_BANQUISE * TAILLE_BANQUISE;
            score -= cost(actions);
            if(score > max_score)
            {
                max_score = score;
                best_actions = actions;
                has_action = true;
            }
        }
    if(has_action)
    {
        execute(best_actions);
        state::check_is_on_goal(id_agent);
    }
}
