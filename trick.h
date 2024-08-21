#ifndef TRICK_H
#define TRICK_H

#include <vector>

class Player;
class Card;
class Suit;

struct Play {
    Player& player;
    const Card& card;
};

class Trick {
    std::vector<Play> plays_;
    const Suit* leading_{nullptr};
    // TODO field for trump

   public:
    void add_play(Player& p);
    const std::vector<Play>& plays() const;
    const Suit* leading() const;
    bool following_suit(const Card& c) const;
    Player& winner() const;
};

#endif
