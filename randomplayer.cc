#include "randomplayer.h"

#include <random>

#include "card.h"
#include "trick.h"

const Card& RandomPlayer::select_card(const Trick& t) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<Card*> choices;

    for (Card* c : cards()) {
        if (t.following_suit(*c)) {
            choices.emplace_back(c);
        }
    }

    if (choices.empty()) {
        choices = cards();
    }

    std::uniform_int_distribution<> dist(0, choices.size() - 1);

    return *choices[dist(gen)];
}
