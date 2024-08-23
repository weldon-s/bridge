#ifndef VIEW_H
#define VIEW_H

#include <iostream>

#include "bids/bid.h"
#include "card.h"
#include "players/player.h"

std::ostream& operator<<(std::ostream& out, const Card& c);
std::ostream& operator<<(std::ostream& out, const Player& p);
std::ostream& operator<<(std::ostream& out, const Bid& b);
std::ostream& operator<<(std::ostream& out, const BidPlay& bp);

#endif
