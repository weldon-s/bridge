#ifndef BID_H
#define BID_H

#include <memory>

#include "suit.h"

class Player;

class Bid {
   public:
    bool operator<(const Bid& other) const;
    virtual std::string name() const = 0;
    virtual int level() const = 0;
    virtual const Suit& suit() const = 0;
    // TODO method to get points
    virtual ~Bid();
};

struct BidPlay {
    Player& player;
    std::unique_ptr<Bid> bid;
};
#endif
