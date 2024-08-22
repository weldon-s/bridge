#include "hand.h"

#include <array>
#include <random>
#include <vector>

#include "card.h"
#include "player.h"

Hand::Hand(std::array<Player*, 4> players) : cards_{Card::all()}, players_{players}, leader_{nullptr}, trump_{nullptr} {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3);

    std::array<std::vector<Card*>, 4> player_cards;

    for (const std::unique_ptr<Card>& c : cards_) {
        int player{dist(gen)};

        while (player_cards[player].size() == num_tricks) {
            player = dist(gen);
        }

        player_cards[player].emplace_back(c.get());
    }

    for (int i = 0; i < 4; ++i) {
        players[i]->set_cards(player_cards[i]);
    }
}

const Trick& Hand::play_trick() {
    // TODO update to be left neighbour of declarer
    if (!leader_) {
        leader_ = players_[0];
    }

    Trick t;
    Player* current{leader_};

    for (int i = 0; i < 4; ++i) {
        t.add_play(*current);
        current = current->next();
    }

    leader_ = &t.winner();
    tricks_.emplace_back(t);

    return tricks_[tricks_.size() - 1];
}

bool Hand::done() {
    return tricks_.size() == 13;
}

const std::vector<Trick>& Hand::tricks() {
    return tricks_;
}

const std::array<Player*, 4>& Hand::players() const {
    return players_;
}