#include "card.h"

#include <stdexcept>

Card::Card(int r, const Suit& s) : r{r}, s{s} {
    if (s == Suit::notrump()) {
        throw std::invalid_argument{"invalid card suit"};
    }

    if ((r < min_rank) || (r > max_rank)) {
        throw std::invalid_argument{"invalid card rank"};
    }
}

int Card::rank() const {
    return r;
}

const Suit& Card::suit() const {
    return s;
}

std::string Card::name() const {
    switch (r) {
        case 11:  // jack
            return 'J' + s.label();
        case 12:  // queen
            return 'Q' + s.label();
        case 13:  // king
            return 'K' + s.label();
        case 14:  // ace
            return 'A' + s.label();
        default:
            return static_cast<char>('0' + r) + s.label();
    }
};
