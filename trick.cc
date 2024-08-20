#include "trick.h"

#include "card.h"
#include "player.h"

const Suit* Trick::leading() const {
    return _leading;
}

const std::vector<Play>& Trick::plays() const {
    return _plays;
}

bool Trick::legal(const Card& c) const {
    return !_leading || (*_leading == c.suit());
}

void Trick::add_play(Player& p) {
    const Card& c{p.select_card(*this)};

    _plays.emplace_back(p, c);

    if (_plays.size() == 1) {
        _leading = &c.suit();
    }
}

const Player& Trick::winner() const {
    int highestRank{Card::min_rank - 1};
    const Player* winner = nullptr;

    for (const Play& play : _plays) {
        if ((play.card.suit() == *_leading) && (play.card.rank() > highestRank)) {
            // TODO trump
            winner = &play.player;
        }
    }

    return *winner;
}
