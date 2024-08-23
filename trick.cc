#include "trick.h"

#include "card.h"
#include "players/player.h"

const Suit* Trick::leading() const {
    return leading_;
}

const std::vector<Play>& Trick::plays() const {
    return plays_;
}

bool Trick::following_suit(const Card& c) const {
    return !leading_ || (*leading_ == c.suit);
}

void Trick::add_play(Player& p) {
    const Card& c{p.play_card(*this)};

    plays_.emplace_back(p, c);

    if (plays_.size() == 1) {
        leading_ = &c.suit;
    }
}

Player& Trick::winner() const {
    int highestRank{Card::min_rank - 1};
    Player* winner = nullptr;

    for (const Play& play : plays_) {
        if ((play.card.suit == *leading_) && (play.card.rank > highestRank)) {
            // TODO trump
            winner = &play.player;
            highestRank = play.card.rank;
        }
    }

    return *winner;
}
