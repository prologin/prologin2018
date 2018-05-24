// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2018 Association Prologin <info@prologin.org>

/// This file has been generated, if you wish to
/// modify it in a permanent way, please refer
/// to the script file : gen/generator_python.rb

#include "interface.hh"

static PyObject* c_module;
static PyObject* py_module;
static PyObject* champ_module;

static void _init_python();

template <typename Lang, typename Cxx>
Lang cxx2lang(Cxx in)
{
  return in.__if_that_triggers_an_error_there_is_a_problem;
}

template <>
PyObject* cxx2lang<PyObject*, int>(int in)
{
  return PyLong_FromLong(in);
}


template <>
PyObject* cxx2lang<PyObject*, double>(double in)
{
  return PyFloat_FromDouble(in);
}


template <>
PyObject* cxx2lang<PyObject*, std::string>(std::string in)
{
  return PyUnicode_FromString(in.c_str());
}


template <>
PyObject* cxx2lang<PyObject*, bool>(bool in)
{
  return PyBool_FromLong(in);
}

template <typename Cxx>
PyObject* cxx2lang_array(const std::vector<Cxx>& in)
{
  size_t size = in.size();
  PyObject* out = PyList_New(size);

  for (unsigned int i = 0; i < size; ++i)
    PyList_SET_ITEM(out, i, (cxx2lang<PyObject*, Cxx>(in[i])));

  return out;
}

template <typename Lang, typename Cxx>
Cxx lang2cxx(Lang in)
{
  return in.__if_that_triggers_an_error_there_is_a_problem;
}

template <>
int lang2cxx<PyObject*, int>(PyObject* in)
{
  long out = PyLong_AsLong(in);
  if (PyErr_Occurred())
    throw 42;
  return out;
}

template <>
double lang2cxx<PyObject*, double>(PyObject* in)
{
  double out = PyFloat_AsDouble(in);
  if (PyErr_Occurred())
    throw 42;
  return out;
}

template <>
bool lang2cxx<PyObject*, bool>(PyObject* in)
{
  return (bool)lang2cxx<PyObject*, int>(in);
}

template <>
std::string lang2cxx<PyObject*, std::string>(PyObject* in)
{
  char * out = PyUnicode_AsUTF8(in);
  if (PyErr_Occurred())
    {
      throw 42;
    }
  return out;
}

template <typename Cxx>
std::vector<Cxx> lang2cxx_array(PyObject* in)
{
  if (!PyList_Check(in))
  {
    PyErr_SetString(PyExc_TypeError, "a list is required");
    throw 42;
  }

  std::vector<Cxx> out;
  unsigned int size = PyList_Size(in);

  for (unsigned int i = 0; i < size; ++i)
    out.push_back(lang2cxx<PyObject*, Cxx>(PyList_GET_ITEM(in, i)));

  return out;
}
/// Types de cases
template <>
PyObject* cxx2lang<PyObject*, case_type>(case_type in)
{
  PyObject* name = PyUnicode_FromString("case_type");
  PyObject* enm = PyObject_GetAttr(py_module, name);
  if (enm == NULL) throw 42;
  PyObject* arglist = Py_BuildValue("(i)", (int) in);
  PyObject* ret = PyObject_CallObject(enm, arglist);
  Py_DECREF(name);
  Py_DECREF(arglist);
  Py_DECREF(enm);
  return ret;
}

template <>
case_type lang2cxx<PyObject*, case_type>(PyObject* in)
{
  return (case_type)lang2cxx<PyObject*, int>(in);
}

/// Points cardinaux
template <>
PyObject* cxx2lang<PyObject*, direction>(direction in)
{
  PyObject* name = PyUnicode_FromString("direction");
  PyObject* enm = PyObject_GetAttr(py_module, name);
  if (enm == NULL) throw 42;
  PyObject* arglist = Py_BuildValue("(i)", (int) in);
  PyObject* ret = PyObject_CallObject(enm, arglist);
  Py_DECREF(name);
  Py_DECREF(arglist);
  Py_DECREF(enm);
  return ret;
}

template <>
direction lang2cxx<PyObject*, direction>(PyObject* in)
{
  return (direction)lang2cxx<PyObject*, int>(in);
}

/// Erreurs possibles
template <>
PyObject* cxx2lang<PyObject*, erreur>(erreur in)
{
  PyObject* name = PyUnicode_FromString("erreur");
  PyObject* enm = PyObject_GetAttr(py_module, name);
  if (enm == NULL) throw 42;
  PyObject* arglist = Py_BuildValue("(i)", (int) in);
  PyObject* ret = PyObject_CallObject(enm, arglist);
  Py_DECREF(name);
  Py_DECREF(arglist);
  Py_DECREF(enm);
  return ret;
}

