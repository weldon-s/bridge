#include "trick.h"

#include "card.h"
#include "players/player.h"

Trick::Trick(const Suit& trump) : trump{trump} {}

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
    int highest_rank{Card::min_rank - 1};
    Player* winner{nullptr};
    bool has_trump{false};

    for (const Play& play : plays_) {
        // three ways a player can "place" higher than all previous:
        //  1. plays highest trump if trump already played
        //  2. plays highest of leading suit if no trumps already played
        //  3. plays any trump if no trumps already played
        if ((has_trump && (play.card.suit == trump) && (play.card.rank > highest_rank)) ||
            (!has_trump && (play.card.suit == *leading_) && (play.card.rank > highest_rank)) ||
            (!has_trump && (play.card.suit == trump))) {
            winner = &play.player;
            highest_rank = play.card.rank;

            if (!has_trump && (play.card.suit == trump)) {
                has_trump = true;
            }
        }
    }

    return *winner;
}
