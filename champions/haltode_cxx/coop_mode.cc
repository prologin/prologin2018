#include "common.hh"

const int RADIUS_TO_TARGET = 2;

alien_info coop_target;
int coop_agents[2];
bool has_target;

void play_coop_mode()
{
    if (!has_target || !alien_sur_case(coop_target.pos))
    {
        choose_coop_target();
        choose_coop_agents();
    }

    if (!has_target)
        return;

    debug_afficher_drapeau(coop_target.pos, DRAPEAU_VERT);

    // Move agents close to target
    if (agent_sur_case(coop_target.pos) != moi())
    {
        for (int id = 0; id < 2; id++)
        {
            position agent_pos = position_agent(moi(), coop_agents[id]);
            if (manhattan_dist(agent_pos, coop_target.pos) > RADIUS_TO_TARGET)
            {
                if (agent_sur_case(coop_target.pos) == adversaire())
                    move_agent_radius(coop_agents[id], coop_target.pos,
                                      RADIUS_TO_TARGET);
                else
                    move_agent(coop_agents[id], coop_target.pos);
            }
        }
    }

    // Defend target if on it
    if (agent_sur_case(coop_target.pos) == moi())
    {
        for (int id = 0; id < 2; id++)
        {
            if (position_agent(moi(), coop_agents[id]) == coop_target.pos)
            {
                push_around(coop_agents[id]);
                guard_mode_coop(coop_agents[(id + 1) % 2]);
                push_around(coop_agents[(id + 1) % 2]);
                return;
            }
        }
    }

    // Push ennemy from target
    if (agent_sur_case(coop_target.pos) == adversaire())
        push_ennemy_from_coop_target();

    // Defense mode
    int action_points0 = points_action_agent(coop_agents[0]);
    int action_points1 = points_action_agent(coop_agents[1]);
    if (action_points0 < action_points1 && action_points0 > 0)
    {
        move_agent(coop_agents[0], coop_target.pos);
        guard_mode_coop(coop_agents[1]);
    }
    else if (action_points1 > 0)
    {
        move_agent(coop_agents[1], coop_target.pos);
        guard_mode_coop(coop_agents[0]);
    }

    // TODO: push around?
    // for (int id = 0; id < 2; id++)
    //    push_around(coop_agents[id]);
}

void choose_coop_target()
{
    int round = tour_actuel();
    std::vector<alien_info> aliens = liste_aliens();
    sort_aliens_by_time(aliens);
    int best_score = 0;
    alien_info best_alien{};

    // Choose best alien
    for (size_t id = 0; id < aliens.size(); id++)
    {
        alien_info alien = aliens[id];
        // We look at max 10 round ahead (or more if we don't find anything)
        if (alien.tour_invasion - round > 10 && best_score != 0)
            break;
        if (!alien_shoud_be_on_round(alien) && best_score != 0)
            break;
        if (alien_shoud_be_on_round(alien) && !alien_sur_case(alien.pos))
            continue;
        // TODO: we don't always ignore aliens where we cannot push (eg: when we
        // can go on it first)
        if (!can_push_agent_from(alien.pos))
            continue;
        // Too open
        if (cnt_open_dir(alien.pos) == 4)
            continue;
        // Someone is capturing it (and we don't have time to get it)
        int agent_id = get_closest_agent(moi(), alien.pos);
        position agent_pos = position_agent(moi(), agent_id);
        int nb_turn = cost_turn_with_push(agent_pos, alien.pos);
        if (alien.capture_en_cours != 0 &&
            nb_turn >= NB_TOURS_CAPTURE - alien.capture_en_cours)
            continue;
        int start = alien.tour_invasion;
        int end = start + alien.duree_invasion;
        start = std::max(start, round);
        end = std::min(end, NB_TOURS - 1);
        if (end - start <= NB_TOURS_CAPTURE)
            continue;

        if (alien.points_capture > best_score)
        {
            best_score = alien.points_capture;
            best_alien = alien;
        }
    }

    if (best_score != 0)
    {
        coop_target = best_alien;
        has_target = true;
    }
    else
    {
        std::cout << "no target :(\n";
        has_target = false;
    }
}

