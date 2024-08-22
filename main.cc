#include <time.h>

#include <iostream>

#include "double.h"
#include "hand.h"
#include "levelbid.h"
#include "randomplayer.h"
#include "view.h"

int main() {
    Bid* b = new LevelBid{3, Suit::spades};

    Bid* c = new Double{*b};

    std::cout << b->name() << ' ' << c->name() << std::endl;

    delete b;
    delete c;

    // RandomPlayer p1, p2, p3, p4;
    // std::array<Player*, 4> players{&p1, &p2, &p3, &p4};
    // Player::configure(players);
    // Hand h{players};

    // while (!h.done()) {
    //     std::cout << *h.players()[0];

    //     const Trick& t{h.play_trick()};

    //     for (const Play& p : t.plays()) {
    //         std::cout << p.player.position() << ": " << p.card << "    ";
    //     }

    //     std::cout << "(" << t.winner().position() << " wins)" << std::endl
    //               << std::endl;
    // }

    return 0;
}
