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

#ifndef ACTIONS_HH
#define ACTIONS_HH

enum action_id
{
    ID_ACTION_DEPLACER,
    ID_ACTION_GLISSER,
    ID_ACTION_POUSSER,
    ID_ACTION_DEBUG_AFFICHER_DRAPEAU
};

#include "action_debug_afficher_drapeau.hh"
#include "action_deplacer.hh"
#include "action_glisser.hh"
#include "action_pousser.hh"

#endif // !ACTIONS_HH
