#include "hand.h"

#include <array>
#include <random>
#include <vector>

#include "card.h"
#include "players/player.h"

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

const BidPlay& Hand::play_bid() {
    // if no bids, assume first player is dealer
    // otherwise, get bid from player following last bidder
    Player* current{bids_.empty() ? players_[0] : bids_.back().player.next()};

    std::unique_ptr<Bid> bid{current->play_bid(bids_)};

    bids_.emplace_back(*current, std::move(bid));
    return bids_.back();
}

bool Hand::done_playing() const {
    // if we are passed out or we have played 13 tricks, we are done
    return (bids_.back().bid->level() == 0) || (tricks_.size() == 13);
}

bool Hand::done_bidding() const {
    // need at least 3 passes -> need at least 3 bids
    if (bids_.size() < 3) {
        return false;
    }

    auto iter = bids_.rbegin();

    // check if last 3 bids are all passes
    for (int i = 0; i < 3; ++iter, ++i) {
        if (!iter->bid->pass) {
            return false;
        }
    }

    return true;
}

const Bid* Hand::contract() const {
    for (auto iter = bids_.rbegin(); iter != bids_.rend(); ++iter) {
        if (!iter->bid->pass) {
            return iter->bid.get();
        }
    }

    return bids_.empty() ? nullptr : bids_.back().bid.get();
}

const std::vector<Trick>& Hand::tricks() const {
    return tricks_;
}

const std::array<Player*, 4>& Hand::players() const {
    return players_;
}