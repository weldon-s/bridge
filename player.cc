#include "player.h"

#include <algorithm>
#include <array>

#include "card.h"
#include "trick.h"

void Player::set_cards(std::vector<Card*> new_cards) {
    cards_ = new_cards;
}

const Card& Player::play_card(const Trick& t) {
    const Card& choice{select_card(t)};
    cards_.erase(std::find_if(cards_.begin(), cards_.end(), [choice](Card* c) { return *c == choice; }));

    return choice;
}

Player* Player::next() const {
    return next_;
}

char Player::position() const {
    return position_;
}

const std::vector<Card*>& Player::cards() const {
    return cards_;
}

void Player::configure(std::array<Player*, 4> players) {
    for (int i = 0; i < 4; ++i) {
        players[i]->next_ = players[(i + 1) % 4];
    }

    players[0]->position_ = 'N';
    players[1]->position_ = 'E';
    players[2]->position_ = 'S';
    players[3]->position_ = 'W';
}

Player::~Player() {}
