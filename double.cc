#include "double.h"

#include <algorithm>
#include <stdexcept>

Double::Double(const Bid& previous) : previous_{previous} {
    const std::string& prev{previous_.name()};
    const std::string& double_x{"XX"};  // cost of this is negligible since bids are not created often
    // also, most bids are not doubles

    if (std::equal(double_x.rbegin(), double_x.rend(), prev.rbegin())) {
        throw std::invalid_argument{"cannot double a redouble"};
    }
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
