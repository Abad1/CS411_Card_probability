//Deck.cpp
//Cody Abad
#include "Deck.hpp"

#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>
using std::swap;

Deck::Deck(){
  for(int j = 0; j < 4; j++){
    for(int i = 1; i <= 13; i++){
      struct Card card;
      card.suit = static_cast<Suit>(j);
      card.value = i;
      _cards.push_back(card);
    }
  }
}

void Deck::printCards() const{
  for(auto i:_cards){
    switch(i.suit){
      case(Spade): cout << "Spade, ";
      break;
      case(Club): cout << "Club, ";
      break;
      case(Heart): cout << "Heart, ";
      break;
      case(Diamond): cout << "Diamond, ";
      break;
      default: cout << "Invalid suit, ";
    }
    switch(i.value){
      case(1): cout << "Ace" << endl;
      break;
      case(11): cout << "Jack" << endl;
      break;
      case(12): cout << "Queen" << endl;
      break;
      case(13): cout << "King" << endl;
      break;
      default: cout << i.value << endl;
    }
  }
}

void Deck::shuffle(){
  for (int k = 0; k < _cards.size(); k++) {
      int r = k + rand() % (_cards.size() - k);
      swap(_cards[k], _cards[r]);
  }
}

void Deck::cardCombos() const{
  int count = 0;
  for (int i = 0; i < (_cards.size()-2); i++){
    for(int j = i+1; j < (_cards.size()-1); j++){
      for(int k = j+1; k < _cards.size(); k++){
        count++;
        cout << _cards[i].suit << ", " << _cards[i].value << ", " << _cards[j].suit << ", " << _cards[j].value << ", " << _cards[k].suit << ", " << _cards[k].value << endl;
      }
    }
  }
  cout << count;
}

std::vector<Card> Deck::getDeck() const
{
    return _cards;
}

Card Deck::getCard(int index) const
{
    return _cards[index];
}
