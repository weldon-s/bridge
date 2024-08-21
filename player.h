#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <vector>

class Card;
class Trick;

class Player {
    char position_{' '};
    Player* next_{nullptr};
    std::vector<Card*> cards_;
    // TODO see if we can just remove cards after being played

   public:
    void set_cards(std::vector<Card*> new_cards);
    const Card& select_card(const Trick& t);
    Player* next() const;
    char position() const;

    static void configure(std::array<Player*, 4> players);
};

#endif
