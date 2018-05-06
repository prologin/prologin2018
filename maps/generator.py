#!/usr/bin/env python3

import sys
from enum import IntEnum
from random import randint, choice


TAILLE_ICEBERG = 25
NB_AGENTS = 4
NB_TOURS_CAPTURE = 3
NB_TOURS = 100


class case(IntEnum):
    LIBRE = 0
    MUR = 1


class symetry(IntEnum):
    DIAG = 0
    HORI = 1
    VERT = 2


def get_opp(pos, sym):
    if (sym == symetry.DIAG):
        return (TAILLE_ICEBERG - 1 - pos[0], TAILLE_ICEBERG - 1 - pos[1])
    elif (sym == symetry.HORI):
        return (TAILLE_ICEBERG - 1 - pos[0], pos[1])
    else:
        return (pos[0], TAILLE_ICEBERG - 1 - pos[1])

class Generator:
    def __init__(self, murs, aliens):
        self.murs = min(murs, TAILLE_ICEBERG ** 2 // 2)
        self.nb_aliens = aliens
        self.sym = choice(list(symetry))
        self.iceberg = [[case.LIBRE] * TAILLE_ICEBERG for i in range(TAILLE_ICEBERG)]
        self.pinguins1 = []
        self.pinguins2 = []
        self.aliens = []

    def gen_walls(self):
        for i in range(self.murs // 2):
            pos = (randint(0, TAILLE_ICEBERG - 1), randint(0, TAILLE_ICEBERG - 1))
            self.iceberg[pos[0]][pos[1]] = case.MUR
            pos = get_opp(pos, self.sym)
            self.iceberg[pos[0]][pos[1]] = case.MUR


    def gen_pinguins(self):
        positions = []
        for i in range(TAILLE_ICEBERG):
            for j in range(TAILLE_ICEBERG):
                if (self.sym == symetry.DIAG and self.iceberg[i][j] == case.LIBRE \
                        and i < j):
                    positions.append((i, j))
                elif (self.sym == symetry.HORI and self.iceberg[i][j] == case.LIBRE \
                        and i < TAILLE_ICEBERG // 2):
                    positions.append((i, j))
                elif (self.sym == symetry.VERT and self.iceberg[i][j] == case.LIBRE \
                        and j < TAILLE_ICEBERG // 2):
                    positions.append((i, j))
        if len(positions) < NB_AGENTS:
            print("Il y a trop de murs", file=sys.stderr)
            exit(1)
        for i in range(NB_AGENTS):
            pos = choice(positions)
            self.pinguins1.append(pos)
            self.pinguins2.append(get_opp(pos, self.sym))
            positions.remove(pos)


    def gen_aliens(self):
        positions = []
        for i in range(TAILLE_ICEBERG):
            for j in range(TAILLE_ICEBERG):
                if (self.sym == symetry.DIAG and self.iceberg[i][j] == case.LIBRE \
                        and i <= j):
                    positions.append((i, j))
                elif (self.sym == symetry.HORI and self.iceberg[i][j] == case.LIBRE \
                        and i <= TAILLE_ICEBERG // 2):
                    positions.append((i, j))
                elif (self.sym == symetry.VERT and self.iceberg[i][j] == case.LIBRE \
                        and j <= TAILLE_ICEBERG // 2):
                    positions.append((i, j))

        if len(positions) < self.nb_aliens:
            print("Il y a trop de murs et aliens", file=sys.stderr)
            exit(1)

        for i in range(self.nb_aliens // 2):
            pos = choice(positions)
            pos2 = get_opp(pos, self.sym)
            pts = randint(3, 12)
            invasion = randint(0, NB_TOURS - NB_TOURS_CAPTURE)
            duration = randint(NB_TOURS_CAPTURE, 25)
            self.aliens.append((pos, pts, invasion, duration))
            if pos != pos2:
                self.aliens.append((pos2, pts, invasion, duration))
            positions.remove(pos)


    def dump(self):
        for line in self.iceberg:
            for e in line:
                print('.' if e == case.LIBRE else 'X', end='')
            print()

        for pos in self.pinguins1:
            print(pos[0], pos[1])

        for pos in self.pinguins2:
            print(pos[0], pos[1])

        print(len(self.aliens))
        for alien in self.aliens:
            print(alien[0][0], alien[0][1], alien[1], alien[2], alien[3])

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} NB_MURS NB_ALIENS", file=sys.stderr)
        exit(1)

    g = Generator(int(sys.argv[1]), int(sys.argv[2]))
    g.gen_walls()
    g.gen_pinguins()
    g.gen_aliens()
    g.dump()
