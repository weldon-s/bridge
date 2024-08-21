#include "player.h"

#include <array>
#include <random>

#include "card.h"
#include "trick.h"

void Player::set_cards(std::vector<Card*> new_cards) {
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

char Player::position() const {
    return _position;
}

void Player::configure(std::array<Player*, 4> players) {
    for (int i = 0; i < 4; ++i) {
        players[i]->_next = players[(i + 1) % 4];
    }

    players[0]->_position = 'N';
    players[1]->_position = 'E';
    players[2]->_position = 'S';
    players[3]->_position = 'W';
}
