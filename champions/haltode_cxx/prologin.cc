#include "common.hh"

void clear_debug_flags()
{
    for (int l = 0; l < TAILLE_ICEBERG; l++)
        for (int c = 0; c < TAILLE_ICEBERG; c++)
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
