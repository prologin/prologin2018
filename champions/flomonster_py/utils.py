from api import *
from collections import deque
from operator import attrgetter

def filter_aliens():
    aliens = liste_aliens()
    i = 0
    while i < len(aliens):
        if not alien_sur_case(aliens[i].pos) and (aliens[i].tour_invasion < tour_actuel() \
                or aliens[i].tour_invasion > tour_actuel() + 5):
            aliens.pop(i)
        else:
            i += 1
    return aliens

def time_travel(path):
    pa = NB_POINTS_ACTION
    time = 0
    for direc in path:
        if direc > 3:
            pa -= COUT_GLISSADE
        else:
            pa -= COUT_DEPLACEMENT
        if pa < 0:
            pa = NB_POINTS_ACTION
            time += 1
    return time

def find_best(agent_id, aliens):
    if not aliens:
        return None
    best_alien = None
    best_score = float('-inf')
    for alien in aliens:
        # Check que j'ai le temps d'annuler la capture
        if (agent_sur_case(alien.pos) == adversaire()):
            if (alien.points_capture * 2 > best_score):
                best_alien = alien
                best_score = alien.points_capture * 2

        path = mon_chemin(position_agent(moi(), agent_id), alien.pos)
        if path == None:
            continue

        # Check que j'ai le temps de capturer l'alien
        elif (alien.tour_invasion + alien.duree_invasion >= tour_actuel() + \
                NB_TOURS_CAPTURE + time_travel(path)):

            if alien.points_capture - time_travel(path) - alien.tour_invasion > best_score:
                best_alien = alien
                best_score = alien.points_capture - time_travel(path) - alien.tour_invasion

    return best_alien

def is_empty(pos):
    return type_case(pos) == case_type.LIBRE and agent_sur_case(pos) == -1

def list_pos(pos):
    if is_empty((pos[0] - 1, pos[1])):
        yield ((pos[0] - 1, pos[1]), direction.NORD)
    if is_empty((pos[0] + 1, pos[1])):
        yield ((pos[0] + 1, pos[1]), direction.SUD)
    if is_empty((pos[0], pos[1] + 1)):
        yield ((pos[0], pos[1] + 1), direction.EST)
    if is_empty((pos[0], pos[1] - 1)):
        yield ((pos[0], pos[1] - 1), direction.OUEST)

    i = 0
    while is_empty((pos[0] - i - 1, pos[1])):
        i += 1
    if i >= COUT_GLISSADE - COUT_DEPLACEMENT:
        yield ((pos[0] - i, pos[1]), direction.NORD + 4)

    i = 0
    while is_empty((pos[0] + i + 1, pos[1])):
        i += 1
    if i >= COUT_GLISSADE - COUT_DEPLACEMENT:
        yield ((pos[0] + i, pos[1]), direction.SUD + 4)

    i = 0
    while is_empty((pos[0], pos[1] + i + 1)):
        i += 1
    if i >= COUT_GLISSADE - COUT_DEPLACEMENT:
        yield ((pos[0], pos[1] + i), direction.EST + 4)

    i = 0
    while is_empty((pos[0], pos[1] - i - 1)):
        i += 1
    if i >= COUT_GLISSADE - COUT_DEPLACEMENT:
        yield ((pos[0], pos[1] - i), direction.OUEST + 4)

def mon_chemin(origin, dest):
    queue = deque([(origin, [])])
    marks = [[0] * TAILLE_ICEBERG for i in range(TAILLE_ICEBERG)]
    marks[origin[0]][origin[1]] = 1
    while (queue):
        (pos, hist) = queue.pop()
        if (pos == dest):
            return hist
        for (new_pos, direction) in list_pos(pos):
            if not marks[new_pos[0]][new_pos[1]]:
                cpy = hist[:]
                cpy.append(direction)
                queue.appendleft((new_pos, cpy))
                marks[new_pos[0]][new_pos[1]] = 1

def move(agent_id, pos):
    chemin = mon_chemin(position_agent(moi(), agent_id), pos)
    if not chemin:
        return chemin == []
    while (chemin and points_action_agent(agent_id) >= COUT_DEPLACEMENT):
        direction = chemin.pop(0)
        if direction > 3:
            glisser(agent_id, direction - 4)
        else:
            deplacer(agent_id, direction)
    return not chemin


def attack(agent_id, alien):
    if is_empty((alien.pos[0]-1, alien.pos[1])) and \
            is_empty((alien.pos[0]+1, alien.pos[1])):
        p1 = mon_chemin(position_agent(moi(), agent_id), (alien.pos[0]-1, alien.pos[1]))
        p2 = mon_chemin(position_agent(moi(), agent_id), (alien.pos[0]+1, alien.pos[1]))
        if p1 != None and p2 != None and time_travel(p1) < time_travel(p2):
            if (move(agent_id, (alien.pos[0]-1, alien.pos[1])) and \
                    points_action_agent(agent_id) >= COUT_POUSSER):
                pousser(agent_id, direction.SUD)
        elif (move(agent_id, (alien.pos[0]+1, alien.pos[1])) and \
                points_action_agent(agent_id) >= COUT_POUSSER):
            pousser(agent_id, direction.NORD)
        return True


    if is_empty((alien.pos[0], alien.pos[1] - 1)) and \
            is_empty((alien.pos[0], alien.pos[1] + 1)):
        p1 = mon_chemin(position_agent(moi(), agent_id), (alien.pos[0], alien.pos[1] - 1))
        p2 = mon_chemin(position_agent(moi(), agent_id), (alien.pos[0], alien.pos[1] + 1))
        if p1 != None and p2 != None and time_travel(p1) < time_travel(p2):
            if (move(agent_id, (alien.pos[0], alien.pos[1] - 1)) and \
                    points_action_agent(agent_id) >= COUT_POUSSER):
                pousser(agent_id, direction.EST)
        elif (move(agent_id, (alien.pos[0], alien.pos[1] + 1)) and \
                points_action_agent(agent_id) >= COUT_POUSSER):
            pousser(agent_id, direction.OUEST)
        return True
    return False


def defend(agent_id, capturing):
    capturing = capturing[:]
    while capturing:
        alien = min(capturing, key=attrgetter('tour_invasion'))
        capturing.remove(alien)
        if is_empty((alien.pos[0]-1, alien.pos[1])) and \
                is_empty((alien.pos[0]+1, alien.pos[1])):
            p1 = mon_chemin(position_agent(moi(), agent_id), (alien.pos[0]-1, alien.pos[1]))
            p2 = mon_chemin(position_agent(moi(), agent_id), (alien.pos[0]+1, alien.pos[1]))
            if p1 != None and p2 != None:
                if time_travel(p1) < time_travel(p2):
                    move(agent_id, (alien.pos[0] - 1, alien.pos[1]))
                else:
                    move(agent_id, (alien.pos[0] + 1, alien.pos[1]))
                break

        if is_empty((alien.pos[0], alien.pos[1]-1)) and \
                is_empty((alien.pos[0], alien.pos[1]+1)):
            p1 = mon_chemin(position_agent(moi(), agent_id), (alien.pos[0], alien.pos[1]-1))
            p2 = mon_chemin(position_agent(moi(), agent_id), (alien.pos[0], alien.pos[1]+1))
            if p1 != None and p2 != None:
                if time_travel(p1) < time_travel(p2):
                    move(agent_id, (alien.pos[0], alien.pos[1] - 1))
                else:
                    move(agent_id, (alien.pos[0], alien.pos[1] + 1))
                break
