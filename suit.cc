#include "suit.h"

const Suit& Suit::notrump{Suit("NT", "", Value::NOTRUMP)};
const Suit& Suit::spades{Suit("S", "♠", Value::SPADES)};
const Suit& Suit::hearts{Suit("H", "♥", Value::HEARTS)};
const Suit& Suit::diamonds{Suit("D", "♦", Value::DIAMONDS)};
const Suit& Suit::clubs{Suit("C", "♣", Value::CLUBS)};

Suit::Suit(std::string n, std::string l, Value value) : value{value}, name{n}, label{l} {}

bool Suit::operator<(const Suit& other) const {
    return value < other.value;
}

bool Suit::operator==(const Suit& other) const {
    return value == other.value;
}