template <>
erreur lang2cxx<PyObject*, erreur>(PyObject* in)
{
  return (erreur)lang2cxx<PyObject*, int>(in);
}

/// Types d'actions
template <>
PyObject* cxx2lang<PyObject*, action_type>(action_type in)
{
  PyObject* name = PyUnicode_FromString("action_type");
  PyObject* enm = PyObject_GetAttr(py_module, name);
  if (enm == NULL) throw 42;
  PyObject* arglist = Py_BuildValue("(i)", (int) in);
  PyObject* ret = PyObject_CallObject(enm, arglist);
  Py_DECREF(name);
  Py_DECREF(arglist);
  Py_DECREF(enm);
  return ret;
}

template <>
action_type lang2cxx<PyObject*, action_type>(PyObject* in)
{
  return (action_type)lang2cxx<PyObject*, int>(in);
}

/// Types de drapeaux de débug
template <>
PyObject* cxx2lang<PyObject*, debug_drapeau>(debug_drapeau in)
{
  PyObject* name = PyUnicode_FromString("debug_drapeau");
  PyObject* enm = PyObject_GetAttr(py_module, name);
  if (enm == NULL) throw 42;
  PyObject* arglist = Py_BuildValue("(i)", (int) in);
  PyObject* ret = PyObject_CallObject(enm, arglist);
  Py_DECREF(name);
  Py_DECREF(arglist);
  Py_DECREF(enm);
  return ret;
}

template <>
debug_drapeau lang2cxx<PyObject*, debug_drapeau>(PyObject* in)
{
  return (debug_drapeau)lang2cxx<PyObject*, int>(in);
}

/// Position sur l'iceberg, donnée par deux coordonnées.
template <>
PyObject* cxx2lang<PyObject*, position>(position in)
{
  PyObject* tuple = PyTuple_New(2);
  PyTuple_SET_ITEM(tuple, 0, (cxx2lang<PyObject*, int>(in.ligne)));
  PyTuple_SET_ITEM(tuple, 1, (cxx2lang<PyObject*, int>(in.colonne)));
  return tuple;
}

template <>
position lang2cxx<PyObject*, position>(PyObject* in)
{
  position out;
  PyObject* i;
  i = PyTuple_GetItem(in, 0);
  if (i == NULL) throw 42;
  out.ligne = lang2cxx<PyObject*, int>(i);
  i = PyTuple_GetItem(in, 1);
  if (i == NULL) throw 42;
  out.colonne = lang2cxx<PyObject*, int>(i);
  return out;
}

/// Alien à capturer durant la mission.
template <>
PyObject* cxx2lang<PyObject*, alien_info>(alien_info in)
{
  PyObject* tuple = PyTuple_New(5);
  PyTuple_SET_ITEM(tuple, 0, (cxx2lang<PyObject*, position>(in.pos)));
  PyTuple_SET_ITEM(tuple, 1, (cxx2lang<PyObject*, int>(in.points_capture)));
  PyTuple_SET_ITEM(tuple, 2, (cxx2lang<PyObject*, int>(in.tour_invasion)));
  PyTuple_SET_ITEM(tuple, 3, (cxx2lang<PyObject*, int>(in.duree_invasion)));
  PyTuple_SET_ITEM(tuple, 4, (cxx2lang<PyObject*, int>(in.capture_en_cours)));
  PyObject* name = PyUnicode_FromString("alien_info");
  PyObject* cstr = PyObject_GetAttr(py_module, name);
  Py_DECREF(name);
  if (cstr == NULL) throw 42;
  PyObject* ret = PyObject_CallObject(cstr, tuple);
  Py_DECREF(cstr);
  Py_DECREF(tuple);
  if (ret == NULL) throw 42;
  return ret;
}

template <>
alien_info lang2cxx<PyObject*, alien_info>(PyObject* in)
{
  alien_info out;
  PyObject* i;
  i = cxx2lang<PyObject*, int>(0);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.pos = lang2cxx<PyObject*, position>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(1);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.points_capture = lang2cxx<PyObject*, int>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(2);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.tour_invasion = lang2cxx<PyObject*, int>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(3);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.duree_invasion = lang2cxx<PyObject*, int>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(4);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.capture_en_cours = lang2cxx<PyObject*, int>(i);
  Py_DECREF(i);
  return out;
}

