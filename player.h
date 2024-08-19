#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <set>

class Card;

class Player {
    std::set<Card*> cards;
    std::map<Card*, bool> played;

   public:
    void update_cards(std::set<Card*> new_cards);
};

#endif
