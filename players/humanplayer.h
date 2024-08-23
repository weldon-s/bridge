#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "players/player.h"

class HumanPlayer : public Player {
    const Card& select_card(const Trick& t) override;
};

#endif
