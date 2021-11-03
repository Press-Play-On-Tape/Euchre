#include "Euchre.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::swap_Init() {

    this->gameState = GameState::Swap;

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::swap() {

    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = this->savedState;

    }         


    if (this->gameStatus.getPlayerView() != 0) {

        PD::setColor(3);
        PD::fillRect(0, 0, 110, 176);
        PD::setColor(1);
        PD::fillRect(110, 0, 110, 176);
        PD::drawBitmap(81, 60, Images::Swap_01);

    }
    else {

        PD::setColor(1);
        PD::fillRect(0, 0, 110, 176);
        PD::setColor(3);
        PD::fillRect(110, 0, 110, 176);
        PD::drawBitmap(81, 60, Images::Swap_00);

    }

    PD::setColor(7, 14);
    PD::fontSize = 2;
    PD::adjustCharStep = 1;
    PD::setCursor(20,130);

    switch (this->gameStatus.getPlayerView()) {

        case 0:

            switch (this->swapCaption) {

                case SwapCaption::DiscardACard:
                    PD::print("Player 1: Discard a card..");
                    break;

                case SwapCaption::LeadACard:
                    PD::print("Player 1: Lead a card..");
                    break;

                case SwapCaption::FollowALead:
                    PD::print("Player 1: Follow the lead..");
                    break;
 
                case SwapCaption::YourBid:
                    PD::print("Player 1: Your bid..");
                    break;

                default: break;
                    
            }

            break;

        default:

            switch (this->swapCaption) {

                case SwapCaption::DiscardACard:
                    PD::print("Player 2: Discard a card..");
                    break;

                case SwapCaption::LeadACard:
                    PD::print("Player 2: Lead a card..");
                    break;

                case SwapCaption::FollowALead:
                    PD::print("Player 2: Follow the lead..");
                    break;
 
                case SwapCaption::YourBid:
                    PD::print("Player 2: Your bid..");
                    break;

                default: break;
                    
            }

            break;

    }

}
