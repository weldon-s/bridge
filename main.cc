#include <iostream>

#include "suit.h"

int main() {
    Suit s{Suit::spades()};
    std::cout << s.label() << std::endl;
    return 0;
}