
#include "bids/levelbid.h"

#include <stdexcept>

LevelBid::LevelBid(int l, const Suit& s) : level_{l}, suit_{s} {
    if ((l < min_level) || (l > max_level)) {
        throw std::invalid_argument{"invalid bid level"};
    }
}

std::string LevelBid::name() const {
    return std::to_string(level_) + suit_.name;
}

int LevelBid::level() const {
    return level_;
}

const Suit& LevelBid::suit() const {
    return suit_;
}