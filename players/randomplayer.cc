#include "players/randomplayer.h"

#include <random>

#include "card.h"
#include "trick.h"

const Card& RandomPlayer::select_card(const Trick& t) {
    std::random_device rd;
    std::mt19937 gen(rd());

    const std::vector<Card*>& legal{legal_cards(t)};

    std::uniform_int_distribution<> dist(0, legal.size() - 1);

    return *legal[dist(gen)];
}
