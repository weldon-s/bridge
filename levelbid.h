#ifndef LEVELBID_H
#define LEVELBID_H

#include "bid.h"

class LevelBid : public Bid {
    const int level_;
    const Suit& suit_;

   public:
    LevelBid(int l, const Suit& s);

    std::string name() const override;
    int level() const override;
    const Suit& suit() const override;

    static const int min_level{1};
    static const int max_level{7};
};

#endif