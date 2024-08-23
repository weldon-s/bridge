#ifndef PASS_H
#define PASS_H

#include "bids/bid.h"

class Pass : public Bid {
    const Bid& previous_;

   public:
    Pass(const Bid& previous);

    std::string name() const override;
    int level() const override;
    const Suit& suit() const override;
};

#endif
