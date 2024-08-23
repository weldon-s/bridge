#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include <random>

#include "players/player.h"

class RandomPlayer : public Player {
   public:
    RandomPlayer();

   private:
    std::mt19937 mt_;
    const Card& select_card(const Trick& t) override;
    std::unique_ptr<Bid> select_bid(const std::vector<BidPlay>& bids) override;
};

#endif
