// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2018 Thibault Allançon

#include "common.hh"

void clear_debug_flags()
{
    for (int l = 0; l < TAILLE_BANQUISE; l++)
        for (int c = 0; c < TAILLE_BANQUISE; c++)
            debug_afficher_drapeau({l, c}, AUCUN_DRAPEAU);
}

void partie_init()
{
}

void jouer_tour()
{
    // clear_debug_flags();

    play_coop_mode();

    play_solo_mode();
    std::cout << "end turn: " << tour_actuel() << "\n";
}

void partie_fin()
{
}
