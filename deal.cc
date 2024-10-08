#include "deal.h"

#include <array>
#include <random>
#include <vector>

#include "card.h"
#include "players/player.h"

Deal::Deal(std::array<Player*, 4> players, std::vector<Card*> perm) : cards_{perm}, players_{players}, leader_{nullptr}, trump_{nullptr} {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3);

    std::array<std::vector<Card*>, 4> player_cards;

    for (int i = 0; i < cards_.size(); ++i) {
        player_cards[i % 4].emplace_back(cards_[i]);
    }

    for (int i = 0; i < 4; ++i) {
        players[i]->set_cards(player_cards[i]);
    }
}

const Trick& Deal::play_trick() {
    if (!leader_) {
        leader_ = declarer()->next();
    }

    Trick t{contract()->bid->suit()};
    Player* current{leader_};

    for (int i = 0; i < 4; ++i) {
        t.add_play(*current);
        current = current->next();
    }

    leader_ = &t.winner();
    tricks_.emplace_back(t);

    return tricks_[tricks_.size() - 1];
}

Player* Deal::declarer() const {
    const BidPlay& contr{*contract()};

    for (auto iter = bids_.begin(); iter != bids_.end(); ++iter) {
        if ((iter->bid->suit() == contr.bid->suit()) &&
            ((&iter->player == &contr.player) || (iter->player.partner() == &contr.player))) {
            return &iter->player;
        }
    }

    // this is not needed, but keeps compiler from complaining
    return nullptr;
}

const BidPlay& Deal::play_bid() {
    // if no bids, assume first player is dealer
    // otherwise, get bid from player following last bidder
    Player* current{bids_.empty() ? players_[0] : bids_.back().player.next()};

    std::unique_ptr<Bid> bid{current->play_bid(bids_)};

    bids_.emplace_back(*current, std::move(bid));
    return bids_.back();
}

bool Deal::done_playing() const {
    // if we are passed out or we have played 13 tricks, we are done
    return (bids_.back().bid->level() == 0) || (tricks_.size() == 13);
}

bool Deal::done_bidding() const {
    // we will always have >= 4 bids if we are done
    // if first 3 pass, 4th can bid
    // otherwise, at least one player has bid + we need 3 passes to confirm their bid
    if (bids_.size() < 4) {
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

const BidPlay* Deal::contract() const {
    for (auto iter = bids_.rbegin(); iter != bids_.rend(); ++iter) {
        if (!iter->bid->pass) {
            return &*iter;
        }
    }

    return bids_.empty() ? nullptr : &bids_.back();
}

int Deal::tricks_taken() const {
    const Player* decl{declarer()};

    int count{0};

    for (const Trick& t : tricks_) {
        const Player* winner{&t.winner()};

        if ((decl == winner) || (decl->partner() == winner)) {
            ++count;
        }
    }

    return count;
}

const std::vector<Trick>& Deal::tricks() const {
    return tricks_;
}

const std::array<Player*, 4>& Deal::players() const {
    return players_;
}