#include <iostream>
#include <memory>

#include "bids/double.h"
#include "bids/levelbid.h"
#include "deal.h"
#include "players/randomplayer.h"
#include "view.h"

int main() {
    std::vector<std::unique_ptr<Card>> cards{Card::all()};

    RandomPlayer p1, p2, p3, p4;
    std::array<Player*, 4> players{&p1, &p2, &p3, &p4};
    Player::configure(players);
    Deal h{players, Card::shuffle_all(cards)};

    while (!h.done_bidding()) {
        const BidPlay& bp{h.play_bid()};

        std::cout << bp << std::endl;
    }

    std::cout << "contract is " << *h.contract() << std::endl;

    while (!h.done_playing()) {
        std::cout << *h.players()[0];

        const Trick& t{h.play_trick()};

        for (const Play& p : t.plays()) {
            std::cout << p.player.position() << ": " << p.card << "    ";
        }

        std::cout << "(" << t.winner().position() << " wins)" << std::endl
                  << std::endl;
    }

    std::cout << "Declarer and dummy took " << h.tricks_taken() << " tricks " << std::endl;
    std::cout << "Points: " << h.contract()->bid->points(h.tricks_taken(), false) << std::endl;

    return 0;
}
