#include "bid.h"

#include <stdexcept>

Bid::Bid(int l, const Suit& s) : level{l}, suit{s} {
    if ((level < min_level) || (level > max_level)) {
        throw std::invalid_argument{"invalid bid level"};
    }
}

std::string Bid::name() const {
    return std::to_string(level) + suit.name;
}

bool Bid::operator<(const Bid& other) const {
    if (level != other.level) {
        return level < other.level;
    }

    return suit < other.suit;
}