/// Action de déplacement représentée dans l'historique.
template <>
PyObject* cxx2lang<PyObject*, action_hist>(action_hist in)
{
  PyObject* tuple = PyTuple_New(3);
  PyTuple_SET_ITEM(tuple, 0, (cxx2lang<PyObject*, action_type>(in.type)));
  PyTuple_SET_ITEM(tuple, 1, (cxx2lang<PyObject*, int>(in.id_agent)));
  PyTuple_SET_ITEM(tuple, 2, (cxx2lang<PyObject*, direction>(in.dir)));
  PyObject* name = PyUnicode_FromString("action_hist");
  PyObject* cstr = PyObject_GetAttr(py_module, name);
  Py_DECREF(name);
  if (cstr == NULL) throw 42;
  PyObject* ret = PyObject_CallObject(cstr, tuple);
  Py_DECREF(cstr);
  Py_DECREF(tuple);
  if (ret == NULL) throw 42;
  return ret;
}

template <>
action_hist lang2cxx<PyObject*, action_hist>(PyObject* in)
{
  action_hist out;
  PyObject* i;
  i = cxx2lang<PyObject*, int>(0);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.type = lang2cxx<PyObject*, action_type>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(1);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.id_agent = lang2cxx<PyObject*, int>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(2);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.dir = lang2cxx<PyObject*, direction>(i);
  Py_DECREF(i);
  return out;
}

/// Déplace l'agent ``id_agent`` d'une case dans la direction choisie.
static PyObject* p_deplacer(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, erreur>(api_deplacer(lang2cxx<PyObject*, int>(a0), lang2cxx<PyObject*, direction>(a1)));
  } catch (...) { return NULL; }
}

/// Propulse l'agent ``id_agent`` dans la direction choisie jusqu'à ce qu'il heurte un obstacle, c'est-à-dire soit un mur soit un autre agent.
static PyObject* p_glisser(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, erreur>(api_glisser(lang2cxx<PyObject*, int>(a0), lang2cxx<PyObject*, direction>(a1)));
  } catch (...) { return NULL; }
}

/// L'agent ``id_agent`` pousse tout autre agent se trouvant sur la case adjacente dans la direction indiquée. Ce dernier est propulsé jusqu'à ce qu'il rencontre un obstacle, c'est-à-dire soit un mur soit un autre agent.
static PyObject* p_pousser(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, erreur>(api_pousser(lang2cxx<PyObject*, int>(a0), lang2cxx<PyObject*, direction>(a1)));
  } catch (...) { return NULL; }
}

/// Affiche le drapeau spécifié sur la case indiquée.
static PyObject* p_debug_afficher_drapeau(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, erreur>(api_debug_afficher_drapeau(lang2cxx<PyObject*, position>(a0), lang2cxx<PyObject*, debug_drapeau>(a1)));
  } catch (...) { return NULL; }
}

/// Renvoie le plus court chemin entre deux positions de l'iceberg sous la forme d'une suite de direction à emprunter. Ce chemin ne contient pas de glissade, uniquement des déplacements simples. Si la position est invalide ou que le chemin n'existe pas, le chemin renvoyé est vide.
static PyObject* p_chemin(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
    try {
return cxx2lang_array(api_chemin(lang2cxx<PyObject*, position>(a0), lang2cxx<PyObject*, position>(a1)));
  } catch (...) { return NULL; }
}

/// Renvoie le type d'une case donnée.
static PyObject* p_type_case(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, case_type>(api_type_case(lang2cxx<PyObject*, position>(a0)));
  } catch (...) { return NULL; }
}

/// Renvoie le numéro du joueur à qui appartient l'agent sur la case indiquée. Renvoie -1 s'il n'y a pas d'agent ou si la position est invalide.
static PyObject* p_agent_sur_case(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_agent_sur_case(lang2cxx<PyObject*, position>(a0)));
  } catch (...) { return NULL; }
}

/// Indique si un alien se trouve sur une case donnée. Renvoie vrai si l'alien est en train d'envahir l'iceberg et qu'il n'a pas encore été capturé. Renvoie faux autremement, ou si la position est invalide.
static PyObject* p_alien_sur_case(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, bool>(api_alien_sur_case(lang2cxx<PyObject*, position>(a0)));
  } catch (...) { return NULL; }
}

