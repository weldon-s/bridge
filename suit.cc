#include "suit.h"

const Suit& Suit::nt{Suit("NT", 4)};
const Suit& Suit::s{Suit("S", 3)};
const Suit& Suit::h{Suit("H", 2)};
const Suit& Suit::d{Suit("D", 1)};
const Suit& Suit::c{Suit("C", 0)};

Suit::Suit(std::string l, int value) : l{l}, value{value} {}

std::string Suit::label() const {
    return l;
}

bool Suit::operator<(const Suit& other) const {
    return value < other.value;
}

const Suit& Suit::notrump() {
    return nt;
}

const Suit& Suit::spades() {
    return s;
}

const Suit& Suit::hearts() {
    return h;
}

const Suit& Suit::diamonds() {
    return d;
}

const Suit& Suit::clubs() {
    return c;
}