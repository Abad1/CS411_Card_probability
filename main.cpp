//main.cpp
//Cody Abad

#include "Deck.hpp"

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <algorithm>
using std::sort;




bool sameSuit(const vector<Card> &hand) {
    if ((hand[0].suit == hand[1].suit) &&
        (hand[1].suit == hand[2].suit)) {
        return true;
    }
    return false;
}

bool isStraight(vector<Card> hand) {

    sort(hand.begin(), hand.end(), [](Card l, Card r) {
        return (l.value < r.value);
        });

    if ((hand[2].value == (hand[1].value + 1)) &&
        (hand[1].value == (hand[0].value + 1))) {
        return true;
    }
    if ((hand[2].value == 13) &&
        (hand[1].value == 12) &&
        (hand[0].value == 1)){
        return true;
    }
    return false;
}
    
bool hasPair(const vector<Card> &hand) {
    for (int i = 0; i < hand.size(); i++) {
        for (int j = i + 1; j < hand.size(); j++) {
            if (hand[i].value == hand[j].value)
                return true;
        }
    }
    return false;
}
enum handType { SF, TOK, S, F, P, H };

handType determineHandType(const vector<Card> &hand) {

    //Straight flush
    if (isStraight(hand) && sameSuit(hand))
        return SF;

    //Three of a Kind
    if ((hand[0].value == hand[1].value) &&
        (hand[1].value == hand[2].value))
        return TOK;

    if (isStraight(hand))
        return S;

    if (sameSuit(hand))
        return F;

    if (hasPair(hand)) {
        return(P);
    }

    return H;
}

void probabilityCalculator(Deck deck) {
    vector<Card> hand(3);
    float straightFlush(0.0);
    float threeOfKind(0.0);
    float straight(0.0);
    float flush(0.0);
    float pair(0.0);
    float high(0.0);
    float total(0.0);
    float payout(0.0);

    for (int i = 0; i < (deck.getDeck().size() - 2); i++) {
        hand[0] = deck.getCard(i);
        for (int j = i + 1; j < (deck.getDeck().size() - 1); j++) {
            hand[1] = deck.getCard(j);
            for (int k = j + 1; k < deck.getDeck().size(); k++) {
                hand[2] = deck.getCard(k);
                switch (determineHandType(hand)) {
                case(SF): straightFlush++;
                    break;
                case(TOK): threeOfKind++;
                    break;
                case(S): straight++;
                    break;
                case(F): flush++;
                    break;
                case(P): pair++;
                    break;
                case(H): high++;
                    break;
                default: high++;
                }
            }
        }
    }
    total = straightFlush + threeOfKind + straight + flush + pair + high;
    cout << "Frequency of hands: " << endl;
    cout << "Straight Flush: " << straightFlush << endl;
    cout << "Three of a Kind: " << threeOfKind << endl;
    cout << "Straight: " << straight << endl;
    cout << "Flush: " << flush << endl;
    cout << "Pair: " << pair << endl;
    cout << "High Card: " << high << endl;
    cout << "Total Combinations: " << total << endl;
    cout << endl;

    //Probability
    straightFlush /= total;
    threeOfKind /= total;
    straight /= total;
    flush /= total;
    pair /= total;
    high /= total;
    cout << "Probability of Hands: " << endl;
    cout << "Straight Flush: " << straightFlush << endl;
    cout << "Three of a Kind: " << threeOfKind << endl;
    cout << "Straight: " << straight << endl;
    cout << "Flush: " << flush << endl;
    cout << "Pair: " << pair << endl;
    cout << "High Card: " << high << endl;
    cout << endl;

    //Return
    straightFlush *= 99;
    threeOfKind *= 29;
    straight *= 14;
    flush *= 4;
    pair *= 0;
    high *= -1;
    total = straightFlush + threeOfKind + straight + flush + pair + high;
    cout << "Expected return of game: " << endl;
    cout << "Straight Flush: " << straightFlush << endl;
    cout << "Three of a Kind: " << threeOfKind << endl;
    cout << "Straight: " << straight << endl;
    cout << "Flush: " << flush << endl;
    cout << "Pair: " << pair << endl;
    cout << "High Card: " << high << endl;
    cout << "Total: " << total << endl;
}

int main() {
  Deck deck;
  probabilityCalculator(deck);
}