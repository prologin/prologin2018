#include "direction.hh"

#include "position.hh"

position dir::offset(position pos, const direction &direction)
{
    if(direction == NORD)
        --pos.ligne;
    else if(direction == SUD)
        ++pos.ligne;
    else if(direction == OUEST)
        --pos.colonne;
    else
        ++pos.colonne;
    return pos;
}

position dir::slide(position pos, const direction &direction)
{
    position next;
    while(pos::is_free(next = offset(pos, direction)))
        pos = next;
    return pos;
}

int dir::slide_distance(position pos, const direction &direction)
{
    position next;
    int distance = 0;
    while(pos::is_free(next = offset(pos, direction)))
    {
        pos = next;
        ++distance;
    }
    return distance;
}

direction dir::get(const position &a, const position &b)
{
    if(a.ligne == b.ligne)
    {
        if(a.colonne > b.colonne)
            return OUEST;
        return EST;
    }
    if(a.ligne > b.ligne)
        return NORD;
    return SUD;
}
