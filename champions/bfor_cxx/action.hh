#ifndef BFOR_CXX_ACTION_HH
#define BFOR_CXX_ACTION_HH

#include <vector>

#include "prologin.hh"

namespace action
{
    erreur execute(const action_hist &action);
    erreur execute(const std::vector<action_hist> &actions);
    int cost(const action_hist &action);
    int cost(const std::vector<action_hist> &actions);
    void attack(int id_agent, int max_cost);
    void capture(int id_agent);
}

#endif //BFOR_CXX_ACTION_HH
