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
using std::max;

double payout[] = { 250,100,100,30,15,5,1,0 };


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
        (hand[0].value == 1)) {
        return true;
    }
    return false;
}

bool hasPair(const vector<Card>& hand) {
    for (int i = 0; i < hand.size(); i++) {
        for (int j = i + 1; j < hand.size(); j++) {
            if (hand[i].value == hand[j].value)
                return true;
        }
    }
    return false;
}
enum handType { RF, AAA, SF, TOK, S, F, P, H };

handType determineHandType(const vector<Card>& hand) {
    //Royal flush
    if (isStraight(hand) && sameSuit(hand)) {
        auto temp = hand;
        sort(temp.begin(), temp.end(), [](Card l, Card r) {
            return (l.value < r.value);
            });
        if (hand[0].value == 1 && hand[1].value == 12 && hand[2].value == 13)
            return RF;
    }
    //Three Aces
    if (hand[0].value == 1) {
        if (hand[1].value == 1 && hand[2].value == 1)
            return AAA;
    }
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


double probabilityOf(const vector<Card>& hand) {
    return 0;
}

void printCards(const vector<Card>& hand) {
    for (auto i : hand) {
        switch (i.value) {
        case(1):cout << "Ace";
            break;
        case(11):cout << "Jack";
            break;
        case(12):cout << "Queen";
            break;
        case(13):cout << "King";
            break;
        default:cout << i.value;
        }
        cout << ", ";
        switch (i.suit) {
        case(Spade):cout << "Spades";
            break;
        case(Club):cout << "Clubs";
            break;
        case(Heart):cout << "Hearts";
            break;
        case(Diamond):cout << "Diamonds";
            break;
        default:
            break;
        }
        cout << endl;
    }
    cout << endl;
}
bool cardIsIn(const Card& card, const vector<Card>& hand) {
    for (auto i : hand) {
        if ((card.suit == i.suit) && (card.value == i.value)) {
            return true;
        }
    }
    return false;
}

double expectedValueOfSwap(const vector<Card>& hand, bool firstCard = false, bool secondCard = false, bool thirdCard = false) {
    Deck deck;
    auto temp = hand;
    Card newCard;
    double total(0.0);
    int card(0);
    bool twoCards = false;
    bool threeCards = false;
    if (((firstCard && secondCard) || (firstCard && thirdCard)) || (secondCard && thirdCard)) {
        twoCards = true;
    }
    if ((firstCard && secondCard) && thirdCard){
        threeCards = true;
    }
    if (!twoCards && !threeCards) {
        if (firstCard) {
            card = 0;
        }
        if (secondCard) {
            card = 1;
        }
        if (thirdCard) {
            card = 2;
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 1; j < 14; j++) {
                newCard.value = j;
                newCard.suit = static_cast<Suit>(i);
                if (!cardIsIn(newCard, hand)) {
                    temp[card] = newCard;
                    total += payout[static_cast<int>(determineHandType(temp))];
                }

            }
        }
        return total / 49;
    }
    if (!threeCards) {
        if (!firstCard) {
            card = 0;
        }
        if (!secondCard) {
            card = 1;
        }
        if (!thirdCard) {
            card = 2;
        }
        temp[0] = hand[card];

        for (int i = 0; i < deck.getDeck().size() - 1; i++) {
            if (!cardIsIn(deck.getCard(i),hand)) {
                temp[1] = deck.getCard(i);
                for (int j = i + 1; j < deck.getDeck().size(); j++) {
                    if (!cardIsIn(deck.getCard(j), hand)) {
                        temp[2] = deck.getCard(j);
                        total += payout[static_cast<int>(determineHandType(temp))];
                    }
                }
            }
        }
        return total / 1176;
    }

    for (int i = 0; i < deck.getDeck().size() - 2; i++) {
        if (!cardIsIn(deck.getCard(i), hand)) {
            temp[0] = deck.getCard(i);
            for (int j = i + 1; j < deck.getDeck().size()-1; j++) {
                if (!cardIsIn(deck.getCard(j), hand)) {
                    temp[1] = deck.getCard(j);
                    for (int k = j + 1; k < deck.getDeck().size(); k++) {
                        if (!cardIsIn(deck.getCard(k), hand)) {
                            temp[2] = deck.getCard(j);
                            total += payout[static_cast<int>(determineHandType(temp))];
                        }
                    }
                }
            }
        }
    }
    return total/18424;
}
double perfectPlay(const vector<Card>& hand) {
    double keep = 0.0, first = 0.0, second = 0.0, third = 0.0, firstSecond = 0.0, firstThird = 0.0, secondThird = 0.0, all = 0.0;
    
    double max(0);
    int best(0);
    int count(0);
    //keep all cards
    keep = payout[static_cast<int>(determineHandType(hand))];
    //swap first card
    first = expectedValueOfSwap(hand, true);
    //swap second card
    second = expectedValueOfSwap(hand, false,true);
    //swap third card
    third = expectedValueOfSwap(hand, false,false,true);
    //swap first and second
    firstSecond = expectedValueOfSwap(hand, true, true);
    //swap first and third
    firstThird = expectedValueOfSwap(hand, true, false, true);
    //swap second and third
    secondThird = expectedValueOfSwap(hand, false, true, true);
    //swap all
    all = expectedValueOfSwap(hand, true, true, true);

    vector<double> plays = { keep,first,second,third,firstSecond,firstThird,secondThird,all };
    /*
    cout << "Expected value of plays: " << endl;
    cout << endl;
    cout << "Keep all cards: " << keep << endl;
    cout << "Swap first card: " << first << endl;
    cout << "Swap second card: " << second << endl;
    cout << "Swap third card: " << third << endl;
    cout << "Swap first and second card: " << firstSecond << endl;
    cout << "Swap first and third card: " << firstThird << endl;
    cout << "Swap second and third card: " << secondThird << endl;
    cout << "Swap all cards: " << all << endl;
    cout << "Best move: ";
    */

    for (auto i : plays) {
        if (i > max) {
            max = i;
            best = count;
        }
        count++;
    }
    /*
    switch (best) {
    case(0):cout << "Keep all cards, " << keep << endl;
        break;
    case(1):cout << "Discard first, " << first << endl;
        break;
    case(2):cout << "Discard second, " << second << endl;
        break;
    case(3):cout << "Discard third, " << third << endl;
        break;
    case(4):cout << "Discard first and second, " << firstSecond << endl;
        break;
    case(5):cout << "Discard first and third, " << firstThird << endl;
        break;
    case(6):cout << "Discard second and third, " << secondThird << endl;
        break;
    case(7):cout << "Discard all, " << all << endl;
        break;
    }
    cout << endl;
    cout << endl;
    */
    return max;
}


