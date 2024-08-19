#ifndef HAND_H
#define HAND_H

#include <array>

class Player;

class Hand {
    std::array<Player*, 4> players;

   public:
    Hand(std::array<Player*, 4> players);
};

#endif
