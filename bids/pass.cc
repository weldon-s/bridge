#include "bids/pass.h"

Pass::Pass(const Bid* previous) : previous_{previous} {}

std::string Pass::name() const {
    return "Pass";
}

int Pass::level() const {
    return previous_ ? previous_->level() : 0;
}

const Suit& Pass::suit() const {
    return previous_ ? previous_->suit() : Suit::notrump;
}
