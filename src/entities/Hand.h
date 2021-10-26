#pragma once

#include "Pokitto.h"
#include "Card.h"
#include "GameStatus.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"

struct Hand {

    private:

        Card hand[6];
        Card backup[5];
        CallStatus callStatus;
        uint8_t callStatus_DisplayCounter;
        uint8_t handNumber = 0;
        int8_t cardsInHand = 0;

    public:
    
        uint8_t getCardsInHand()                { return this->cardsInHand; }
        CallStatus getCallStatus()              { return this->callStatus; }
        bool showCallStatus()                   { return this->callStatus_DisplayCounter > 0; }

        void setCallStatus(CallStatus val)      { this->callStatus = val; this->callStatus_DisplayCounter = Constants::BidDialogueDelay; }


    private:

        void backupHand() {

            for (uint8_t i = 0; i < 5; i++) {

                this->backup[i].init(this->hand[i].getCardIndex());

            }

        }

        void restoreHand() {

            for (uint8_t i = 0; i < 5; i++) {

                this->hand[i].init(this->backup[i].getCardIndex());

            }

        }

        void swap(uint8_t x, uint8_t y) {
        
            uint8_t tmp = this->hand[x].getCardIndex();
            this->hand[x].init(this->hand[y].getCardIndex());
            this->hand[y].init(tmp); ;

        }
        
        void sortHand(int n, bool scoringHand, CardSuit suit, bool trumpsOnLeft = true) {

            uint8_t i, j;

            for (uint8_t i = 0; i < n - 1; i++) {
            
                for (j = 0; j < n-i-1; j++) {

                    if (scoringHand) {

                        if (trumpsOnLeft) {
                            if (this->hand[j].getCardValue(suit) < this->hand[j+1].getCardValue(suit)) {
                                this->swap(j, j + 1);
                            }
                        }
                        else {
                            if (this->hand[j].getCardValue(suit) > this->hand[j+1].getCardValue(suit)) {
                                this->swap(j, j + 1);
                            }
                        }

                    }
                    else {

                        if (this->hand[j].getCardIndex() > this->hand[j+1].getCardIndex()) {
                            this->swap(j, j + 1);
                        }

                    }

                }

            }

        }


    public:

        void init(uint8_t handNumber) {

            this->handNumber = handNumber;

            for (uint8_t i = 0; i < 5; i++) {

                this->hand[i].init(Cards::NoCard);

            }

            this->cardsInHand = 0;
            this->callStatus = CallStatus::None;

        }

        void update() {

            if (this->callStatus_DisplayCounter > 0) this->callStatus_DisplayCounter--;

        }

        bool isBidWinner() {

            return (this->callStatus == CallStatus::FirstRound ||
                    this->callStatus == CallStatus::SecondRound);

        }

        void shuffleHand() {

            this->sortHand(this->cardsInHand, false, CardSuit::None);

        } 

        void shuffleHandTrumps(CardSuit trumps) {

            this->sortHand(this->cardsInHand, true, trumps, false);

        } 

        void selectBestFive(CardSuit trumps, Card dealtCard) {

            this->addCard(dealtCard);
            this->sortHand(this->cardsInHand, true, trumps);
            this->removeCard(5);

        } 

        void addCard(Card &card) {

            this->hand[this->cardsInHand].init(card.getCardIndex());
            this->cardsInHand++;

        }

        void removeCard(uint8_t index) {
//printf("remove card %i\n", index);//SJH overflow
            for (uint8_t i = index; i < this->cardsInHand - 1; i++) {
//printf(">> move card %i < %i\n", i, i + 1);//SJH overflow

                this->hand[i].init(this->hand[i + 1].getCardIndex());

            }

//printf(">> init %i \n", this->cardsInHand - 1);//SJH overflow
            this->hand[this->cardsInHand - 1].init(Cards::NoCard);
//printf(">> init done\n");//SJH overflow
            this->cardsInHand--;
//printf(">> cardsInHand %i \n", this->cardsInHand);//SJH overflow

        }

