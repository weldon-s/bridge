#include "players/player.h"

#include <algorithm>
#include <array>
#include <stdexcept>

#include "card.h"
#include "trick.h"

void Player::set_cards(std::vector<Card*>& new_cards) {
    std::sort(new_cards.begin(), new_cards.end(), comparator(Suit::notrump));
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

std::unique_ptr<Bid> Player::play_bid(const std::vector<BidPlay>& bids) {
    std::unique_ptr<Bid> choice = select_bid(bids);

    // TODO somehow also prevent illegal doubles?
    // e.g. doubling on partner's bid or something like 1C 1DX
    if (*choice < *bids.back().bid) {
        throw std::logic_error{"illegal bid"};
    }

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

// cant have member function to pass in as comparator, so we need to do it this way
std::function<bool(const Card* c1, const Card* c2)> Player::comparator(const Suit& trump) {
    std::map<Suit, int> ordering;

    switch (trump.value) {
        case Suit::NOTRUMP:
        case Suit::SPADES:
            ordering = std::map<Suit, int>{{Suit::spades, 0}, {Suit::hearts, 1}, {Suit::clubs, 2}, {Suit::diamonds, 3}};
            break;

        case Suit::HEARTS:
            ordering = std::map<Suit, int>{{Suit::hearts, 0}, {Suit::spades, 1}, {Suit::diamonds, 2}, {Suit::clubs, 3}};
            break;

        case Suit::DIAMONDS:
            ordering = std::map<Suit, int>{{Suit::diamonds, 0}, {Suit::spades, 1}, {Suit::hearts, 2}, {Suit::clubs, 3}};
            break;

        case Suit::CLUBS:
            ordering = std::map<Suit, int>{{Suit::clubs, 0}, {Suit::hearts, 1}, {Suit::spades, 2}, {Suit::diamonds, 3}};
    }

    return [ordering](const Card* c1, const Card* c2) -> bool {
        if (c1->suit == c2->suit) {
            return c2->rank < c1->rank;
        }

        return ordering.at(c1->suit) < ordering.at(c2->suit);
    };
}

Player::~Player() {}
