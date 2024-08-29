#ifndef BID_H
#define BID_H

#include <memory>

#include "suit.h"

class Player;

class Bid {
   private:
   public:
    Bid(bool pass);
    static const int book_size{6};

    const bool pass;
    bool operator<(const Bid& other) const;

    virtual int contract_points(int taken, bool vulnerable) const;
    virtual int overtrick_points(int taken, bool vulnerable) const;
    virtual int slam_points(int taken, bool vulnerable) const;
    virtual int doubling_points(int taken, bool vulnerable) const;
    virtual int penalty_points(int taken, bool vulnerable) const;
    virtual int game_points(int taken, bool vulnerable) const;

    int points(int taken, bool vulnerable) const;
    virtual std::string name() const = 0;
    virtual int level() const = 0;
    virtual const Suit& suit() const = 0;
    virtual ~Bid();
};

struct BidPlay {
    Player& player;
    std::unique_ptr<Bid> bid;
};
#endif