        Card& getCard(uint8_t index) {

            return this->hand[index];

        }

        void print(bool lineEnd = true) {

            printf("Hand %i: ", (uint16_t)this->handNumber);

            for (uint8_t i = 0; i < this->cardsInHand; i++) {

                this->hand[i].print();

            }

            if (lineEnd) printf("\n");

        }
        
        uint16_t bid(CardSuit suit) {

            Card card;
            card.init(Cards::NoCard);

            return bid(suit, card, false);

        }

        uint16_t bid(CardSuit suit, Card dealerCard, uint8_t isDealer) {

            this->backupHand();

            if (isDealer) {
                this->hand[5].init(dealerCard.getCardIndex());
                this->sortHand(this->cardsInHand + 1, true, suit);
            }
            else {
                this->sortHand(this->cardsInHand, true, suit);
            }

            /*HAND*/ this->print(false);
            /*HAND*/ if (isDealer) printf(" (D)");
            /*HAND*/ if (!isDealer) printf(" (d)");
            /*HAND*/ printf(" >> ");

            uint8_t handScore = 0;
            bool hasRightBower = false;
            bool hasLeftBower = false;

            for (uint8_t i = 0; i < this->cardsInHand; i++) {

                bool matchingSuit = 0;
                Card &card = this->hand[i];
                card.print();

                if (card.getSuit(dealerCard.getSuit(CardSuit::None)) == suit) { matchingSuit = true; }

                switch (card.getCardValue(suit)) {

                    case Cards::RightBower:
                        handScore = handScore + 100;
                        hasRightBower = true;
                        /*HAND*/ printf("100 Right Bower, ");
                        break;

                    case Cards::LeftBower:
                        handScore = handScore + (hasRightBower ? 100 : 80);
                        /*HAND*/ printf(hasRightBower ? "100 Left Bower (inc RB), " : "80 Left Bower only, ");
                        hasRightBower = true;
                        break;

                    default:

                        switch (card.getNumber()) {
                                
                            case Cards::Ace:    

                                if (matchingSuit) {

                                    if (hasRightBower && hasLeftBower) {
                                        /*HAND*/ printf("100 Trumps (inc RB, LB), ");
                                        handScore = handScore + 100;
                                    }
                                    else if (hasRightBower && !hasLeftBower) {
                                        /*HAND*/ printf("70 Trumps (inc RB), ");
                                        handScore = handScore + 70;
                                    }
                                    else if (!hasRightBower && hasLeftBower) {
                                        /*HAND*/ printf("60 Trumps (inc LB), ");
                                        handScore = handScore + 60;
                                    }

                                }
                                else {

                                    /*HAND*/ printf("40 Non-Trump, ");
                                    handScore = handScore + 40;

                                }

                                break;

                            case Cards::King:

                                if (matchingSuit) {

                                    switch (i) {

                                        case 0:

                                            /*HAND*/ printf("20 Trump, ");
                                            handScore = handScore + 20;
                                            break;

                                        case 1:
                                            /*HAND*/ printf("*K %i %i*", i, this->hand[i - 1].getCardValue(dealerCard.getSuit(CardSuit::None)));
                                            switch (this->hand[i - 1].getCardValue(dealerCard.getSuit(CardSuit::None))) {
                                                
                                                case Cards::RightBower:
                                                    /*HAND*/ printf("30 Trump (inc RB), ");
                                                    handScore = handScore + 30;
                                                    break;
                                                
                                                case Cards::LeftBower:
                                                    /*HAND*/ printf("25 Trump (inc LB), ");
                                                    handScore = handScore + 25;
                                                    break;
                                                
                                                case Cards::Ace:
                                                    /*HAND*/ printf("20 Trump (inc Ace), ");
                                                    handScore = handScore + 20;
                                                    break;

                                            }

                                            break;

                                        case 2:

                                            switch (this->hand[i - 1].getCardValue(dealerCard.getSuit(CardSuit::None))) {
                                                
                                                case Cards::LeftBower:
                                                    /*HAND*/ printf("40 Trump (inc RB, LB), ");
                                                    handScore = handScore + 40;
                                                    break;
                                                
                                                case Cards::Ace:
                                                    /*HAND*/ printf("30 Trump (inc Ace), ");
                                                    handScore = handScore + 30;
                                                    break;

                                            }

                                            break;

                                        case 3:
                                        
                                            /*HAND*/ printf("100 Trumps (inc RB, LB, A), ");
                                            handScore = handScore + 100; 
                                            break;


                                    }

                                }
                                else {

                                    switch (i) {

                                        case 0:

                                            /*HAND*/ printf("20 Non-Trumps (no-Ace), ");
                                            handScore = handScore + 20;
                                            break;

                                        default:

                                            if (this->hand[i - 1].getSuit(dealerCard.getSuit(CardSuit::None)) == card.getSuit(dealerCard.getSuit(CardSuit::None))) {

                                                /*HAND*/ printf("30 Non-Trumps (inc Ace), ");
                                                handScore = handScore + 30;

                                            }
                                            else {

                                                /*HAND*/ printf("20 Non-Trumps (no-Ace), ");
                                                handScore = handScore + 20;

                                            }

                                    }

                                }

                                break;

                            case Cards::Queen:

                                if (matchingSuit) {

                                    switch (i) {

                                        case 0:
                                            /*HAND*/ printf("10 Trumps, ");
                                            handScore = handScore + 10; 
                                            break;

                                        case 1:
                                            /*HAND*/ printf("15 Trumps, ");
                                            handScore = handScore + 15; 
                                            break;

                                        case 2:
                                            /*HAND*/ printf("30 Trumps, ");
                                            handScore = handScore + 30; 
                                            break;

                                        case 3:
                                            /*HAND*/ printf("45 Trumps, ");
                                            handScore = handScore + 45; 
                                            break;

                                        case 4:
                                            /*HAND*/ printf("100 Trumps (inc RB, LB, A), ");
                                            handScore = handScore + 100; 
                                            break;

                                    }

                                }
                                break;

                            case Cards::Two ... Cards::Six:

                                if (matchingSuit) {

                                    handScore = handScore + 5;
                                    /*HAND*/ printf("5 Trump, ");
                                
                                }

                                break;

                            case Cards::Seven ... Cards::Ten:

                                if (matchingSuit) {

                                    handScore = handScore + 10;
                                    /*HAND*/ printf("10 Trump, ");
                                
                                }

                                break;

                        }

                        break;

                }

            }

            this->restoreHand();
            /*HAND*/ printf(" = %i\n", handScore);
            return handScore;

        }

