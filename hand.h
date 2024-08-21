#ifndef HAND_H
#define HAND_H

#include <array>
#include <memory>
#include <vector>

#include "card.h"
#include "trick.h"

class Player;

class Hand {
    static const int num_tricks{13};

    const std::vector<std::unique_ptr<Card>> cards;
    std::array<Player*, 4> players;
    std::vector<Trick> _tricks;

   public:
    Hand(std::array<Player*, 4> players);
    void play();
    const std::vector<Trick>& tricks();
};

#endif
