#include "card.h"

#include <stdexcept>

Card::Card(int r, const Suit& s) : rank{r}, suit{s} {
    if (s == Suit::notrump) {
        throw std::invalid_argument{"invalid card suit"};
    }

    if ((r < min_rank) || (r > max_rank)) {
        throw std::invalid_argument{"invalid card rank"};
    }
}

char Card::rank_char() const {
    switch (rank) {
        case 10:  // ten
            return 'T';
        case 11:  // jack
            return 'J';
        case 12:  // queen
            return 'Q';
        case 13:  // king
            return 'K';
        case 14:  // ace
            return 'A';
        default:
            return rank + '0';
    }
}

std::string Card::name() const {
    return rank_char() + suit.label;
};

bool Card::operator==(const Card& other) const {
    return (rank == other.rank) && (suit == other.suit);
}

std::vector<std::unique_ptr<Card>> Card::all() {
    std::vector<std::unique_ptr<Card>> cards{};

    for (int i = min_rank; i <= max_rank; ++i) {
        cards.emplace_back(std::unique_ptr<Card>(new Card{i, Suit::spades}));
        cards.emplace_back(std::unique_ptr<Card>(new Card{i, Suit::hearts}));
        cards.emplace_back(std::unique_ptr<Card>(new Card{i, Suit::diamonds}));
        cards.emplace_back(std::unique_ptr<Card>(new Card{i, Suit::clubs}));
    }

    return cards;
}
