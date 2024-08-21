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

    const std::vector<std::unique_ptr<Card>> cards_;
    std::array<Player*, 4> players_;
    std::vector<Trick> tricks_;

   public:
    Hand(std::array<Player*, 4> players);
    void play();
    const std::vector<Trick>& tricks();
};

#endif
