#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <map>
#include <vector>

class Card;
class Trick;

class Player {
    char position_{' '};
    Player* next_{nullptr};
    std::vector<Card*> cards_;
    virtual const Card& select_card(const Trick& t) = 0;

   public:
    void set_cards(std::vector<Card*> new_cards);

    const std::vector<Card*>& cards() const;
    const std::vector<Card*> legal_cards(const Trick& t) const;

    const Card& play_card(const Trick& t);
    Player* next() const;
    char position() const;

    static void configure(std::array<Player*, 4>& players);
    virtual ~Player();
};

#endif
