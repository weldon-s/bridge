#ifndef DOUBLE_H
#define DOUBLE_H

#include "bids/bid.h"

class Double : public Bid {
    const Bid& previous_;
    bool is_redoubled() const;

   protected:
    virtual int contract_points(int taken, bool vulnerable) const override;
    virtual int overtrick_points(int taken, bool vulnerable) const override;
    virtual int doubling_points(int taken, bool vulnerable) const override;
    virtual int penalty_points(int taken, bool vulnerable) const override;
    // TODO check what happens when a doubled bid has >=100 contract points but isn't 3+NT, 4+S/H, 5+D/C

   public:
    Double(const Bid& previous);

    std::string name() const override;
    int level() const override;
    const Suit& suit() const override;
};

#endif
