#include "view.h"

#define BLACK "\u001b[30m"
#define RED "\u001b[31m"
#define WHITE_BG "\u001b[;47m"
#define RESET "\u001b[0m"

std::ostream& operator<<(std::ostream& out, const Card& c) {
    out << WHITE_BG << BLACK << c.rank_char();

    if (c.suit() == Suit::diamonds() || c.suit() == Suit::hearts()) {
        out << RED;
    }

    out << c.suit().label() << RESET;
    return out;
}

std::ostream& operator<<(std::ostream& out, const Player& p) {
    out << p.position() << ':';

    for (Card* c : p.cards()) {
        out << ' ' << *c;
    }

    out << std::endl;

    return out;
}