/// Indique la position de l'agent sur l'iceberg désigné par le numéro ``id_agent`` appartenant au joueur ``id_joueur``. Si la description de l'agent est incorrecte, la position (-1, -1) est renvoyée.
static PyObject* p_position_agent(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, position>(api_position_agent(lang2cxx<PyObject*, int>(a0), lang2cxx<PyObject*, int>(a1)));
  } catch (...) { return NULL; }
}

/// Renvoie la description d'un alien en fonction d'une position donnée. Si l'alien n'est pas présent sur la carte, ou si la position est invalide, tous les membres de la structure ``alien_info`` renvoyée sont initialisés à -1.
static PyObject* p_info_alien(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, alien_info>(api_info_alien(lang2cxx<PyObject*, position>(a0)));
  } catch (...) { return NULL; }
}

/// Renvoie la liste de tous les aliens présents durant la partie.
static PyObject* p_liste_aliens(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang_array(api_liste_aliens());
  } catch (...) { return NULL; }
}

/// Renvoie la liste des actions effectuées par l’adversaire durant son tour, dans l'ordre chronologique. Les actions de débug n'apparaissent pas dans cette liste.
static PyObject* p_historique(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang_array(api_historique());
  } catch (...) { return NULL; }
}

/// Renvoie le score du joueur ``id_joueur``. Renvoie -1 si le joueur est invalide.
static PyObject* p_score(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_score(lang2cxx<PyObject*, int>(a0)));
  } catch (...) { return NULL; }
}

/// Renvoie votre numéro de joueur.
static PyObject* p_moi(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_moi());
  } catch (...) { return NULL; }
}

/// Renvoie le numéro de joueur de votre adversaire.
static PyObject* p_adversaire(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_adversaire());
  } catch (...) { return NULL; }
}

/// Annule la dernière action. Renvoie faux quand il n'y a pas d'action à annuler ce tour-ci.
static PyObject* p_annuler(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, bool>(api_annuler());
  } catch (...) { return NULL; }
}

/// Retourne le numéro du tour actuel.
static PyObject* p_tour_actuel(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_tour_actuel());
  } catch (...) { return NULL; }
}

/// Renvoie le nombre de points d'action de l'agent ``id_agent`` restants pour le tour. Si le numéro d'agent est invalide, la fonction renvoie -1.
static PyObject* p_points_action_agent(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_points_action_agent(lang2cxx<PyObject*, int>(a0)));
  } catch (...) { return NULL; }
}

