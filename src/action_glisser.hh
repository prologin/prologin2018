#ifndef ACTION_GLISSER_HH
#define ACTION_GLISSER_HH

#include <rules/action.hh>

#include "actions.hh"
#include "game_state.hh"
#include "constant.hh"

class ActionGlisser : public rules::Action<GameState>
{
public:
    ActionGlisser(int id_agent, direction dir, int player_id) : id_agent_(id_agent), dir_(dir), player_id_(player_id) {}
    ActionGlisser() {} // for register_action()

    int check(const GameState* st) const override;
    void apply_on(GameState* st) const override;

    void handle_buffer(utils::Buffer& buf) override
    {
        buf.handle(id_agent_);
        buf.handle(dir_);
        buf.handle(player_id_);
    }

    uint32_t player_id() const override { return player_id_; };
    uint32_t id() const override { return ID_ACTION_GLISSER; }

private:
    int id_agent_;
    direction dir_;
    int player_id_;
};

#endif // !ACTION_GLISSER_HH