        uint8_t leadACard(CardSuit trumps, GameStatus &gameStatus, bool isBidWinner, bool isBidWinnerAlt) {

            uint8_t maybeScore = 0;
            uint8_t maybeIndex = Cards::NoCard;

            if (isBidWinner || isBidWinnerAlt) {


                // If we have a Right Bower then lead it ..

                for (uint8_t i = 0; i < this->cardsInHand; i++) {

                    if (this->hand[i].getCardValue(trumps) == Cards::RightBower) {

//LEAD printf("leadACard 1 - bid winner, lead a right Bower\n");
                        return i;

                    }

                }


                // If we have a Left Bower and the Right bower has been played then lead it ..

                Card card;
                card.init(trumps, Cards::Jack);

                if (gameStatus.getHasBeenPlayed(card)) {
                        
                    for (uint8_t i = 0; i < this->cardsInHand; i++) {

                        if (this->hand[i].getCardValue(trumps) == Cards::RightBower) {

//LEAD printf("leadACard 2 - bid winner, lead a left Bower\n");
                            return i;

                        }

                    }

                }


                // Lead an off-suit Ace?

                for (uint8_t i = 0; i < this->cardsInHand; i++) {

                    if (this->hand[i].getSuit(trumps) != trumps && this->hand[i].getNumber() == Cards::Ace) {

                        if (this->evaluatePlay(gameStatus, trumps, i, maybeScore, maybeIndex, 10, 25) != Cards::NoCard) {

//LEAD printf("leadACard 3 - bid winner, off-suit A\n");
                            return i;

                        }

                    }

                }


                // Lead a small trump if partner has any ..

                if (gameStatus.getHasSuit((this->handNumber + 2) % 4, trumps) != HasSuit::False) {
                    
                    for (uint8_t cardValue = 9; cardValue < Cards::Ten; cardValue++) {

                        for (uint8_t i = 0; i < this->cardsInHand; i++) {

                            if (this->hand[i].getSuit(trumps) == trumps && this->hand[i].getNumber() == cardValue) {

//LEAD printf("leadACard 3 - bid winner, off-suit K\n");
                                return i;

                            }

                        }

                    }

                }


                // Lead a small non-trump if partner has any ..
                    
                for (uint8_t cardValue = Cards::Nine; cardValue < Cards::Ten; cardValue++) {

                    for (uint8_t i = 0; i < this->cardsInHand; i++) {

                        if (this->hand[i].getSuit(trumps) != trumps && this->hand[i].getNumber() == cardValue) {

                            if (gameStatus.getHasSuit((this->handNumber + 2) % 4, this->hand[i].getSuit(trumps)) != HasSuit::False) {

//LEAD printf("leadACard 4 - bid winner, small non-trump\n");
                                return i;

                            }

                        }

                    }

                }


                // Random card?

//LEAD printf("leadACard 5 - bid winner, random\n");
                return random(0, this->cardsInHand);

            }
            else {


                // Lead an off-suit Ace?

                for (uint8_t i = 0; i < this->cardsInHand; i++) {

                    if (this->hand[i].getSuit(trumps) != trumps && this->hand[i].getNumber() == Cards::Ace) {

                        if (this->evaluatePlay(gameStatus, trumps, i, maybeScore, maybeIndex, 10, 25) != Cards::NoCard) {

//LEAD printf("leadACard 6 - non-bid winner, off suit A\n");
                            return i;

                        }

                    }

                }


                // Lead an off-suit King? But only if the Ace has been played or your partner may have it ..

                for (uint8_t i = 0; i < this->cardsInHand; i++) {

                    if (this->hand[i].getSuit(trumps) != trumps && this->hand[i].getNumber() == Cards::King) {

                        Card card;
                        card.init(this->hand[i].getSuit(trumps), Cards::Ace);

                        if (gameStatus.getHasBeenPlayed(card) || gameStatus.getHasSuit((this->handNumber + 2) % 4, this->hand[i].getSuit(trumps)) != HasSuit::False) {

                            if (this->evaluatePlay(gameStatus, trumps, i, maybeScore, maybeIndex, 8, 15) != Cards::NoCard) {

//LEAD printf("leadACard 6 - non-bid winner, off suit K\n");
                                return i;

                            }

                        }

                    }

                }


                // Did we find a playable card?

                if (maybeScore > 0) {

//LEAD printf("leadACard 7 - non-bid winner, off suit K 2\n");
                    return maybeIndex;

                }


                // Otherwise do we have a small card ?

                for (uint8_t j = Cards::Nine; j <= Cards::Queen; j++) {
//LEAD printf("leadACard 8 - test card %i\n", j);

                    for (uint8_t i = 0; i < this->cardsInHand; i++) {
//LEAD printf("leadACard 8 - test suit %i\n", i);

                        if (this->hand[i].getSuit(trumps) != trumps && this->hand[i].getNumber() == j) {
//LEAD printf("leadACard 8 - non trumps!! \n");

                            // Does our partner have any of this suit ?

                            if (gameStatus.getHasSuit((this->handNumber + 2) % 4, this->hand[i].getSuit(trumps)) != HasSuit::False) {
                                  
                                if (this->evaluatePlay(gameStatus, trumps, i, maybeScore, maybeIndex, 4, 10) != Cards::NoCard) {

//LEAD printf("leadACard 8 - non-bid winner, small non-trump\n");
                                    return i;

                                }

                            } 
                            else {
//LEAD printf("leadACard 8 - other play has none of these. \n");
//SJH Need to add some more logic here
                            }

                        }

                    }


                    // Did we find a playable card?

                    if (maybeScore > 0) {
//LEAD printf("leadACard 9 - non-bid winner, small non-trump 2\n");

                        return maybeIndex;

                    }

                }


                // Nothing? A random card ..
//LEAD printf("leadACard 10 - random\n");

                return random(0, this->cardsInHand);

            }

        }


