#include "player.h"

#include <algorithm>
#include <array>
#include <random>

#include "card.h"
#include "trick.h"

void Player::set_cards(std::vector<Card*> new_cards) {
    cards_ = new_cards;
}

const Card& Player::select_card(const Trick& t) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<Card*> choices;

    for (Card* c : cards_) {
        if (t.following_suit(*c)) {
            choices.emplace_back(c);
        }
    }

    if (choices.empty()) {
        choices = cards_;
    }

    std::uniform_int_distribution<> dist(0, choices.size() - 1);

    Card* ret{choices[dist(gen)]};
    cards_.erase(std::find_if(cards_.begin(), cards_.end(), [ret](Card* c) { return *c == *ret; }));

    return *ret;
}

Player* Player::next() const {
    return next_;
}

char Player::position() const {
    return position_;
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
