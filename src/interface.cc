// SPDX-License-Identifier: GPL-2.0-or-later
/*
** This file is part of Prologin2018, a rules library for stechec2.
**
** Copyright (c) 2018 Association Prologin <info@prologin.org>
**
** Prologin2018 is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Prologin2018.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "api.hh"

#include <iostream>
#include <sstream>
#include <vector>

// from api.cc
extern Api* api;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& arr)
{
    os << "[";
    typename std::vector<T>::const_iterator it;
    for (it = arr.begin(); it != arr.end(); ++it)
    {
        if (it != arr.begin())
            os << ", ";
        os << *it;
    }
    os << "]";
    return os;
}

// todo avoir un ostringstream a la place de std::string

std::string convert_to_string(int i)
{
    std::ostringstream s;
    s << i;
    std::string result = s.str();
    return result;
}
std::string convert_to_string(double i)
{
    std::ostringstream s;
    s << i;
    std::string result = s.str();
    return result;
}
std::string convert_to_string(std::string i)
{
    return i;
}
std::string convert_to_string(bool i)
{
    return i ? "true" : "false";
}
std::string convert_to_string(std::vector<int> in)
{
    if (in.size())
    {
        std::string s = "[" + convert_to_string(in[0]);
        for (int i = 1, l = in.size(); i < l; i++)
        {
            s = s + ", " + convert_to_string(in[i]);
        }
        return s + "]";
    }
    else
    {
        return "[]";
    }
}
std::string convert_to_string(case_type in)
{
    switch (in)
    {
    case LIBRE:
        return "\"libre\"";
    case MUR:
        return "\"mur\"";
    case ERREUR:
        return "\"erreur\"";
    }
    return "bad value";
}
std::string convert_to_string(std::vector<case_type> in)
{
    if (in.size())
    {
        std::string s = "[" + convert_to_string(in[0]);
        for (int i = 1, l = in.size(); i < l; i++)
        {
            s = s + ", " + convert_to_string(in[i]);
        }
        return s + "]";
    }
    else
    {
        return "[]";
    }
}
std::string convert_to_string(direction in)
{
    switch (in)
    {
    case NORD:
        return "\"nord\"";
    case EST:
        return "\"est\"";
    case SUD:
        return "\"sud\"";
    case OUEST:
        return "\"ouest\"";
    }
    return "bad value";
}
std::string convert_to_string(std::vector<direction> in)
{
    if (in.size())
    {
        std::string s = "[" + convert_to_string(in[0]);
        for (int i = 1, l = in.size(); i < l; i++)
        {
            s = s + ", " + convert_to_string(in[i]);
        }
        return s + "]";
    }
    else
    {
        return "[]";
    }
}
std::string convert_to_string(erreur in)
{
    switch (in)
    {
    case OK:
        return "\"ok\"";
    case PA_INSUFFISANTS:
        return "\"pa_insuffisants\"";
    case POSITION_INVALIDE:
        return "\"position_invalide\"";
    case OBSTACLE_MUR:
        return "\"obstacle_mur\"";
    case OBSTACLE_AGENT:
        return "\"obstacle_agent\"";
    case DEPLACEMENT_HORS_LIMITES:
        return "\"deplacement_hors_limites\"";
    case DIRECTION_INVALIDE:
        return "\"direction_invalide\"";
    case ID_AGENT_INVALIDE:
        return "\"id_agent_invalide\"";
    case RIEN_A_POUSSER:
        return "\"rien_a_pousser\"";
    case DRAPEAU_INVALIDE:
        return "\"drapeau_invalide\"";
    }
    return "bad value";
}
std::string convert_to_string(std::vector<erreur> in)
{
    if (in.size())
    {
        std::string s = "[" + convert_to_string(in[0]);
        for (int i = 1, l = in.size(); i < l; i++)
        {
            s = s + ", " + convert_to_string(in[i]);
        }
        return s + "]";
    }
    else
    {
        return "[]";
    }
}
std::string convert_to_string(action_type in)
{
    switch (in)
    {
    case ACTION_DEPLACER:
        return "\"action_deplacer\"";
    case ACTION_GLISSER:
        return "\"action_glisser\"";
    case ACTION_POUSSER:
        return "\"action_pousser\"";
    }
    return "bad value";
}
std::string convert_to_string(std::vector<action_type> in)
{
    if (in.size())
    {
        std::string s = "[" + convert_to_string(in[0]);
        for (int i = 1, l = in.size(); i < l; i++)
        {
            s = s + ", " + convert_to_string(in[i]);
        }
        return s + "]";
    }
    else
    {
        return "[]";
    }
}
std::string convert_to_string(debug_drapeau in)
{
    switch (in)
    {
    case AUCUN_DRAPEAU:
        return "\"aucun_drapeau\"";
    case DRAPEAU_BLEU:
        return "\"drapeau_bleu\"";
    case DRAPEAU_VERT:
        return "\"drapeau_vert\"";
    case DRAPEAU_ROUGE:
        return "\"drapeau_rouge\"";
    }
    return "bad value";
}
std::string convert_to_string(std::vector<debug_drapeau> in)
{
    if (in.size())
    {
        std::string s = "[" + convert_to_string(in[0]);
        for (int i = 1, l = in.size(); i < l; i++)
        {
            s = s + ", " + convert_to_string(in[i]);
        }
        return s + "]";
    }
    else
    {
        return "[]";
    }
}
std::string convert_to_string(position in)
{
    std::string ligne = convert_to_string(in.ligne);
    std::string colonne = convert_to_string(in.colonne);
    std::string out = "{";
    out += "ligne:" + ligne;
    out += ", ";
    out += "colonne:" + colonne;
    return out + "}";
}

std::string convert_to_string(std::vector<position> in)
{
    if (in.size())
    {
        std::string s = "[" + convert_to_string(in[0]);
        for (int i = 1, l = in.size(); i < l; i++)
        {
            s = s + ", " + convert_to_string(in[i]);
        }
        return s + "]";
    }
    else
    {
        return "[]";
    }
}
std::string convert_to_string(alien_info in)
{
    std::string pos = convert_to_string(in.pos);
    std::string points_capture = convert_to_string(in.points_capture);
    std::string tour_invasion = convert_to_string(in.tour_invasion);
    std::string duree_invasion = convert_to_string(in.duree_invasion);
    std::string capture_en_cours = convert_to_string(in.capture_en_cours);
    std::string out = "{";
    out += "pos:" + pos;
    out += ", ";
    out += "points_capture:" + points_capture;
    out += ", ";
    out += "tour_invasion:" + tour_invasion;
    out += ", ";
    out += "duree_invasion:" + duree_invasion;
    out += ", ";
    out += "capture_en_cours:" + capture_en_cours;
    return out + "}";
}

std::string convert_to_string(std::vector<alien_info> in)
{
    if (in.size())
    {
        std::string s = "[" + convert_to_string(in[0]);
        for (int i = 1, l = in.size(); i < l; i++)
        {
            s = s + ", " + convert_to_string(in[i]);
        }
        return s + "]";
    }
    else
    {
        return "[]";
    }
}
std::string convert_to_string(action_hist in)
{
    std::string type = convert_to_string(in.type);
    std::string id_agent = convert_to_string(in.id_agent);
    std::string dir = convert_to_string(in.dir);
    std::string out = "{";
    out += "type:" + type;
    out += ", ";
    out += "id_agent:" + id_agent;
    out += ", ";
    out += "dir:" + dir;
    return out + "}";
}

std::string convert_to_string(std::vector<action_hist> in)
{
    if (in.size())
    {
        std::string s = "[" + convert_to_string(in[0]);
        for (int i = 1, l = in.size(); i < l; i++)
        {
            s = s + ", " + convert_to_string(in[i]);
        }
        return s + "]";
    }
    else
    {
        return "[]";
    }
}
/// Déplace l'agent ``id_agent`` d'une case dans la direction choisie.
extern "C" erreur api_deplacer(int id_agent, direction dir)
{
    return api->deplacer(id_agent, dir);
}

/// Propulse l'agent ``id_agent`` dans la direction choisie jusqu'à ce qu'il
/// heurte un obstacle, c'est-à-dire soit un mur soit un autre agent.
extern "C" erreur api_glisser(int id_agent, direction dir)
{
    return api->glisser(id_agent, dir);
}

/// L'agent ``id_agent`` pousse tout autre agent se trouvant sur la case
/// adjacente dans la direction indiquée. Ce dernier est propulsé jusqu'à ce
/// qu'il rencontre un obstacle, c'est-à-dire soit un mur soit un autre agent.
extern "C" erreur api_pousser(int id_agent, direction dir)
{
    return api->pousser(id_agent, dir);
}

/// Affiche le drapeau spécifié sur la case indiquée.
extern "C" erreur api_debug_afficher_drapeau(position pos,
                                             debug_drapeau drapeau)
{
    return api->debug_afficher_drapeau(pos, drapeau);
}

/// Renvoie le plus court chemin entre deux positions de l'iceberg sous la forme
/// d'une suite de direction à emprunter. Ce chemin ne contient pas de glissade,
/// uniquement des déplacements simples. Si la position est invalide ou que le
/// chemin n'existe pas, le chemin renvoyé est vide.
extern "C" std::vector<direction> api_chemin(position pos1, position pos2)
{
    return api->chemin(pos1, pos2);
}

/// Renvoie le type d'une case donnée.
extern "C" case_type api_type_case(position pos)
{
    return api->type_case(pos);
}

/// Renvoie le numéro du joueur à qui appartient l'agent sur la case indiquée.
/// Renvoie -1 s'il n'y a pas d'agent ou si la position est invalide.
extern "C" int api_agent_sur_case(position pos)
{
    return api->agent_sur_case(pos);
}

/// Indique si un alien se trouve sur une case donnée. Renvoie vrai si
/// l'alien est en train d'envahir l'iceberg et qu'il n'a pas encore été
/// capturé. Renvoie faux autremement, ou si la position est invalide.
extern "C" bool api_alien_sur_case(position pos)
{
    return api->alien_sur_case(pos);
}

/// Indique la position de l'agent sur l'iceberg désigné par le numéro
/// ``id_agent`` appartenant au joueur ``id_joueur``. Si la description de
/// l'agent est incorrecte, la position (-1, -1) est renvoyée.
extern "C" position api_position_agent(int id_joueur, int id_agent)
{
    return api->position_agent(id_joueur, id_agent);
}

/// Renvoie la description d'un alien en fonction d'une position donnée. Si
/// l'alien n'est pas présent sur la carte, ou si la position est invalide, tous
/// les membres de la structure ``alien_info`` renvoyée sont initialisés à -1.
extern "C" alien_info api_info_alien(position pos)
{
    return api->info_alien(pos);
}

/// Renvoie la liste de tous les aliens présents durant la partie.
extern "C" std::vector<alien_info> api_liste_aliens()
{
    return api->liste_aliens();
}

/// Renvoie la liste des actions effectuées par l’adversaire durant son tour,
/// dans l'ordre chronologique. Les actions de débug n'apparaissent pas dans
/// cette liste.
extern "C" std::vector<action_hist> api_historique()
{
    return api->historique();
}

/// Renvoie le score du joueur ``id_joueur``. Renvoie -1 si le joueur est
/// invalide.
extern "C" int api_score(int id_joueur)
{
    return api->score(id_joueur);
}

/// Renvoie votre numéro de joueur.
extern "C" int api_moi()
{
    return api->moi();
}

/// Renvoie le numéro de joueur de votre adversaire.
extern "C" int api_adversaire()
{
    return api->adversaire();
}

/// Annule la dernière action. Renvoie faux quand il n'y a pas d'action à
/// annuler ce tour-ci.
extern "C" bool api_annuler()
{
    return api->annuler();
}

/// Retourne le numéro du tour actuel.
extern "C" int api_tour_actuel()
{
    return api->tour_actuel();
}

/// Renvoie le nombre de points d'action de l'agent ``id_agent`` restants pour
/// le tour. Si le numéro d'agent est invalide, la fonction renvoie -1.
extern "C" int api_points_action_agent(int id_agent)
{
    return api->points_action_agent(id_agent);
}

/// Affiche le contenu d'une valeur de type case_type
std::ostream& operator<<(std::ostream& os, case_type v)
{
    switch (v)
    {
    case LIBRE:
        os << "LIBRE";
        break;
    case MUR:
        os << "MUR";
        break;
    case ERREUR:
        os << "ERREUR";
        break;
    }
    return os;
}
extern "C" void api_afficher_case_type(case_type v)
{
    std::cerr << v << std::endl;
}

/// Affiche le contenu d'une valeur de type direction
std::ostream& operator<<(std::ostream& os, direction v)
{
    switch (v)
    {
    case NORD:
        os << "NORD";
        break;
    case EST:
        os << "EST";
        break;
    case SUD:
        os << "SUD";
        break;
    case OUEST:
        os << "OUEST";
        break;
    }
    return os;
}
extern "C" void api_afficher_direction(direction v)
{
    std::cerr << v << std::endl;
}

/// Affiche le contenu d'une valeur de type erreur
std::ostream& operator<<(std::ostream& os, erreur v)
{
    switch (v)
    {
    case OK:
        os << "OK";
        break;
    case PA_INSUFFISANTS:
        os << "PA_INSUFFISANTS";
        break;
    case POSITION_INVALIDE:
        os << "POSITION_INVALIDE";
        break;
    case OBSTACLE_MUR:
        os << "OBSTACLE_MUR";
        break;
    case OBSTACLE_AGENT:
        os << "OBSTACLE_AGENT";
        break;
    case DEPLACEMENT_HORS_LIMITES:
        os << "DEPLACEMENT_HORS_LIMITES";
        break;
    case DIRECTION_INVALIDE:
        os << "DIRECTION_INVALIDE";
        break;
    case ID_AGENT_INVALIDE:
        os << "ID_AGENT_INVALIDE";
        break;
    case RIEN_A_POUSSER:
        os << "RIEN_A_POUSSER";
        break;
    case DRAPEAU_INVALIDE:
        os << "DRAPEAU_INVALIDE";
        break;
    }
    return os;
}
extern "C" void api_afficher_erreur(erreur v)
{
    std::cerr << v << std::endl;
}

/// Affiche le contenu d'une valeur de type action_type
std::ostream& operator<<(std::ostream& os, action_type v)
{
    switch (v)
    {
    case ACTION_DEPLACER:
        os << "ACTION_DEPLACER";
        break;
    case ACTION_GLISSER:
        os << "ACTION_GLISSER";
        break;
    case ACTION_POUSSER:
        os << "ACTION_POUSSER";
        break;
    }
    return os;
}
extern "C" void api_afficher_action_type(action_type v)
{
    std::cerr << v << std::endl;
}

/// Affiche le contenu d'une valeur de type debug_drapeau
std::ostream& operator<<(std::ostream& os, debug_drapeau v)
{
    switch (v)
    {
    case AUCUN_DRAPEAU:
        os << "AUCUN_DRAPEAU";
        break;
    case DRAPEAU_BLEU:
        os << "DRAPEAU_BLEU";
        break;
    case DRAPEAU_VERT:
        os << "DRAPEAU_VERT";
        break;
    case DRAPEAU_ROUGE:
        os << "DRAPEAU_ROUGE";
        break;
    }
    return os;
}
extern "C" void api_afficher_debug_drapeau(debug_drapeau v)
{
    std::cerr << v << std::endl;
}

/// Affiche le contenu d'une valeur de type position
std::ostream& operator<<(std::ostream& os, position v)
{
    os << "{ ";
    os << "ligne"
       << "=" << v.ligne;
    os << ", ";
    os << "colonne"
       << "=" << v.colonne;
    os << " }";
    return os;
}
extern "C" void api_afficher_position(position v)
{
    std::cerr << v << std::endl;
}

/// Affiche le contenu d'une valeur de type alien_info
std::ostream& operator<<(std::ostream& os, alien_info v)
{
    os << "{ ";
    os << "pos"
       << "=" << v.pos;
    os << ", ";
    os << "points_capture"
       << "=" << v.points_capture;
    os << ", ";
    os << "tour_invasion"
       << "=" << v.tour_invasion;
    os << ", ";
    os << "duree_invasion"
       << "=" << v.duree_invasion;
    os << ", ";
    os << "capture_en_cours"
       << "=" << v.capture_en_cours;
    os << " }";
    return os;
}
extern "C" void api_afficher_alien_info(alien_info v)
{
    std::cerr << v << std::endl;
}

/// Affiche le contenu d'une valeur de type action_hist
std::ostream& operator<<(std::ostream& os, action_hist v)
{
    os << "{ ";
    os << "type"
       << "=" << v.type;
    os << ", ";
    os << "id_agent"
       << "=" << v.id_agent;
    os << ", ";
    os << "dir"
       << "=" << v.dir;
    os << " }";
    return os;
}
extern "C" void api_afficher_action_hist(action_hist v)
{
    std::cerr << v << std::endl;
}