        uint8_t followACard(GameStatus &gameStatus) {

            uint8_t maybeScore = 0;
            uint8_t maybeIndex = Cards::NoCard;
            uint8_t cardIndex = Cards::NoCard;
            uint8_t lastPlayerIdx = gameStatus.getLastPlayerIdx();

            CardSuit suitLed = gameStatus.getSuitLed();

            if (gameStatus.isPartnerWinning((this->handNumber + 2) % 4, suitLed)) {

                if (this->hasSuit(suitLed, gameStatus.getTrumps())) {
//LEAD printf("followACard 1 - partner wining. Play smallest of suit led\n");
                    cardIndex = this->throwSmallestOfSuit(suitLed, gameStatus.getTrumps());
                    if (cardIndex != Cards::NoCard) return cardIndex;

                }
                else {
                        
                    if (lastPlayerIdx == this->handNumber) {
//LEAD printf("followACard 2 - partner winning but no led suit.  Play smallest non-trump followed by smallest non-trump\n");
                        
                        cardIndex = this->throwSmallestNonTrump(gameStatus.getTrumps());
                        if (cardIndex != Cards::NoCard) return cardIndex;
                        cardIndex = this->throwSmallestTrump(gameStatus.getTrumps());
                        if (cardIndex != Cards::NoCard) return cardIndex;

                    }
                    else {

                        if (gameStatus.getHasSuit(lastPlayerIdx, suitLed) == HasSuit::False && gameStatus.getHasSuit(lastPlayerIdx, gameStatus.getTrumps()) != HasSuit::False) {
//LEAD printf("followACard 3 - partner winning but no led suit and not last player.  Throw largest trump followed by smallest non-trump. \n");

                            cardIndex = this->throwLargestTrump(gameStatus.getTrumps());
                            if (cardIndex != Cards::NoCard) return cardIndex;
                            cardIndex = this->throwSmallestNonTrump(gameStatus.getTrumps());
                            if (cardIndex != Cards::NoCard) return cardIndex;
                           
                        }
                        else {
//LEAD printf("followACard 4 - partner winning but no led suit and not last player.  Throw smallest trump followed by smallest non-trump\n");

                            cardIndex = this->throwSmallestTrump(gameStatus.getTrumps());
                            if (cardIndex != Cards::NoCard) return cardIndex;
                            cardIndex = this->throwSmallestNonTrump(gameStatus.getTrumps());
                            if (cardIndex != Cards::NoCard) return cardIndex;

                        }

                    }

                }

            }
            else {

                if (this->hasSuit(suitLed, gameStatus.getTrumps())) {

                    uint8_t trumpToBeat = gameStatus.getHighestTrumpInHand();
                    uint8_t suitLedToBeat = gameStatus.getHighestOfSuitInHand(suitLed);

                    if (suitLed != gameStatus.getTrumps()) {

                        if (trumpToBeat != Cards::NoCard) {
//LEAD printf("followACard 5a - have suit, non-trumps but hand trumped. Play the smallest of the led suit\n");
                         
                            cardIndex = this->throwSmallestOfSuit(suitLed, gameStatus.getTrumps());
                            if (cardIndex != Cards::NoCard) return cardIndex;

                        }
                        else {
                            
                            if (gameStatus.isPlayerWinning((this->handNumber + 2) % 4)) {

//LEAD printf("followACard 5b1 - partner Winning, have suit, non-trumps and hand not trumped. Play the lowestof the suit led\n");

                                cardIndex = this->throwSmallestOfSuit(suitLed, gameStatus.getTrumps());
                                if (cardIndex != Cards::NoCard) return cardIndex;

                            }
                            else {

//LEAD printf("followACard 5b2 - partner not Winning, have suit, non-trumps and hand not trumped. Play the next biggest of the led suit followed by small of the suit\n");

                                cardIndex = this->throwSmallestOfSuit(suitLed, gameStatus.getTrumps(), suitLedToBeat);
                                if (cardIndex != Cards::NoCard) return cardIndex;
                                cardIndex = this->throwSmallestOfSuit(suitLed, gameStatus.getTrumps());
                                if (cardIndex != Cards::NoCard) return cardIndex;

                            }

                        }

                    }
                    else {

                        if (this->haveHigherTrump(gameStatus.getTrumps(), trumpToBeat)) {
//LEAD printf("followACard 5c - have a larger trump. Play the next biggest trump\n");

                            cardIndex = this->throwSmallestOfSuit(suitLed, gameStatus.getTrumps(), trumpToBeat);
                            if (cardIndex != Cards::NoCard) return cardIndex;

                        }

//LEAD printf("followACard 5d - do not have a larger trump. Play the smallest trump\n");
                        cardIndex = this->throwSmallestOfSuit(suitLed, gameStatus.getTrumps());
                        if (cardIndex != Cards::NoCard) return cardIndex;

                    }

                }
                else {

                    if (lastPlayerIdx == this->handNumber) {
//LEAD printf("followACard 6 - last player, none of the led suit.  Try a small trump followed by small non-trumps\n");

                        cardIndex = this->throwSmallestTrump(gameStatus.getTrumps());
                        if (cardIndex != Cards::NoCard) return cardIndex;
                        cardIndex = this->throwSmallestNonTrump(gameStatus.getTrumps());
                        if (cardIndex != Cards::NoCard) return cardIndex;

                    }
                    else {
                            
                        if (gameStatus.getHasSuit(lastPlayerIdx, suitLed) == HasSuit::False && gameStatus.getHasSuit(lastPlayerIdx, gameStatus.getTrumps()) != HasSuit::False) {
//LEAD printf("followACard 7 - not last player, none of the led suit. Play large trump followed by small non-trump\n");

                            cardIndex = this->throwLargestTrump(gameStatus.getTrumps());
                            if (cardIndex != Cards::NoCard) return cardIndex;
                            cardIndex = this->throwSmallestNonTrump(gameStatus.getTrumps());
                            if (cardIndex != Cards::NoCard) return cardIndex;
                            
                        }
                        else {
                            
                            uint8_t highestTrump = gameStatus.getHighestTrumpInHand();

                            if (highestTrump != Cards::NoCard) {
//LEAD printf("followACard 8 - not last player, none of the led suit. Hand already trumped / is trumps. Play small trump nigger than %i followed by small non-trump\n", highestTrump);

                                cardIndex = this->throwSmallestTrump(gameStatus.getTrumps(), highestTrump);
                                if (cardIndex != Cards::NoCard) return cardIndex;

                            }
                            else {
//LEAD printf("followACard 9 - not last player, none of the led suit. Hand not already trumped / is trumps. Play small trump followed by small non-trump\n");

                                cardIndex = this->throwSmallestTrump(gameStatus.getTrumps());
                                if (cardIndex != Cards::NoCard) return cardIndex;

                            }

                            cardIndex = this->throwSmallestNonTrump(gameStatus.getTrumps());
                            if (cardIndex != Cards::NoCard) return cardIndex;

                        }

                    }

                }

            }

            return Cards::NoCard;

        }

