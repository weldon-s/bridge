#include "bid.h"

#include <stdexcept>

Bid::Bid(int l, const Suit& s) : l{l}, s{s} {
    if ((l < min_level) || (l > max_level)) {
        throw std::invalid_argument{"invalid bid level"};
    }
}

std::string Bid::name() const {
    // TODO use proper string conversion
    return static_cast<char>(l + '0') + s.name();
}

const Suit& Bid::suit() const {
    return s;
}

int Bid::level() const {
    return l;
}

bool Bid::operator<(const Bid& other) const {
    if (l != other.l) {
        return l < other.l;
    }

    return s < other.s;
}
