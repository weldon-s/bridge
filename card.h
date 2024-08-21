#ifndef CARD_H
#define CARD_H

#include <memory>
#include <vector>

#include "suit.h"

class Card {
    const int rank_;
    const Suit& suit_;
    Card(int r, const Suit& s);

   public:
    int rank() const;
    const Suit& suit() const;
    std::string name() const;
    bool operator==(const Card& other) const;

    // we could treat aces as 1s, but this is easier since they're always high in bridge
    static const int min_rank{2};
    static const int max_rank{14};

    static std::vector<std::unique_ptr<Card>> all();
};

#endif
