#ifndef BID_H
#define BID_H
#include "suit.h"

class Bid {
   public:
    Bid(int l, const Suit& s);
    const int level;
    const Suit& suit;

    std::string name() const;
    bool operator<(const Bid& other) const;

    static const int min_level{1};
    static const int max_level{7};
};
#endif