void probabilityCalculator(Deck deck) {
    vector<Card> hand(3);
    float royalFlush(0.0);
    float threeAces(0.0);
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
                case(RF): royalFlush++;
                    break;
                case(AAA): threeAces++;
                    break;
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
    total = royalFlush + threeAces + straightFlush + threeOfKind + straight + flush + pair + high;
    cout << "Frequency of hands: " << endl;
    cout << "Royal Flush: " << royalFlush << endl;
    cout << "Three Aces: " << threeAces << endl;
    cout << "Straight Flush: " << straightFlush << endl;
    cout << "Three of a Kind: " << threeOfKind << endl;
    cout << "Straight: " << straight << endl;
    cout << "Flush: " << flush << endl;
    cout << "Pair: " << pair << endl;
    cout << "High Card: " << high << endl;
    cout << "Total Combinations: " << total << endl;
    cout << endl;

    //Probability
    royalFlush /= total;
    threeAces /= total;
    straightFlush /= total;
    threeOfKind /= total;
    straight /= total;
    flush /= total;
    pair /= total;
    high /= total;
    cout << "Probability of Hands: " << endl;
    cout << "Royal Flush: " << royalFlush << endl;
    cout << "Three Aces: " << threeAces << endl;
    cout << "Straight Flush: " << straightFlush << endl;
    cout << "Three of a Kind: " << threeOfKind << endl;
    cout << "Straight: " << straight << endl;
    cout << "Flush: " << flush << endl;
    cout << "Pair: " << pair << endl;
    cout << "High Card: " << high << endl;
    cout << endl;

    //Return
    royalFlush *= 250;
    threeAces *= 100;
    straightFlush *= 100;
    threeOfKind *= 30;
    straight *= 15;
    flush *= 5;
    pair *= 1;
    high *= 0;
    total = straightFlush + threeOfKind + straight + flush + pair + high;
    cout << "Expected return of game: " << endl;
    cout << "Royal Flush: " << royalFlush << endl;
    cout << "Three Aces: " << threeAces << endl;
    cout << "Straight Flush: " << straightFlush << endl;
    cout << "Three of a Kind: " << threeOfKind << endl;
    cout << "Straight: " << straight << endl;
    cout << "Flush: " << flush << endl;
    cout << "Pair: " << pair << endl;
    cout << "High Card: " << high << endl;
    cout << "Total: " << total << endl;
}

