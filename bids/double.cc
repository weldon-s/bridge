#include "bids/double.h"

#include <algorithm>
#include <stdexcept>

Double::Double(const Bid& previous) : Bid{false}, previous_{previous} {
    const std::string& prev{previous_.name()};
    const std::string& double_x{"XX"};  // cost of this is negligible since bids are not created often
    // also, most bids are not doubles

    if (std::equal(double_x.rbegin(), double_x.rend(), prev.rbegin())) {
        throw std::invalid_argument{"cannot double a redouble"};
    }
}

constexpr bool Double::is_redoubled() const {
    return previous_.name().back() == 'X';
}

std::string Double::name() const {
    return previous_.name() + 'X';
}

int Double::level() const {
    return previous_.level();
}

const Suit& Double::suit() const {
    return previous_.suit();
}

int Double::contract_points(int taken, bool vulnerable) const {
    return previous_.contract_points(taken, vulnerable) * 2;
}

int Double::overtrick_points(int taken, bool vulnerable) const {
    int overtricks{taken - (level() + book_size)};

    if (overtricks <= 0) {
        return 0;
    }

    int per_overtrick{100};

    if (vulnerable) {
        per_overtrick *= 2;
    }

    if (is_redoubled()) {
        per_overtrick *= 2;
    }

    return overtricks * per_overtrick;
}

int Double::doubling_points(int taken, bool vulnerable) const {
    if (taken >= (level() + book_size)) {
        return is_redoubled() ? 100 : 50;
    }

    return 0;
}

int Double::penalty_points(int taken, bool vulnerable) const {
    if (vulnerable) {
        return penalty_points(taken + 1, false);
    }

    if (is_redoubled()) {
        return previous_.penalty_points(taken, vulnerable) * 2;
    }

    int undertricks{level() + book_size - taken};

    if (undertricks <= 0) {
        return 0;
    }

    // logic below is a result of the following system (when not vulnerable)
    // 1st undertrick is 100
    // 2nd, 3rd are 200 each
    // 4th+ are 300 each
    if (undertricks == 1) {
        return 100;
    }

    if (undertricks <= 3) {
        return 100 + (undertricks - 1) * 200;
    }

    return 500 + (undertricks - 3) * 300;
}
