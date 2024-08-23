#ifndef DOUBLE_H
#define DOUBLE_H

#include "bids/bid.h"

class Double : public Bid {
    const Bid& previous_;

   public:
    Double(const Bid& previous);

    std::string name() const override;
    int level() const override;
    const Suit& suit() const override;
};

#endif