// Choose agents closest to target alien
void choose_coop_agents()
{
    if (!has_target)
        return;

    int min0 = INF;
    int min1 = INF;
    for (int agent = 0; agent < NB_AGENTS; agent++)
    {
        position agent_pos = position_agent(moi(), agent);
        int dist = cost_move(agent_pos, coop_target.pos);
        if (dist < min0)
        {
            min1 = min0;
            coop_agents[1] = coop_agents[0];
            min0 = dist;
            coop_agents[0] = agent;
        }
        else if (dist < min1)
        {
            min1 = dist;
            coop_agents[1] = agent;
        }
    }
}

void guard_mode_coop(int agent_id)
{
    // If adjacent wall next to target: try put agent in diag to block off any
    // push
    int min_dist = INF;
    position best_cell{};
    for (int idir = 0; idir < 4; idir++)
    {
        direction dir = (direction)idir;
        position pos = get_position_offset(coop_target.pos, dir);
        if (type_case(pos) == MUR)
        {
            direction best_dir = (direction)(((idir - 1) + 4) % 4);
            position cell = get_position_offset(coop_target.pos, best_dir);
            std::pair<direction, direction> orth = orth_dir(best_dir);
            position slide_end1 = simulate_slide(cell, orth.first);
            position slide_end2 = simulate_slide(cell, orth.second);
            int dist1 = manhattan_dist(cell, slide_end1);
            int dist2 = manhattan_dist(cell, slide_end2);
            int dist = std::max(dist1, dist2);
            if (dist < min_dist)
            {
                min_dist = dist;
                best_cell = cell;
            }
        }
    }

    if (min_dist != INF)
    {
        move_agent(agent_id, best_cell);
        return;
    }

    // Otherwise, simply try to put the agent between the other coop agent and
    // the ennemy
    position agent_pos = position_agent(moi(), agent_id);
    int dir_to_guard = -1;
    int min_cost = INF;
    for (int idir = 0; idir < 4; idir++)
    {
        direction dir = (direction)idir;
        position pos = get_position_offset(coop_target.pos, dir);
        while (inside_map(pos) && type_case(pos) == LIBRE &&
               agent_sur_case(pos) == -1)
            pos = get_position_offset(pos, dir);
        if (agent_sur_case(pos) == adversaire())
        {
            position to_guard = get_position_offset(coop_target.pos, dir);
            int dist = cost_move(agent_pos, to_guard);
            if (dist < min_cost)
            {
                min_cost = dist;
                dir_to_guard = idir;
            }
        }
    }
    if (dir_to_guard != -1)
    {
        direction dir = (direction)dir_to_guard;
        position to_guard = get_position_offset(coop_target.pos, dir);
        move_agent(agent_id, to_guard);
    }
}

void push_ennemy_from_coop_target()
{
    int min_dist = INF;
    direction best_dir;
    int best_id = -1;
    for (int id = 0; id < 2; id++)
    {
        std::pair<position, direction> res =
            get_push_cell(coop_agents[id], coop_target.pos);
        if (res.first == (position){-1, -1})
            continue;
        position agent_pos = position_agent(moi(), coop_agents[id]);
        int dist = cost_move(agent_pos, res.first);
        int action_points = points_action_agent(coop_agents[id]);
        if (dist + COUT_POUSSER <= action_points)
        {
            if (dist < min_dist)
            {
                min_dist = dist;
                best_dir = res.second;
                best_id = id;
            }
        }
    }
    if (best_id == -1)
        return;

    position push_cell =
        get_position_offset(coop_target.pos, opposite_dir(best_dir));
    move_agent(coop_agents[best_id], push_cell);
    pousser(coop_agents[best_id], best_dir);
}

bool is_coop_agent(int agent_id)
{
    return coop_agents[0] == agent_id || coop_agents[1] == agent_id;
}

bool is_coop_target(alien_info alien)
{
    return has_target && coop_target == alien;
}
