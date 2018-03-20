/*
** Stechec project is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** The complete GNU General Public Licence Notice can be found as the
** `NOTICE' file in the root directory.
**
** Copyright (C) 2018 Prologin
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

std::string convert_to_string(int i){
  std::ostringstream s;
  s << i;
  std::string result = s.str();
  return result;
}
std::string convert_to_string(double i){
  std::ostringstream s;
  s << i;
  std::string result = s.str();
  return result;
}
std::string convert_to_string(std::string i){
  return i;
}
std::string convert_to_string(bool i){
  return i?"true":"false";
}
std::string convert_to_string(std::vector<int> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(case_type in){
  switch (in)
  {
    case LIBRE: return "\"libre\"";
    case MUR: return "\"mur\"";
    case ERREUR: return "\"erreur\"";
  }
  return "bad value";
}
std::string convert_to_string(std::vector<case_type> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(direction in){
  switch (in)
  {
    case NORD: return "\"nord\"";
    case EST: return "\"est\"";
    case SUD: return "\"sud\"";
    case OUEST: return "\"ouest\"";
  }
  return "bad value";
}
std::string convert_to_string(std::vector<direction> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(erreur in){
  switch (in)
  {
    case OK: return "\"ok\"";
    case PA_INSUFFISANTS: return "\"pa_insuffisants\"";
    case POSITION_INVALIDE: return "\"position_invalide\"";
    case DIRECTION_INVALIDE: return "\"direction_invalide\"";
    case ID_AGENT_INVALIDE: return "\"id_agent_invalide\"";
    case ID_JOUEUR_INVALIDE: return "\"id_joueur_invalide\"";
  }
  return "bad value";
}
std::string convert_to_string(std::vector<erreur> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(action_type in){
  switch (in)
  {
    case ACTION_DEPLACER: return "\"action_deplacer\"";
    case ACTION_GLISSER: return "\"action_glisser\"";
  }
  return "bad value";
}
std::string convert_to_string(std::vector<action_type> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(position in){
  std::string x = convert_to_string(in.x);
  std::string y = convert_to_string(in.y);
  std::string out = "{";
  out += "x:" + x;
  out += ", ";
  out += "y:" + y;
  return out + "}";
}

std::string convert_to_string(std::vector<position> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(alien_info in){
  std::string pos = convert_to_string(in.pos);
  std::string puissance = convert_to_string(in.puissance);
  std::string tour_invasion = convert_to_string(in.tour_invasion);
  std::string duree_invasion = convert_to_string(in.duree_invasion);
  std::string out = "{";
  out += "pos:" + pos;
  out += ", ";
  out += "puissance:" + puissance;
  out += ", ";
  out += "tour_invasion:" + tour_invasion;
  out += ", ";
  out += "duree_invasion:" + duree_invasion;
  return out + "}";
}

std::string convert_to_string(std::vector<alien_info> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(action_hist in){
  std::string type = convert_to_string(in.type);
  std::string id_agent = convert_to_string(in.id_agent);
  std::string dest = convert_to_string(in.dest);
  std::string dir = convert_to_string(in.dir);
  std::string out = "{";
  out += "type:" + type;
  out += ", ";
  out += "id_agent:" + id_agent;
  out += ", ";
  out += "dest:" + dest;
  out += ", ";
  out += "dir:" + dir;
  return out + "}";
}

std::string convert_to_string(std::vector<action_hist> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
/// Déplace l'agent ``id_agent`` sur la case donnée en paramètre.
extern "C" erreur api_deplacer(int id_agent, position dest)
{
  return api->deplacer(id_agent, dest);
}

/// Propulse l'agent ``id_agent`` dans la direction choisie jusqu'à ce qu'il heurte un obstacle, c'est-à-dire soit un mur soit un autre agent. Si au début de la glissade, il y a un autre agent sur une case adjacente dans cette direction, alors cet agent est poussé dans la direction jusqu'à ce qu'il rencontre un obstacle.
extern "C" erreur api_glisser(int id_agent, direction dir)
{
  return api->glisser(id_agent, dir);
}

/// Renvoie le type d'une case donnée.
extern "C" case_type api_type_case(position pos)
{
  return api->type_case(pos);
}

/// Indique si un agent se trouve sur une case donnée. Renvoie faux si la position est invalide.
extern "C" bool api_agent_sur_case(position pos)
{
  return api->agent_sur_case(pos);
}

/// Indique la position de l'agent sur l'iceberg désigné par le numéro ``id_agent``.
extern "C" position api_position_agent(int id_agent)
{
  return api->position_agent(id_agent);
}

/// Renvoie la liste de tous les agents du joueur désigné par le numéro ``id_joueur``.
extern "C" std::vector<int> api_liste_agents(int id_joueur)
{
  return api->liste_agents(id_joueur);
}

/// Renvoie la liste de tous les aliens présents sur l'iceberg.
extern "C" std::vector<alien_info> api_liste_aliens()
{
  return api->liste_aliens();
}

/// Renvoie la liste des tours où se produisent une rafale.
extern "C" std::vector<int> api_liste_rafales()
{
  return api->liste_rafales();
}

/// Renvoie la direction des rafales.
extern "C" direction api_direction_rafale()
{
  return api->direction_rafale();
}

/// Renvoie la liste des actions effectuées par l’adversaire durant son tour, dans l'ordre chronologique.
extern "C" std::vector<action_hist> api_historique()
{
  return api->historique();
}

/// Renvoie le score du joueur ``id_joueur``. Renvoie -1 si le joueur est invalide.
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

/// Annule la dernière action. Renvoie ``false`` quand il n'y a pas d'action à annuler ce tour-ci.
extern "C" bool api_annuler()
{
  return api->annuler();
}

/// Retourne le numéro du tour actuel.
extern "C" int api_tour_actuel()
{
  return api->tour_actuel();
}

/// Renvoie votre nombre de points d'action restants pour le tour.
extern "C" int api_points_action()
{
  return api->points_action();
}

/// Affiche le contenu d'une valeur de type case_type
std::ostream& operator<<(std::ostream& os, case_type v)
{
  switch (v) {
  case LIBRE: os << "LIBRE"; break;
  case MUR: os << "MUR"; break;
  case ERREUR: os << "ERREUR"; break;
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
  switch (v) {
  case NORD: os << "NORD"; break;
  case EST: os << "EST"; break;
  case SUD: os << "SUD"; break;
  case OUEST: os << "OUEST"; break;
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
  switch (v) {
  case OK: os << "OK"; break;
  case PA_INSUFFISANTS: os << "PA_INSUFFISANTS"; break;
  case POSITION_INVALIDE: os << "POSITION_INVALIDE"; break;
  case DIRECTION_INVALIDE: os << "DIRECTION_INVALIDE"; break;
  case ID_AGENT_INVALIDE: os << "ID_AGENT_INVALIDE"; break;
  case ID_JOUEUR_INVALIDE: os << "ID_JOUEUR_INVALIDE"; break;
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
  switch (v) {
  case ACTION_DEPLACER: os << "ACTION_DEPLACER"; break;
  case ACTION_GLISSER: os << "ACTION_GLISSER"; break;
  }
  return os;
}
extern "C" void api_afficher_action_type(action_type v)
{
  std::cerr << v << std::endl;
}

/// Affiche le contenu d'une valeur de type position
std::ostream& operator<<(std::ostream& os, position v)
{
  os << "{ ";
  os << "x" << "=" << v.x;
  os << ", ";
  os << "y" << "=" << v.y;
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
  os << "pos" << "=" << v.pos;
  os << ", ";
  os << "puissance" << "=" << v.puissance;
  os << ", ";
  os << "tour_invasion" << "=" << v.tour_invasion;
  os << ", ";
  os << "duree_invasion" << "=" << v.duree_invasion;
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
  os << "type" << "=" << v.type;
  os << ", ";
  os << "id_agent" << "=" << v.id_agent;
  os << ", ";
  os << "dest" << "=" << v.dest;
  os << ", ";
  os << "dir" << "=" << v.dir;
  os << " }";
  return os;
}
extern "C" void api_afficher_action_hist(action_hist v)
{
  std::cerr << v << std::endl;
}

