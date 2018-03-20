#ifndef ACTION_DEPLACER_HH
#define ACTION_DEPLACER_HH

#include <rules/action.hh>

#include "actions.hh"
#include "game_state.hh"
#include "constant.hh"

class ActionDeplacer : public rules::Action<GameState>
{
public:
    ActionDeplacer(int id_agent, position dest, int player_id) : id_agent_(id_agent), dest_(dest), player_id_(player_id) {}
    ActionDeplacer() {} // for register_action()

    int check(const GameState* st) const override;
    void apply_on(GameState* st) const override;

    void handle_buffer(utils::Buffer& buf) override
    {
        buf.handle(id_agent_);
        buf.handle(dest_);
        buf.handle(player_id_);
    }

    uint32_t player_id() const override { return player_id_; };
    uint32_t id() const override { return ID_ACTION_DEPLACER; }

private:
    int id_agent_;
    position dest_;
    int player_id_;
};

#endif // !ACTION_DEPLACER_HH
