#!/usr/bin/env python3
import sys


MAP_SIZE = 25
NB_AGENTS = 4
NB_TURNS = 100

def inside_map(r, c):
    return (0 <= r < MAP_SIZE and
            0 <= c < MAP_SIZE)

m = []

for _ in range(MAP_SIZE):
    line = input()
    for c in line:
        if c != '.' and c != 'X':
            sys.exit("Type de la case invalide : " + c)
    m.append(line)

s = set()
for _ in range(2):
    for agent in range(NB_AGENTS):
        r, c = map(int, input().split(' '))
        pos = (r, c)
        if not inside_map(r, c):
            sys.exit("Position agent hors de la carte : ({}, {})".format(r, c))
        if pos in s:
            sys.exit("Position agent déjà prise : ({}, {})".format(r, c))
        if m[r][c] == 'X':
            sys.exit("Position agent est un mur : ({}, {})".format(r, c))
        s.add(pos)

s = set()
nl = input()
try:
    nb_aliens = int(nl)
except ValueError:
    sys.exit("Après avoir lu {} positions d'agents, le nombre d'aliens est "
             "attendu mais la ligne suivante a été trouvée : {}"
             .format(NB_AGENTS, nl))
for id_alien in range(nb_aliens):
    r, c, nb_point, round_spawn, round_span = map(int, input().split(' '))
    pos = (r, c)
    if not inside_map(r, c):
        sys.exit("Position alien hors de la carte : ({}, {})".format(r, c))
    if pos in s:
        sys.exit("Position alien déjà prise : ({}, {})".format(r, c))
    if m[r][c] == 'X':
        sys.exit("Position alien est un mur : ({}, {})".format(r, c))
    if round_spawn < 0 or round_spawn >= NB_TURNS:
        sys.exit("Tour apparition alien invalide : ", id_alien)
    s.add(pos)
