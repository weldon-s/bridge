#ifndef SUIT_H
#define SUIT_H

#include <string>

class Suit final {
   public:
    enum Value {
        CLUBS,
        DIAMONDS,
        HEARTS,
        SPADES,
        NOTRUMP
    };

    const Value value;
    const std::string name;
    const std::string label;

    bool operator<(const Suit& other) const;
    bool operator==(const Suit& other) const;

    const static Suit& notrump;
    const static Suit& spades;
    const static Suit& hearts;
    const static Suit& diamonds;
    const static Suit& clubs;

    static const Suit& from_value(int v);

   private:
    Suit(std::string n, std::string l, Value value);
};

#endif