        uint8_t throwLargestTrump(CardSuit trumps) {

            return this->throwLargestOfSuit(trumps, trumps);

        }

        uint8_t throwLargestOfSuit(CardSuit cardSuit, CardSuit trumps) {

            uint8_t cardVal = 0;
            uint8_t cardIdx = Cards::NoCard;

            for (uint8_t i = 0; i < this->cardsInHand; i++) {

                if (cardSuit == trumps) {

                    if (this->hand[i].isTrump(trumps) && cardVal < this->hand[i].getCardValue(trumps)) {

                        cardVal = this->hand[i].getCardValue(trumps);
                        cardIdx = i;

                    }

                }
                else {
                    
                    if (!this->hand[i].isTrump(trumps) && this->hand[i].getSuit(trumps) == cardSuit && cardVal < this->hand[i].getCardValue(trumps)) {

                        cardVal = this->hand[i].getCardValue(trumps);
                        cardIdx = i;

                    }

                }

            }

            return cardIdx;

        }

        uint8_t throwSmallestNonTrump(CardSuit trumps) {

            uint8_t smallestIndex[4] = { Cards::NoCard, Cards::NoCard, Cards::NoCard, Cards::NoCard };

            for (uint8_t suit = 0; suit < 4; suit++) {

                if (static_cast<CardSuit>(suit) != trumps) {

                    smallestIndex[suit] = this->getSmallestOfNonTrump(static_cast<CardSuit>(suit), trumps);

                }

            }

            uint8_t smallesIndexOverall = smallestIndex[0];
            if (smallestIndex[1] < smallesIndexOverall) smallesIndexOverall = smallestIndex[1];
            if (smallestIndex[2] < smallesIndexOverall) smallesIndexOverall = smallestIndex[2];
            if (smallestIndex[3] < smallesIndexOverall) smallesIndexOverall = smallestIndex[3];

            return smallesIndexOverall;

        }