/// Affiche le contenu d'une valeur de type case_type
static PyObject* p_afficher_case_type(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_case_type(lang2cxx<PyObject*, case_type>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

/// Affiche le contenu d'une valeur de type direction
static PyObject* p_afficher_direction(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_direction(lang2cxx<PyObject*, direction>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

/// Affiche le contenu d'une valeur de type erreur
static PyObject* p_afficher_erreur(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_erreur(lang2cxx<PyObject*, erreur>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

/// Affiche le contenu d'une valeur de type action_type
static PyObject* p_afficher_action_type(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_action_type(lang2cxx<PyObject*, action_type>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

/// Affiche le contenu d'une valeur de type debug_drapeau
static PyObject* p_afficher_debug_drapeau(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_debug_drapeau(lang2cxx<PyObject*, debug_drapeau>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

/// Affiche le contenu d'une valeur de type position
static PyObject* p_afficher_position(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_position(lang2cxx<PyObject*, position>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

/// Affiche le contenu d'une valeur de type alien_info
static PyObject* p_afficher_alien_info(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_alien_info(lang2cxx<PyObject*, alien_info>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

/// Affiche le contenu d'une valeur de type action_hist
static PyObject* p_afficher_action_hist(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_action_hist(lang2cxx<PyObject*, action_hist>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}


/*
** Api functions to register.
*/
static PyMethodDef api_callback[] = {
  {"deplacer", p_deplacer, METH_VARARGS, "deplacer"},  {"glisser", p_glisser, METH_VARARGS, "glisser"},  {"pousser", p_pousser, METH_VARARGS, "pousser"},  {"debug_afficher_drapeau", p_debug_afficher_drapeau, METH_VARARGS, "debug_afficher_drapeau"},  {"chemin", p_chemin, METH_VARARGS, "chemin"},  {"type_case", p_type_case, METH_VARARGS, "type_case"},  {"agent_sur_case", p_agent_sur_case, METH_VARARGS, "agent_sur_case"},  {"alien_sur_case", p_alien_sur_case, METH_VARARGS, "alien_sur_case"},  {"position_agent", p_position_agent, METH_VARARGS, "position_agent"},  {"info_alien", p_info_alien, METH_VARARGS, "info_alien"},  {"liste_aliens", p_liste_aliens, METH_VARARGS, "liste_aliens"},  {"historique", p_historique, METH_VARARGS, "historique"},  {"score", p_score, METH_VARARGS, "score"},  {"moi", p_moi, METH_VARARGS, "moi"},  {"adversaire", p_adversaire, METH_VARARGS, "adversaire"},  {"annuler", p_annuler, METH_VARARGS, "annuler"},  {"tour_actuel", p_tour_actuel, METH_VARARGS, "tour_actuel"},  {"points_action_agent", p_points_action_agent, METH_VARARGS, "points_action_agent"},  {"afficher_case_type", p_afficher_case_type, METH_VARARGS, "afficher_case_type"},  {"afficher_direction", p_afficher_direction, METH_VARARGS, "afficher_direction"},  {"afficher_erreur", p_afficher_erreur, METH_VARARGS, "afficher_erreur"},  {"afficher_action_type", p_afficher_action_type, METH_VARARGS, "afficher_action_type"},  {"afficher_debug_drapeau", p_afficher_debug_drapeau, METH_VARARGS, "afficher_debug_drapeau"},  {"afficher_position", p_afficher_position, METH_VARARGS, "afficher_position"},  {"afficher_alien_info", p_afficher_alien_info, METH_VARARGS, "afficher_alien_info"},  {"afficher_action_hist", p_afficher_action_hist, METH_VARARGS, "afficher_action_hist"},  {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC PyInit__api()
{
  static struct PyModuleDef apimoduledef = {
      PyModuleDef_HEAD_INIT,
      "_api",
      "API module",
      -1,
      api_callback,
      NULL,
      NULL,
      NULL,
      NULL,
  };
  return PyModule_Create(&apimoduledef);
}


/*
** Load a Python module
*/

static PyObject* _import_module(const char* m)
{
  PyObject* name = PyUnicode_FromString(m);
  PyObject* module = PyImport_Import(name);
  Py_DECREF(name);
  if (module == NULL)
    if (PyErr_Occurred())
    {
      PyErr_Print();
      abort();
    }
  return module;
}

/*
** Inititialize python, register API functions,
** and load .py file
*/
static void _init_python()
{
  static wchar_t empty_string[] = L"";
  static wchar_t *argv[] = { (wchar_t *) &empty_string, NULL };

  const char* champion_path;

  champion_path = getenv("CHAMPION_PATH");
  if (champion_path == NULL)
    champion_path = ".";

  setenv("PYTHONPATH", champion_path, 1);

  static wchar_t program_name[] = L"stechec";
  Py_SetProgramName(program_name);

  PyImport_AppendInittab("_api", PyInit__api);
  Py_Initialize();
  PySys_SetArgvEx(1, argv, 0);

  champ_module = _import_module("prologin");
  py_module = _import_module("api");
}

/*
** Run a python function.
*/
static PyObject* _call_python_function(const char* name)
{
  static bool initialized = false;

  if (!initialized)
  {
    initialized = true;
    _init_python();
  }

  PyObject *arglist, *func;
  PyObject *result = NULL;

  func = PyObject_GetAttrString(champ_module, (char*)name);
  if (func && PyCallable_Check(func))
  {
    arglist = Py_BuildValue("()");
    result = PyEval_CallObject(func, arglist);
    Py_XDECREF(arglist);
    Py_DECREF(func);
  }
  if (result == NULL && PyErr_Occurred())
    PyErr_Print();

  return result;
}

/*
** Functions called from stechec to C.
*/
extern "C" void partie_init()
{
  PyObject* _retval = _call_python_function("partie_init");
  if (!_retval && PyErr_Occurred()) { PyErr_Print(); abort(); }
  try {
  Py_XDECREF(_retval);
  } catch (...) { PyErr_Print(); abort(); }
}

extern "C" void jouer_tour()
{
  PyObject* _retval = _call_python_function("jouer_tour");
  if (!_retval && PyErr_Occurred()) { PyErr_Print(); abort(); }
  try {
  Py_XDECREF(_retval);
  } catch (...) { PyErr_Print(); abort(); }
}

extern "C" void partie_fin()
{
  PyObject* _retval = _call_python_function("partie_fin");
  if (!_retval && PyErr_Occurred()) { PyErr_Print(); abort(); }
  try {
  Py_XDECREF(_retval);
  } catch (...) { PyErr_Print(); abort(); }
}

