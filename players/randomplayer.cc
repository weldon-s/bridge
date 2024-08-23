#include "players/randomplayer.h"

#include "bids/levelbid.h"
#include "bids/pass.h"
#include "card.h"
#include "trick.h"

RandomPlayer::RandomPlayer() : mt_{std::random_device()()} {
}

const Card& RandomPlayer::select_card(const Trick& t) {
    const std::vector<Card*>& legal{legal_cards(t)};
    std::uniform_int_distribution<> dist(0, legal.size() - 1);
    return *legal[dist(mt_)];
}

std::unique_ptr<Bid> RandomPlayer::select_bid(const std::vector<BidPlay>& bids) {
    std::bernoulli_distribution pass_dist{0.75};

    if (pass_dist(mt_) ||
        (!bids.empty() && bids.back().bid->level() == 7 && bids.back().bid->suit() == Suit::notrump)) {
        return std::make_unique<Pass>(bids.empty() ? nullptr : bids.back().bid.get());
    }

    // TODO doubles?
    std::uniform_int_distribution level_dist(1, 7);
    std::uniform_int_distribution suit_dist(0, 4);

    while (true) {
        LevelBid lb{level_dist(mt_), Suit::from_value(suit_dist(mt_))};

        if (bids.empty() || (*bids.back().bid < lb)) {
            return std::make_unique<LevelBid>(lb);
        }
    }
}
