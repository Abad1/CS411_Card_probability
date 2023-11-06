//Card.hpp
//Cody Abad
#pragma once

#include <vector>

enum Suit{Spade,Club,Heart,Diamond};

struct Card{
int value;
Suit suit;
};

class Deck{
public:
  Deck();
  void printCards() const;
  void shuffle();
  void cardCombos();
private:
  std::vector<Card> _cards;
};