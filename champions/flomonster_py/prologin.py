# coding: utf-8
# This file has been generated, if you wish to
# modify it in a permanent way, please refer
# to the script file : gen/generator_python.rb

from api import *
from utils import *

# Fonction appelée au début de la partie.
def partie_init():
    pass

# Fonction appelée à chaque tour.
def jouer_tour():
    aliens = filter_aliens()
    capturing = []
    for agent_id in range(NB_AGENTS):
        while aliens:
            alien = find_best(agent_id, aliens)
            if not alien:
                defend(agent_id, capturing)
                break
            aliens.remove(alien)
            if agent_sur_case(alien.pos) == adversaire():
                if not attack(agent_id, alien):
                    continue
            else:
                move(agent_id, alien.pos)
                capturing.append(alien)
            break
        else:
            defend(agent_id, capturing)

# Fonction appelée à la fin de la partie.
def partie_fin():
    pass

