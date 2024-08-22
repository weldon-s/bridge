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

char Card::rank_char() const {
    switch (rank_) {
        case 10:  // ten
            return 'T';
        case 11:  // jack
            return 'J';
        case 12:  // queen
            return 'Q';
        case 13:  // king
            return 'K';
        case 14:  // ace
            return 'A';
        default:
            return rank_ + '0';
    }
}

const Suit& Card::suit() const {
    return suit_;
}

std::string Card::name() const {
    return rank_char() + suit_.label();
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
