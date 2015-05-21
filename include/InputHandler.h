//
//  InputHandler.h
//  Kiwi
//
//  Created by Jacinth Nguyen on 2/4/15.
//
//

/*
    InputHandler is in charge of interpreting keyboard inputs and translating them to game commands.
    
    The game loops constantly reads from the the input handler, which player instances draw their inputs from.
 
 */

#ifndef Kiwi_InputHandler_h
#define Kiwi_InputHandler_h

#include "cinder/app/AppNative.h"

enum class Input
{
    NONE, LEFT, DOWN, RIGHT, HIT, JUMP
};

// Holds information regarding whether or not a button is pressed. Exists one for every player.
struct InputBools
{
    bool    mL = false,
            mD = false,
            mR = false,
            mH = false,
            mJ = false;
    
    // Used when pausing
    void clear()
    {
        mL = mD = mR = mH = mJ = false;
    }
};

class InputHandler
{
  public:
    InputHandler( int players );    // Sizes vectors to the number of players
    virtual ~InputHandler();
    void    toggle( const ci::app::KeyEvent& event );      // Interperets key press and assigns input
    void    untoggle( const ci::app::KeyEvent& event );    // Set input press to false
    void    pause();                // Clears input and input booleans
    
    Input getInput( int PLAYER_ID ) const { return pin[PLAYER_ID]; }  // Returns input for player requesting it
    
  private:
    std::vector<InputBools>  pbs; // Player booleans
    std::vector<Input>       pin; // Player inputs
    int                      numPlayers;
};

using InputModPtr = std::shared_ptr<InputHandler>;
#endif