        uint8_t throwSmallestTrump(CardSuit trumps, uint8_t largerThan = Cards::Two) {

            return this->throwSmallestOfSuit(trumps, trumps, largerThan);

        }


        uint8_t getSmallestOfNonTrump(CardSuit cardSuit, CardSuit trumps, uint8_t largerThan = Cards::Two) {

// printf("smallest of suit %i %i > %i\n", (uint16_t)cardSuit, (uint16_t)trumps, (uint16_t)largerThan);
            uint8_t cardVal = Cards::NoCard;
            uint8_t cardIdx = Cards::NoCard;

            for (uint8_t i = 0; i < this->cardsInHand; i++) {

                if (!this->hand[i].isTrump(trumps) && this->hand[i].getSuit(trumps) == cardSuit && cardVal > this->hand[i].getNumber() && (largerThan > Cards::Two ? this->hand[i].getNumber() > largerThan : true)) {
// printf(">  smallest of suit .. card ");
// this->hand[i].print();                    
// if (this->hand[i].isTrump(trumps)) printf("is a trump\n");
// if (!this->hand[i].isTrump(trumps)) printf("is not a trump\n");
// printf(">  LargerThan %i, this->hand[i].getNumber() % i\n", largerThan, this->hand[i].getNumber());
                    cardVal = this->hand[i].getNumber();
                    cardIdx = i;

                }

            }

            return cardIdx;

        }

