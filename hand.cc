#include "hand.h"

#include <array>
#include <random>
#include <set>

#include "card.h"
#include "player.h"

Hand::Hand(std::array<Player*, 4> players) : players{players} {
    auto cards{Card::all_cards()};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3);

    std::array<std::set<Card*>, 4> player_cards;

    for (std::unique_ptr<Card>& cptr : cards) {
        int player{dist(gen)};

        while (player_cards[player].size() == 13) {
            player = dist(gen);
        }

        player_cards[player].emplace(cptr.get());
    }

    for (int i = 0; i < 4; ++i) {
        players[i]->update_cards(player_cards[i]);
    }
}
