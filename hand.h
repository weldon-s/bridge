#ifndef HAND_H
#define HAND_H

#include <array>
#include <memory>
#include <vector>

#include "bids/bid.h"
#include "card.h"
#include "trick.h"

class Player;

class Hand {
    static const int num_tricks{13};

    const std::vector<std::unique_ptr<Card>> cards_;
    std::array<Player*, 4> players_;
    std::vector<Trick> tricks_;
    Player* leader_;
    Suit* trump_;
    std::vector<BidPlay> bids_;
    Player* declarer() const;

   public:
    Hand(std::array<Player*, 4> players);
    bool done_playing() const;
    bool done_bidding() const;
    int tricks_taken() const;
    const BidPlay* contract() const;
    const std::vector<Trick>& tricks() const;
    const std::array<Player*, 4>& players() const;
    const Trick& play_trick();
    const BidPlay& play_bid();
};

#endif