        uint8_t throwSmallestOfSuit(CardSuit cardSuit, CardSuit trumps, uint8_t largerThan = Cards::Two) {
// printf("smallest of suit %i %i > %i\n", (uint16_t)cardSuit, (uint16_t)trumps, (uint16_t)largerThan);
            uint8_t cardVal = Cards::NoCard;
            uint8_t cardIdx = Cards::NoCard;

            for (uint8_t i = 0; i < this->cardsInHand; i++) {

//                if (cardSuit == trumps && this->hand[i].isTrump()) {
                if (cardSuit == trumps) {

                    if (this->hand[i].isTrump(trumps) && cardVal > this->hand[i].getCardValue(trumps) && (largerThan > Cards::Two ? this->hand[i].getNumber() > largerThan : true)) {
// printf(">  smallest of suit .. card ");
// this->hand[i].print();
// if (this->hand[i].isTrump(trumps)) printf("is a trump\n");
// if (!this->hand[i].isTrump(trumps)) printf("is not a trump\n");

                        cardVal = this->hand[i].getCardValue(trumps);
                        cardIdx = i;

                    }

                }
                else {

                    if (!this->hand[i].isTrump(trumps) && this->hand[i].getSuit(trumps) == cardSuit && cardVal > this->hand[i].getCardValue(trumps) && (largerThan > Cards::Two ? this->hand[i].getNumber() > largerThan : true)) {
// printf(">  smallest of suit .. card ");
// this->hand[i].print();                    
// if (this->hand[i].isTrump(trumps)) printf("is a trump\n");
// if (!this->hand[i].isTrump(trumps)) printf("is not a trump\n");
// printf(">  LargerThan %i, this->hand[i].getNumber() % i\n", largerThan, this->hand[i].getCardValue(trumps));
                        cardVal = this->hand[i].getCardValue(trumps);
                        cardIdx = i;

                    }

                }

            }

            return cardIdx;

        }

