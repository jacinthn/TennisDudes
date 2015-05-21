//
//  InputHandler.cpp
//  Kiwi
//
//  Created by Jacinth Nguyen on 2/4/15.
//
//

#include "InputHandler.h"

using namespace ci::app;

InputHandler::InputHandler( int players ): numPlayers( players )
{
    pin = std::vector<Input>(players);
    // Set all inputs to none
    for( int i = 0; i < players; i++ )
    {
        pin[i] = Input::NONE;
    }
    pbs  = std::vector<InputBools>(players);
}

InputHandler::~InputHandler()
{
    pbs.clear();
    pin.clear();
}

void InputHandler::toggle( const ci::app::KeyEvent& event )
{
    
    //  Set player input and input boolean to be true
    auto in = event.getCode();
    
    // Player 1 input
    if( in ==  KeyEvent::KEY_x)
    {
        if( !pbs[0].mL )
        {
            pbs[0].mL = true;
        }
        pin[0] = Input::LEFT;
    }
    
    else if( in == KeyEvent::KEY_c )
    {
        if( !pbs[0].mD )
        {
            pbs[0].mD = true;
        }
        pin[0] = Input::DOWN;
    }
    
    else if( in == KeyEvent::KEY_v )
    {
        if( !pbs[0].mR )
        {
            pbs[0].mR = true;
        }
        pin[0] = Input::RIGHT;
    }
    
    else if ( in == KeyEvent::KEY_d )
    {
        if( !pbs[0].mJ )
        {
            pbs[0].mJ = true;
        }
        pin[0] = Input::JUMP;
    }
    
    else if ( in == KeyEvent::KEY_LSHIFT )
    {
        if( !pbs[0].mH )
        {
            pbs[0].mH = true;
        }
        pin[0] = Input::HIT;
    }
    
    // Check for 2 players before assessing P2 controls
    if( numPlayers < 2)
    {
        return;
    }
    
    // Player 2 input
    if( in == KeyEvent::KEY_LEFT )
    {
        if( !pbs[1].mL )
        {
            pbs[1].mL = true;
        }
        pin[1] = Input::LEFT;
    }
    
    else if( in == KeyEvent::KEY_DOWN )
    {
        if( !pbs[1].mD )
        {
            pbs[1].mD = true;
        }
        pin[1] = Input::DOWN;
    }
    
    else if( in == KeyEvent::KEY_RIGHT )
    {
        if( !pbs[1].mR )
        {
            pbs[1].mR = true;
        }
        pin[1] = Input::RIGHT;
    }
    
    else if ( in == KeyEvent::KEY_UP )
    {
        if( !pbs[1].mJ )
        {
            pbs[1].mJ = true;
        }
        pin[1] = Input::JUMP;
    }
    
    else if ( in == KeyEvent::KEY_COMMA || in == KeyEvent::KEY_RSHIFT  )
    {
        if( !pbs[1].mH )
        {
            pbs[1].mH = true;
        }
        pin[1] = Input::HIT;
    }
}

void InputHandler::untoggle( const ci::app::KeyEvent& event )
{
    // Set value boolean to false
    auto in = event.getCode();
    
    // P1 Input
    if( in == KeyEvent::KEY_x )
    {
        pbs[0].mL = false;
    }
    
    else if( in == KeyEvent::KEY_c )
    {
        pbs[0].mD = false;
    }
    
    else if( in == KeyEvent::KEY_v )
    {
        pbs[0].mR = false;
    }
    
    else if ( in == KeyEvent::KEY_d )
    {
        pbs[0].mJ = false;
    }
    
    else if ( in == KeyEvent::KEY_LSHIFT )
    {
        pbs[0].mH = false;
    }
    
    // If no input is detected, set input to none
    if( (pbs[0].mL + pbs[0].mD + pbs[0].mR + pbs[0].mH + pbs[0].mJ) == 0 )
    {
        pin[0] = Input::NONE;
    }
    
    // Check for 2 players before assessing P2 controls
    if( numPlayers < 2)
    {
        return;
    }
    
    // P2 input
    if( in == KeyEvent::KEY_LEFT )
    {
        pbs[1].mL = false;
    }
    
    else if( in == KeyEvent::KEY_DOWN )
    {
        pbs[1].mD = false;
    }
    
    else if( in == KeyEvent::KEY_RIGHT )
    {
        pbs[1].mR = false;
    }
    
    else if ( in == KeyEvent::KEY_UP )
    {
        pbs[1].mJ = false;
    }
    
    else if ( in ==  KeyEvent::KEY_COMMA || in == KeyEvent::KEY_RSHIFT )
    {
        pbs[1].mH = false;
    }
    
    if( (pbs[1].mL + pbs[1].mD + pbs[1].mR + pbs[1].mH + pbs[1].mJ) == 0 )
    {
        pin[1] = Input::NONE;
    }
}

void InputHandler::pause()
{
    for( int i = 0; i < pbs.size(); i++ )
    {
        pbs[i].clear();
        pin[i] = Input::NONE;
    }
}
