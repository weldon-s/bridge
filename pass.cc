#include "pass.h"

Pass::Pass(const Bid& previous) : previous_{previous} {}

std::string Pass::name() const {
    return "Pass";
}

int Pass::level() const {
    return previous_.level();
}

const Suit& Pass::suit() const {
    return previous_.suit();
}
