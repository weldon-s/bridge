#ifndef BID_H
#define BID_H
#include "suit.h"

class Bid {
    const int level_;
    const Suit& suit_;

   public:
    Bid(int l, const Suit& s);
    std::string name() const;
    const Suit& suit() const;
    int level() const;
    bool operator<(const Bid& other) const;

    static const int min_level{1};
    static const int max_level{7};
};
#endif
