#include <time.h>

#include <iostream>

#include "hand.h"
#include "player.h"

int main() {
    Player p1, p2, p3, p4;
    std::array<Player*, 4> players{&p1, &p2, &p3, &p4};
    Player::configure(players);
    Hand h{players};

    h.play();

    for (const Trick& t : h.tricks()) {
        for (const Play& p : t.plays()) {
            std::cout << p.player.position() << ": " << p.card.name() << "    ";
        }

        std::cout << "(" << t.winner().position() << " wins)" << std::endl;
    }
}
