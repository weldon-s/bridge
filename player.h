#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <vector>

class Card;
class Trick;

class Player {
    Player* _next{nullptr};
    std::vector<Card*> cards;
    std::map<Card*, bool> played;

   public:
    void update_cards(std::vector<Card*> new_cards);
    const Card& select_card(const Trick& t);
    Player* next() const;

    static void set_nexts(std::array<Player*, 4> players);
};

#endif