        uint8_t hasSuit(CardSuit cardSuit, CardSuit trumps) {

            for (uint8_t i = 0; i < this->cardsInHand; i++) {

                if (this->hand[i].getSuit(trumps) == cardSuit) {

                    return true;

                }

            }

            return false;

        }

        uint8_t evaluatePlay(GameStatus &gameStatus, CardSuit trumps, uint8_t cardIndex, uint8_t &maybeScore, uint8_t &maybeIndex, uint8_t factor1, uint8_t factor2) {

            // Play this card if Opponent 1 & 3 may have some of these cards .. or .. has none of these and no trumps.

            if (((gameStatus.getHasSuit((this->handNumber + 1) % 4, this->hand[cardIndex].getSuit(trumps)) != HasSuit::False) ||
                 (gameStatus.getHasSuit((this->handNumber + 1) % 4, this->hand[cardIndex].getSuit(trumps)) == HasSuit::False && 
                  gameStatus.getHasSuit((this->handNumber + 1) % 4, trumps) == HasSuit::False)) &&                
                ((gameStatus.getHasSuit((this->handNumber + 3) % 4, this->hand[cardIndex].getSuit(trumps)) != HasSuit::False) ||
                 (gameStatus.getHasSuit((this->handNumber + 3) % 4, this->hand[cardIndex].getSuit(trumps)) == HasSuit::False && 
                  gameStatus.getHasSuit((this->handNumber + 3) % 4, trumps) == HasSuit::False))) {

                return cardIndex;

            }
            else {

                // If either opponent does not have this suit and may have a trump, then we need to think about the number of tricks played ..

                if ((gameStatus.getHasSuit((this->handNumber + 1) % 4, this->hand[cardIndex].getSuit(trumps)) == HasSuit::False &&                
                     gameStatus.getHasSuit((this->handNumber + 1) % 4, trumps) != HasSuit::False) ||
                    (gameStatus.getHasSuit((this->handNumber + 3) % 4, this->hand[cardIndex].getSuit(trumps)) == HasSuit::False &&                
                     gameStatus.getHasSuit((this->handNumber + 1) % 4, trumps) != HasSuit::False)) {

                    if (maybeScore < (5 - this->cardsInHand)) {

                        maybeScore = (5 - this->cardsInHand) * factor1;
                        maybeIndex = cardIndex;

                    }

                }

                // If either opponent may have this suit and does have a trump, then this is a 15 lead ..

                if ((gameStatus.getHasSuit((this->handNumber + 1) % 4, this->hand[cardIndex].getSuit(trumps)) == HasSuit::False &&                
                     gameStatus.getHasSuit((this->handNumber + 1) % 4, trumps) == HasSuit::True) ||
                    (gameStatus.getHasSuit((this->handNumber + 3) % 4, this->hand[cardIndex].getSuit(trumps)) == HasSuit::False &&                
                     gameStatus.getHasSuit((this->handNumber + 1) % 4, trumps) == HasSuit::True)) {

                    if (maybeScore < factor2) {

                        maybeScore = factor2;
                        maybeIndex = cardIndex;

                    }

                }
                
            }

            return Cards::NoCard;

        }

        bool haveHigherTrump(CardSuit trumps, uint8_t cardToBeat) {

            for (uint8_t i = 0; i < this->cardsInHand; i++) {

                if (this->hand[i].isTrump(trumps) && this->hand[i].getCardValue(trumps) > cardToBeat) {

                    return true;

                }

            }

            return false;

        }


};
