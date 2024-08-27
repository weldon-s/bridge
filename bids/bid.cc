#include "bids/bid.h"

Bid::Bid(bool pass) : pass{pass} {}

bool Bid::operator<(const Bid& other) const {
    if (level() != other.level()) {
        return level() < other.level();
    }

    return suit() < other.suit();
}

int Bid::points(int taken, bool vulnerable) const {
    return level() == 0 ? 0 : contract_points(taken, vulnerable) + overtrick_points(taken, vulnerable) + slam_points(taken, vulnerable) + doubling_points(taken, vulnerable) + game_points(taken, vulnerable) - penalty_points(taken, vulnerable);
}

int Bid::contract_points(int taken, bool vulnerable) const {
    if (taken < (level() + book_size)) {
        return 0;
    }

    switch (suit().value) {
        case Suit::NOTRUMP:
            return level() * 30 + 10;
        case Suit::SPADES:
        case Suit::HEARTS:
            return level() * 30;
        default:  // diamonds or clubs
            return level() * 20;
    }
}

int Bid::overtrick_points(int taken, bool vulnerable) const {
    int overtricks{taken - (level() + book_size)};

    if (overtricks <= 0) {
        return 0;
    }

    switch (suit().value) {
        case Suit::NOTRUMP:
            return overtricks * 30 + 10;
        case Suit::SPADES:
        case Suit::HEARTS:
            return overtricks * 30;
        default:  // diamonds or clubs
            return overtricks * 20;
    }
}

int Bid::slam_points(int taken, bool vulnerable) const {
    if ((level() == 6) && (taken > (6 + book_size))) {
        return vulnerable ? 750 : 500;
    }

    if ((level() == 7) && (taken > (7 + book_size))) {
        return vulnerable ? 1500 : 1000;
    }

    return 0;
}

int Bid::doubling_points(int taken, bool vulnerable) const {
    return 0;
}

int Bid::penalty_points(int taken, bool vulnerable) const {
    int undertricks{level() + book_size - taken};

    if (undertricks <= 0) {
        return 0;
    }

    return vulnerable ? 100 * undertricks : 50 * undertricks;
}

int Bid::game_points(int taken, bool vulnerable) const {
    if (taken >= (level() + book_size)) {
        if (contract_points(taken, vulnerable) < 100) {
            return 50;
        }

        return vulnerable ? 500 : 300;
    }

    return 0;
}

Bid::~Bid() {}
