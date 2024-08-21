#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include "player.h"

class RandomPlayer : public Player {
    const Card& select_card(const Trick& t) override;
};

#endif
