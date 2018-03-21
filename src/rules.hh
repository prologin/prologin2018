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

#ifndef RULES_RULES_HH_
#define RULES_RULES_HH_

#include <memory>

#include <utils/dll.hh>
#include <utils/sandbox.hh>
#include <rules/options.hh>
#include <rules/client-messenger.hh>
#include <rules/server-messenger.hh>
#include <rules/player.hh>
#include <rules/rules.hh>
#include <rules/actions.hh>

#include "api.hh"

class Rules : public rules::TurnBasedRules
{
public:
    explicit Rules(const rules::Options opt);
    virtual ~Rules() {}

    rules::Actions* get_actions() override;
    void apply_action(const rules::IAction_sptr& action) override;
    bool is_finished() override;

protected:
    // FIXME: Override TurnBasedRules methods here

private:
    void register_actions();

    std::unique_ptr<utils::DLL> champion_dll_;
    std::unique_ptr<Api> api_;
    utils::Sandbox sandbox_;
};

#endif // !RULES_RULES_HH_
