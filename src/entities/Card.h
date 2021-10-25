#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"

struct Card {

    private:

        uint8_t cardIndex;

    public: // Properties

        uint8_t getCardIndex()              { return this->cardIndex; }
       
        void setCardIndex(uint8_t val)      { this->cardIndex = val; }

    public: // Methods 

        void init(uint8_t cardIndex) {

            this->cardIndex = cardIndex;

        }

        void init(CardSuit suit, uint8_t cardNumber) {

            this->cardIndex = (static_cast<uint8_t>(suit) * 13) + cardNumber;

        }

        CardSuit getSuit(CardSuit trumps) {

            if (trumps != CardSuit::None) {
                
                if (this->isTrump(trumps)) {
                    
                    return trumps;

                }
                else {

                    return static_cast<CardSuit>(this->cardIndex / 13);

                }

                
            }
            else {

                return static_cast<CardSuit>(this->cardIndex / 13);

            }
        
        }

        uint8_t getNumber() {

            if (this->cardIndex == Cards::NoCard) return Cards::NoCard;
            
            return this->cardIndex % 13;
        
        }


        uint8_t getCardValue(CardSuit trumps) {

            CardSuit suit = static_cast<CardSuit>(this->cardIndex / 13);;

            if (this->getSuit(CardSuit::None) == trumps) {

                if (this->getNumber() == Cards::Jack) {
                    return Cards::RightBower;
                }
                else {

                    return Cards::TrumpsStart + this->getNumber();

                }

            }
            else if (suit == CardSuit::Clubs && trumps == CardSuit::Spades && this->getNumber() == Cards::Jack) {
                return Cards::LeftBower;
            }
            else if (suit == CardSuit::Spades && trumps == CardSuit::Clubs && this->getNumber() == Cards::Jack) {
                return Cards::LeftBower;
            }
            else if (suit == CardSuit::Hearts && trumps == CardSuit::Diamonds && this->getNumber() == Cards::Jack) {
                return Cards::LeftBower;
            }
            else if (suit == CardSuit::Diamonds && trumps == CardSuit::Hearts && this->getNumber() == Cards::Jack) {
                return Cards::LeftBower;
            }
            else {

                return this->cardIndex;

            }
        
        }


        void print() {

            #ifdef DEBUG

                if (this->cardIndex == Cards::NoCard) {
                    
                    printf("-- ");

                }
                else {
                        
                    switch (this->cardIndex % 13) {

                        case 0 ... 7:    
                            printf("%i", (this->cardIndex % 13) + 2);
                            break;

                        case 8:    
                            printf("T");
                            break;

                        case 9:    
                            printf("J");
                            break;

                        case 10:    
                            printf("Q");
                            break;

                        case 11:    
                            printf("K");
                            break;

                        case 12:    
                            printf("A");
                            break;
                    
                    }

                    switch (this->cardIndex / 13) {

                        case 0:    
                            printf("S");
                            break;

                        case 1:    
                            printf("C");
                            break;

                        case 2:    
                            printf("D");
                            break;

                        case 3:    
                            printf("H");
                            break;
                    
                    }
                    
                    printf(" ");

                }
                
            #endif

        }

        char getSuitAsChar() {

            if (this->cardIndex == Cards::NoCard) {
                
                return '-';

            }
            else {
             
                switch (this->cardIndex / 13) {

                    case 0:    
                        return 'S';

                    case 1:    
                        return 'C';

                    case 2:    
                        return 'D';

                    case 3:    
                        return 'H';
                
                }

            }

            return '-';

        }

        char getNumberAsChar() {

            if (this->cardIndex == Cards::NoCard) {
                
                return ' ';

            }
            else {
                    
                switch (this->cardIndex % 13) {

                    case 0 ... 7:    
                        return 50 + (this->cardIndex % 13);

                    case 8:    
                        return 'T';

                    case 9:    
                        return 'J';

                    case 10:    
                        return 'Q';

                    case 11:    
                        return 'K';

                    case 12:    
                        return 'A';
                
                }

            }

            return '-';

        }


        bool isTrump(CardSuit trumps) {

            if (this->cardIndex == Cards::NoCard) return false;

            CardSuit suit = static_cast<CardSuit>(this->cardIndex / 13);

            if (suit == trumps) {

                return true;

            }
            else if (this->getNumber() == Cards::Jack && suit == CardSuit::Spades && trumps == CardSuit::Clubs) {

                return true;

            }
            else if (this->getNumber() == Cards::Jack && suit == CardSuit::Clubs && trumps == CardSuit::Spades) {

                return true;
                
            }
            else if (this->getNumber() == Cards::Jack && suit == CardSuit::Hearts && trumps == CardSuit::Diamonds) {

                return true;

            }
            else if (this->getNumber() == Cards::Jack && suit == CardSuit::Diamonds && trumps == CardSuit::Hearts) {

                return true;

            }
        
            return false;
        
        }

};