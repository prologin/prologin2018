// SPDX-License-Identifier: GPL-2.0-or-later
/*
** This file is part of Prologin2018, a rules library for stechec2.
**
** Copyright (c) 2018 Association Prologin <info@prologin.org>
** Copyright (c) 2018 Thibault Allançon
**
** Prologin2018 is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Prologin2018.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef API_HH_
#define API_HH_

#include <rules/actions.hh>
#include <rules/api.hh>
#include <rules/game-state.hh>
#include <rules/player.hh>
#include <vector>

#include "actions.hh"
#include "constant.hh"
#include "game_state.hh"

/*!
** The methods of this class are exported through 'interface.cc'
** to be called by the clients
*/
class Api final : public rules::Api<GameState, erreur>
{
public:
    Api(std::unique_ptr<GameState> game_state, rules::Player_sptr player);

    /// Déplace l'agent ``id_agent`` d'une case dans la direction choisie.
    ApiActionFunc<ActionDeplacer> deplacer{this};

    /// Propulse l'agent ``id_agent`` dans la direction choisie jusqu'à ce qu'il
    /// heurte un obstacle, c'est-à-dire soit un mur soit un autre agent.
    ApiActionFunc<ActionGlisser> glisser{this};

    /// L'agent ``id_agent`` pousse tout autre agent se trouvant sur la case
    /// adjacente dans la direction indiquée. Ce dernier est propulsé jusqu'à ce
    /// qu'il rencontre un obstacle, c'est-à-dire soit un mur soit un autre
    /// agent.
    ApiActionFunc<ActionPousser> pousser{this};

    /// Affiche le drapeau spécifié sur la case indiquée.
    ApiActionFunc<ActionDebugAfficherDrapeau> debug_afficher_drapeau{this};

    /// Renvoie le nombre de points d'action de l'agent ``id_agent`` restants
    /// pour le tour. Si le numéro d'agent est invalide, la fonction renvoie -1.
    int points_action_agent(int id_agent);

    /// Renvoie le plus court chemin entre deux positions de la banquise sous la
    /// forme d'une suite de direction à emprunter. Ce chemin ne contient pas de
    /// glissade, uniquement des déplacements simples. Si la position est
    /// invalide ou que le chemin n'existe pas, le chemin renvoyé est vide.
    std::vector<direction> chemin(position pos1, position pos2);

    /// Renvoie le type d'une case donnée.
    case_type type_case(position pos);

    /// Renvoie le numéro du joueur à qui appartient l'agent sur la case
    /// indiquée. Renvoie -1 s'il n'y a pas d'agent ou si la position est
    /// invalide.
    int agent_sur_case(position pos);

    /// Indique si un alien se trouve sur une case donnée. Renvoie vrai si
    /// l'alien est en train d'envahir la banquise et qu'il n'a pas encore été
    /// capturé. Renvoie faux autremement, ou si la position est invalide.
    bool alien_sur_case(position pos);

    /// Indique la position de l'agent sur la banquise désigné par le numéro
    /// ``id_agent`` appartenant au joueur ``id_joueur``. Si la description de
    /// l'agent est incorrecte, la position (-1, -1) est renvoyée.
    position position_agent(int id_joueur, int id_agent);

    /// Renvoie la description d'un alien en fonction d'une position donnée. Si
    /// l'alien n'est pas présent sur la carte, ou si la position est invalide,
    /// tous les membres de la structure ``alien_info`` renvoyée sont
    /// initialisés à -1.
    alien_info info_alien(position pos);

    /// Renvoie la liste de tous les aliens présents durant la partie.
    std::vector<alien_info> liste_aliens();

    /// Renvoie la liste des actions effectuées par l’adversaire durant son
    /// tour, dans l'ordre chronologique. Les actions de débug n'apparaissent
    /// pas dans cette liste.
    std::vector<action_hist> historique();

    /// Renvoie le score du joueur ``id_joueur``. Renvoie -1 si le joueur est
    /// invalide.
    int score(int id_joueur);

    /// Renvoie votre numéro de joueur.
    int moi();

    /// Renvoie le numéro de joueur de votre adversaire.
    int adversaire();

    /// Annule la dernière action. Renvoie faux quand il n'y a pas d'action
    /// à annuler ce tour-ci.
    bool annuler();

    /// Retourne le numéro du tour actuel.
    int tour_actuel();
};

#endif /* !API_HH_ */
