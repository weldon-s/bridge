#include "bids/bid.h"

Bid::Bid(bool pass) : pass{pass} {}

bool Bid::operator<(const Bid& other) const {
    if (level() != other.level()) {
        return level() < other.level();
    }

    return suit() < other.suit();
}

Bid::~Bid() {}
