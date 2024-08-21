#include "suit.h"

const Suit& Suit::nt{Suit("NT", "", 4)};
const Suit& Suit::s{Suit("S", "♠", 3)};
const Suit& Suit::h{Suit("H", "♥", 2)};
const Suit& Suit::d{Suit("D", "♦", 1)};
const Suit& Suit::c{Suit("C", "♣", 0)};

Suit::Suit(std::string n, std::string l, int value) : name_{n}, label_{l}, value{value} {}

std::string Suit::name() const {
    return name_;
}

std::string Suit::label() const {
    return label_;
}

bool Suit::operator<(const Suit& other) const {
    return value < other.value;
}

bool Suit::operator==(const Suit& other) const {
    return value == other.value;
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