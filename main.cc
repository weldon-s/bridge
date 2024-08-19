#include <time.h>

#include <iostream>

#include "hand.h"
#include "player.h"

int main() {
    Player p1, p2, p3, p4;
    std::array<Player*, 4> players{&p1, &p2, &p3, &p4};
    Hand h{players};
}
