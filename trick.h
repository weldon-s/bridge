#ifndef TRICK_H
#define TRICK_H

#include <vector>

class Player;
class Card;
class Suit;

struct Play {
    const Player& player;
    const Card& card;
};

class Trick {
    std::vector<Play> _plays;
    const Suit* _leading{nullptr};
    // TODO field for trump

   public:
    void add_play(Player& p);
    const std::vector<Play>& plays() const;
    const Suit* leading() const;
    bool legal(const Card& c) const;
    const Player& winner() const;
};

#endif
