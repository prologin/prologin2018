#include "state.hh"

#include "position.hh"

void state::new_turn()
{
    goals.clear();
    for(alien_info alien : pos::current_aliens())
        if(agent_sur_case(alien.pos) == moi())
            goals.insert(alien.pos);
}

void state::new_agent(int id_agent)
{
    agent_has_goal = alien_sur_case(position_agent(moi(), id_agent));
}

bool state::is_goal_free(position goal)
{
    return goals.find(goal) == goals.end();
}

void state::check_is_on_goal(int id_agent)
{
    if(alien_sur_case(position_agent(moi(), id_agent)))
    {
        goals.insert(position_agent(moi(), id_agent));
        agent_has_goal = true;
    }
}
