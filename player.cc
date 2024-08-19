#include "player.h"

#include "card.h"

void Player::update_cards(std::set<Card*> new_cards) {
    cards = new_cards;
    played = std::map<Card*, bool>();

    for (Card* c : cards) {
        played[c] = false;
    }
}
