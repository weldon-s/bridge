#include "bid.h"

#include <stdexcept>

Bid::Bid(int l, const Suit& s) : level_{l}, suit_{s} {
    if ((level_ < min_level) || (level_ > max_level)) {
        throw std::invalid_argument{"invalid bid level"};
    }
}

std::string Bid::name() const {
    return std::to_string(level_) + suit_.name();
}

const Suit& Bid::suit() const {
    return suit_;
}

int Bid::level() const {
    return level_;
}

bool Bid::operator<(const Bid& other) const {
    if (level_ != other.level_) {
        return level_ < other.level_;
    }

    return suit_ < other.suit_;
}
