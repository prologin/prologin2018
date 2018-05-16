#include "common.hh"

int cost_single_action(action_hist action)
{
    if (action.type == ACTION_DEPLACER)
        return COUT_DEPLACEMENT;
    else if (action.type == ACTION_GLISSER)
        return COUT_GLISSADE;
    else if (action.type == ACTION_POUSSER)
        return COUT_POUSSER;
    return 0;
}

bool can_push_agent_from(position pos)
{
    for (int dir = 0; dir < 4; dir++)
    {
        direction d1 = (direction)dir;
        direction d2 = (direction)((dir + 1) % 4);
        position off1 = get_position_offset(pos, d1);
        position off2 = get_position_offset(pos, d2);
        if (type_case(off1) == MUR && type_case(off2) == MUR)
            return false;
    }
    return true;
}

int cnt_open_dir(position pos)
{
    int total = 0;
    for (int idir = 0; idir < 4; idir++)
    {
        direction dir = (direction)idir;
        position p1 = get_position_offset(pos, dir);
        position p2 = get_position_offset(p1, dir);
        if (inside_map(p1) && inside_map(p2) && type_case(p1) == LIBRE &&
            type_case(p2) == LIBRE)
            ++total;
    }
    return total;
}

void sort_aliens_by_time(std::vector<alien_info>& aliens)
{
    std::sort(aliens.begin(), aliens.end(),
              [](const auto& lhs, const auto& rhs) {
                  return lhs.tour_invasion < rhs.tour_invasion;
              });
}

bool alien_shoud_be_on_round(alien_info alien)
{
    int round = tour_actuel();
    return alien.tour_invasion <= round &&
           round < alien.tour_invasion + alien.duree_invasion;
}

bool inside_map(position pos)
{
    return pos.ligne >= 0 && pos.ligne < TAILLE_BANQUISE && pos.colonne >= 0 &&
           pos.colonne < TAILLE_BANQUISE;
}

bool is_obstacle(position pos)
{
    return type_case(pos) == MUR || agent_sur_case(pos) != -1;
}

int manhattan_dist(position src, position dest)
{
    return abs(src.ligne - dest.ligne) + abs(src.colonne - dest.colonne);
}

position operator+(position a, position b)
{
    return position{a.ligne + b.ligne, a.colonne + b.colonne};
}

static const position offset[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

position get_position_offset(const position pos, const direction dir)
{
    return pos + offset[dir];
}

direction opposite_dir(direction dir)
{
    if (dir == NORD)
        return SUD;
    else if (dir == EST)
        return OUEST;
    else if (dir == SUD)
        return NORD;
    else
        return EST;
}

std::pair<direction, direction> orth_dir(direction dir)
{
    if (dir == NORD || dir == SUD)
        return {EST, OUEST};
    else
        return {NORD, SUD};
}
