#include "player.h"

#include <algorithm>
#include <array>
#include <stdexcept>

#include "card.h"
#include "trick.h"

void Player::set_cards(std::vector<Card*> new_cards) {
    cards_ = new_cards;
}

const Card& Player::play_card(const Trick& t) {
    const Card& choice{select_card(t)};

    const std::vector<Card*>& legal{legal_cards(t)};
    auto legal_iter{std::find_if(legal.begin(), legal.end(), [choice](Card* c) { return *c == choice; })};

    if (legal_iter == legal.end()) {
        throw std::logic_error{"illegal card"};
    }

    // this is ok since every Card* in legal is also in cards_
    auto iter{std::find_if(cards_.begin(), cards_.end(), [choice](Card* c) { return *c == choice; })};

    cards_.erase(iter);

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

const std::vector<Card*> Player::legal_cards(const Trick& t) const {
    std::vector<Card*> choices;

    for (Card* c : cards()) {
        if (t.following_suit(*c)) {
            choices.emplace_back(c);
        }
    }

    if (choices.empty()) {
        return cards_;
    }

    // we have to copy here, but the array has <=13 elements, so this is negligible
    return choices;
}

void Player::configure(std::array<Player*, 4>& players) {
    for (int i = 0; i < 4; ++i) {
        players[i]->next_ = players[(i + 1) % 4];
    }

    players[0]->position_ = 'N';
    players[1]->position_ = 'E';
    players[2]->position_ = 'S';
    players[3]->position_ = 'W';
}

Player::~Player() {}
