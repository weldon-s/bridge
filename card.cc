#include "card.h"

#include <stdexcept>

Card::Card(int r, const Suit& s) : rank_{r}, suit_{s} {
    if (s == Suit::notrump()) {
        throw std::invalid_argument{"invalid card suit"};
    }

    if ((r < min_rank) || (r > max_rank)) {
        throw std::invalid_argument{"invalid card rank"};
    }
}

int Card::rank() const {
    return rank_;
}

const Suit& Card::suit() const {
    return suit_;
}

std::string Card::name() const {
    switch (rank_) {
        case 10:  // ten (everything is one character long)
            return "T" + suit_.label();
        case 11:  // jack
            return 'J' + suit_.label();
        case 12:  // queen
            return 'Q' + suit_.label();
        case 13:  // king
            return 'K' + suit_.label();
        case 14:  // ace
            return 'A' + suit_.label();
        default:
            return std::to_string(rank_) + suit_.label();
    }
};

bool Card::operator==(const Card& other) const {
    return (rank_ == other.rank_) && (suit_ == other.suit_);
}

std::vector<std::unique_ptr<Card>> Card::all() {
    std::vector<std::unique_ptr<Card>> cards{};

    for (int i = min_rank; i <= max_rank; ++i) {
        cards.emplace_back(std::unique_ptr<Card>(new Card{i, Suit::spades()}));
        cards.emplace_back(std::unique_ptr<Card>(new Card{i, Suit::hearts()}));
        cards.emplace_back(std::unique_ptr<Card>(new Card{i, Suit::diamonds()}));
        cards.emplace_back(std::unique_ptr<Card>(new Card{i, Suit::clubs()}));
    }

    return cards;
}
