#include "player.h"

#include <array>
#include <random>

#include "card.h"
#include "trick.h"

void Player::update_cards(std::vector<Card*> new_cards) {
    cards = new_cards;
    played = std::map<Card*, bool>();

    for (Card* c : cards) {
        played[c] = false;
    }
}

const Card& Player::select_card(const Trick& t) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, cards.size() - 1);

    Card* card{cards[dist(gen)]};

    while (!t.legal(*card) && !played[card]) {
        card = cards[dist(gen)];
    }

    played[card] = true;
    return *card;
}

Player* Player::next() const {
    return _next;
}

void Player::set_nexts(std::array<Player*, 4> players) {
    for (int i = 0; i < 3; ++i) {
        players[i]->_next = players[(i + 1) % 4];
    }
}
