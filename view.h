#ifndef VIEW_H
#define VIEW_H

#include <iostream>

#include "card.h"
#include "players/player.h"

std::ostream& operator<<(std::ostream& out, const Card& c);
std::ostream& operator<<(std::ostream& out, const Player& p);

#endif