double expectedReturnPerfect(Deck deck) {
    double total(0.0);
    int count(0);
    vector<Card> hand(3);
    for (int i = 0; i < (deck.getDeck().size() - 2); i++) {
        hand[0] = deck.getCard(i);
        for (int j = i + 1; j < (deck.getDeck().size() - 1); j++) {
            hand[1] = deck.getCard(j);
            for (int k = j + 1; k < deck.getDeck().size(); k++) {
                count++;
                hand[2] = deck.getCard(k);
                total += perfectPlay(hand);
                cout << count << endl;
            }
        }
    }
    return total;
}

int main() {
  Deck deck;
  vector<Card> hand(3);

  cout << expectedReturnPerfect(deck);
      /*
  hand[0].suit = Spade;
  hand[0].value = 1;
  hand[1].suit = Spade;
  hand[1].value = 12;
  hand[2].suit = Spade;
  hand[2].value = 13;
  printCards(hand);
  perfectPlay(hand);

  hand[0].suit = Spade;
  hand[0].value = 1;
  hand[1].suit = Heart;
  hand[1].value = 1;
  hand[2].suit = Heart;
  hand[2].value = 2;
  printCards(hand);
  perfectPlay(hand);

  hand[0].suit = Club;
  hand[0].value = 1;
  hand[1].suit = Club;
  hand[1].value = 7;
  hand[2].suit = Heart;
  hand[2].value = 2;
  printCards(hand);
  perfectPlay(hand);

  hand[0].suit = Club;
  hand[0].value = 1;
  hand[1].suit = Club;
  hand[1].value = 12;
  hand[2].suit = Heart;
  hand[2].value = 5;
  printCards(hand);
  perfectPlay(hand);

  hand[0].suit = Club;
  hand[0].value = 4;
  hand[1].suit = Club;
  hand[1].value = 6;
  hand[2].suit = Heart;
  hand[2].value = 5;
  printCards(hand);
  perfectPlay(hand);

  hand[0].suit = Heart;
  hand[0].value = 4;
  hand[1].suit = Club;
  hand[1].value = 8;
  hand[2].suit = Heart;
  hand[2].value = 5;
  printCards(hand);
  perfectPlay(hand);

  hand[0].suit = Diamond;
  hand[0].value = 4;
  hand[1].suit = Club;
  hand[1].value = 11;
  hand[2].suit = Heart;
  hand[2].value = 12;
  printCards(hand);
  perfectPlay(hand);

  hand[0].suit = Diamond;
  hand[0].value = 12;
  hand[1].suit = Club;
  hand[1].value = 11;
  hand[2].suit = Heart;
  hand[2].value = 12;
  printCards(hand);
  perfectPlay(hand);

  hand[0].suit = Diamond;
  hand[0].value = 5;
  hand[1].suit = Club;
  hand[1].value = 5;
  hand[2].suit = Diamond;
  hand[2].value = 6;
  printCards(hand);
  perfectPlay(hand);

  hand[0].suit = Diamond;
  hand[0].value = 5;
  hand[1].suit = Diamond;
  hand[1].value = 3;
  hand[2].suit = Diamond;
  hand[2].value = 6;
  printCards(hand);
  perfectPlay(hand);
  */
}