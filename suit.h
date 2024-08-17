#ifndef SUIT_H
#define SUIT_H

#include <string>

class Suit final {
   public:
    std::string name() const;
    std::string label() const;
    bool operator<(const Suit& other) const;
    bool operator==(const Suit& other) const;

    static const Suit& notrump();
    static const Suit& spades();
    static const Suit& hearts();
    static const Suit& diamonds();
    static const Suit& clubs();

   private:
    const std::string n;
    const std::string l;
    const int value;

    const static Suit& nt;
    const static Suit& s;
    const static Suit& h;
    const static Suit& d;
    const static Suit& c;

    Suit(std::string n, std::string l, int value);
};

#endif
