#include "suit.h"

#include <stdexcept>

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

const Suit& Suit::from_value(int v) {
    switch (v) {
        case NOTRUMP:
            return notrump;
        case SPADES:
            return spades;
        case HEARTS:
            return hearts;
        case DIAMONDS:
            return diamonds;
        case CLUBS:
            return clubs;
        default:
            throw std::invalid_argument{"no suit with given value"};
    }
}
