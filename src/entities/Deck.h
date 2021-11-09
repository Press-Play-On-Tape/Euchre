#pragma once

#include "Card.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"

struct Deck {

    private:

        Card deck[24];
        bool seen[4][5];
        int8_t index = 51;


    public:

        int8_t getIndex()       { return this->index; }

        void init() {

            for (uint8_t suit = 0; suit < 4; suit++) {

                for (uint8_t cardIdx = 0; cardIdx < 5; cardIdx++) {

                    this->seen[suit][cardIdx] = false;

                }

            }

            uint8_t counter = 0;

            for (uint8_t suit = 0; suit < 4; suit++) {

                for (uint8_t cardIdx = Cards::Nine; cardIdx <= Cards::Ace; cardIdx++) {

                    this->deck[counter].init((suit * 13) + cardIdx);
                    counter++;

                }

            }

            print();

            this->shuffleCards();
            this->index = 23;

        }

        void shuffleCards() {

            for (uint8_t i = 0; i < 120; i++) {

                uint8_t rnd1 = random(0, 24);
                uint8_t rnd2 = random(0, 24);

                uint8_t tmp = this->deck[rnd1].getCardIndex();
                this->deck[rnd1].init(this->deck[rnd2].getCardIndex());
                this->deck[rnd2].init(tmp); 

            }

        } 

        Card dealCard() {

            this->index--;

            if (this->index >= 0) { return this->deck[this->index]; }
            return this->deck[0]; 
            
        }


        Card getCard(uint8_t index) {

            return this->deck[this->index]; 
            
        }


        void print() {

            #ifdef DEBUG
            printf("Deck : ");
            
            for (uint8_t i = 0; i <= this->getIndex(); i++) {
                if (i < 10) printf("0");
                printf("%i", i);
                printf(" ");
            }

            printf("\n       ");

            for (uint8_t i = 0; i <= this->getIndex(); i++) {

                this->deck[i].print();

            }
            
            printf("\n");
            #endif

        }


};