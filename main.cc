#include <iostream>

#include "card.h"

int main() {
    Card c{13, Suit::clubs()};

    std::cout << c.name() << std::endl;
}
