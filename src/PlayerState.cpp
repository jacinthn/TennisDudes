//
//  State.cpp
//  Kiwi
//
//  Created by Jacinth Nguyen on 2/4/15.
//
//

#include "PlayerState.h"
#include "Player.h"

void PlayerState::init( int startFrame, int endFrame )
{
    mFrame      = startFrame;
    mStartFrame = startFrame;
    mEndFrame   = endFrame;
}

/*
    Idle State
*/

void IdleState::init(int startFrame, int endFrame)
{
    PlayerState::init(startFrame,endFrame);
}

void IdleState::handleInput(const Input input, Player& player)
{
    if(input == Input::JUMP )
    {
        if( !player.mustServe() )
        {
            player.changeState( PSE::JUMP );
            player.enter();
        }
    }
    
    else if(input == Input::HIT )
    {
        player.changeState( PSE::GHIT );
        player.enter();
    }
    
    else if(input == Input::LEFT )
    {
        if(player.DIRECTION > 0.0f)
        {
            player.changeState( PSE::BRUN );
            player.enter();
        }
        else
        {
            player.changeState( PSE::FRUN );
            player.enter();
        }
    }
    
    else if(input == Input::RIGHT )
    {
        if(player.DIRECTION > 0.0f)
        {
            player.changeState( PSE::FRUN );
            player.enter();
        }
        else
        {
            player.changeState( PSE::BRUN );
            player.enter();
        }
    }
}

void IdleState::update(Player &player)
{
    mFrame++;
    if(mFrame > mEndFrame)
    {
        mFrame = mStartFrame;
    }
}

void IdleState::enter( Player& player )
{
    mFrame = mStartFrame;
}

/*
    Forward Running State
 */

void FRunningState::init(int startFrame, int endFrame)
{
    PlayerState::init(startFrame,endFrame);
    mGSptr = GameSound::instance();
}

void FRunningState::handleInput(const Input input, Player& player)
{
    if(input == Input::JUMP )
    {
        if( !player.mustServe() )
        {
            player.changeState( PSE::JUMP );
            player.enter();
        }
    }
    
    else if(input == Input::HIT )
    {
        player.changeState( PSE::GHIT );
        player.enter();
    }
    
    else if( input == Input::LEFT )
    {
        if(player.DIRECTION > 0.0f)
        {
            player.changeState( PSE::BRUN );
            player.enter();
        }
    }
    
    else if(  input == Input::RIGHT )
    {
        if( player.DIRECTION < 0.0f )
        {
            player.changeState( PSE::BRUN );
            player.enter();
        }
    }
    
    else if(input == Input::NONE )
    {
        player.changeState( PSE::IDLE );
        player.enter();
    }
}

void FRunningState::update(Player &player)
{
    mFrame++;
    
    if(mFrame >= mEndFrame)
    {
        mFrame = mStartFrame;
    }

    player.move( ci::Vec2f( player.DIRECTION * MOVE_SPEED, 0.0f ) );
    
    mGSptr->play( SEffect::STEP );
}

void FRunningState::enter( Player& player )
{
    mFrame = mStartFrame;
}

/*
    Backward Running State
 */

void BRunningState::init(int startFrame, int endFrame)
{
    PlayerState::init(startFrame,endFrame);
    mGSptr = GameSound::instance();
}

void BRunningState::handleInput(const Input input, Player& player)
{
    if(input == Input::JUMP )
    {
        if( !player.mustServe() )
        {
            player.changeState( PSE::JUMP );
            player.enter();
        }
    }
    
    else if(input == Input::HIT )
    {
        player.changeState( PSE::GHIT );
        player.enter();
    }
    
    else if(input == Input::RIGHT )
    {
        if(player.DIRECTION > 0.0f)
        {
            player.changeState( PSE::FRUN );
            player.enter();
        }
    }
    else if(input == Input::LEFT)
    {
        if(player.DIRECTION < 0.0f )
        {
            player.changeState( PSE::FRUN );
            player.enter();
        }
    }
    
    else if(input == Input::NONE )
    {
        player.changeState( PSE::IDLE );
        player.enter();
    }
}

void BRunningState::update(Player &player)
{
    mFrame++;
    if(mFrame > mEndFrame)
    {
        mFrame = mStartFrame;
    }
    
    player.move( ci::Vec2f( player.DIRECTION * MOVE_SPEED, 0.0f ) );
    
    mGSptr->play( SEffect::STEP );
}

void BRunningState::enter( Player& player )
{
    mFrame = mStartFrame;
}


/*
    Jumping State
 */

void JumpingState::init(int startFrame, int endFrame)
{
    PlayerState::init(startFrame,endFrame);
    mGSptr = GameSound::instance();
}

void JumpingState::handleInput(const Input input, Player& player)
{
    // Enter a jumping hit
    if(input == Input::HIT )
    {
        if( mHitDelay == 0 )
        {
            mHitDelay   = HIT_DELAY;
            mFalling    = true; // Hitting in the air will cause a fall
            
            player.changeState( PSE::JHIT );
            player.enter();
            
        }
    }
    
    // If player holds down jump button, they will jump higher
    else if( input == Input::JUMP )
    {
        if( mJumpHeight < MAX_JUMP_HEIGHT )
        {
            mJumpHeight = std::min( MAX_JUMP_HEIGHT, mJumpHeight + 2 * JUMP_SPEED );
        }
    }
    
    else if( input == Input::LEFT )
    {
        mArielMomentum = -ARIEL_SPEED;
    }
    
    else if( input == Input::RIGHT )
    {
        mArielMomentum = ARIEL_SPEED;
    }

}

void JumpingState::update(Player &player)
{
    // Stay on end frame when it is reached
    if( mFrame != mEndFrame )
    {
        mFrame++;
    }
    
    if( (mCurrentJump < mJumpHeight ) && !mFalling )
    {
        
        mCurrentJump += JUMP_SPEED;
        
        if(mCurrentJump >= mJumpHeight )
            mFalling = true;
        
        player.move( ci::Vec2f( 0.0f, JUMP_SPEED ) );
    }
    else
    {
        // 1. Calculate the jump height after falling distance D in timestep
        mCurrentJump -= FALL_SPEED;
        
        // If person is still above ground, lower them accordingly
        if( mCurrentJump > 0 )
        {
            player.move( ci::Vec2f( 0.0f, -FALL_SPEED ) );
        }
        // Else if the player would go below ground, lower them the remaining distance
        else if( mCurrentJump < 0 )
        {
            player.move( ci::Vec2f( 0.0f, -(mCurrentJump + FALL_SPEED) ) );
            player.changeState( PSE::LAND );
            player.enter();
        }
        // Else the person lands exactly on the ground and is lowered accordingly
        else
        {
            player.move( ci::Vec2f( 0.0f, -FALL_SPEED ) );
            player.changeState( PSE::LAND );
            player.enter();

        }
    }
    
    if( mHitDelay > 0 )
    {
        mHitDelay--;
    }
}

void JumpingState::enter( Player& player )
{
    mFrame          = mStartFrame;
    mJumpHeight     = NORMAL_JUMP_HEIGHT;
    mCurrentJump    = 0;
    mHitDelay       = 0;
    mArielMomentum  = 0;
    mFalling        = false;
    
    mGSptr->play( SEffect::JUMP );
}

/*
    Landing State
 */

void LandingState::init(int startFrame, int endFrame)
{
    PlayerState::init(startFrame,endFrame);
}

void LandingState::handleInput(const Input input, Player& player)
{
}

void LandingState::update(Player &player)
{
    // Stay on end frame when it is reached
    if( mFrame < mEndFrame )
    {
        mFrame++;
    }
    else
    {
        player.changeState( PSE::IDLE );
        player.enter();
    }
    
}

void LandingState::enter( Player& player )
{
    mFrame          = mStartFrame;
}

/*
    Ground Hitting State
 */

void HittingState::init(int startFrame, int endFrame)
{
    PlayerState::init(startFrame,endFrame);
    mGSptr = GameSound::instance();
}

void HittingState::handleInput(const Input input, Player& player)
{
    // Testing DI in the form of enums
    if( input == Input::LEFT)
    {
        player.setDI( DI::LEFT );
    }
    else if( input == Input::RIGHT)
    {
        player.setDI( DI::RIGHT );
    }
    else if( input == Input::DOWN)
    {
        player.setDI( DI::DOWN );
    }
    else if( input == Input::JUMP )
    {
        player.setDI( DI::UP );
    }
}

void HittingState::update(Player &player)
{
    // Stay on end frame when it is reached
    if( mFrame != mEndFrame )
    {
        mFrame++;
        player.setHitBox( mFrame );
    }
    else
    {
        player.setHitBox( 0 ); // Zero out hitbox when leaving state
        player.changeState( PSE::IDLE );
        player.enter();
    }
    
}

void HittingState::enter( Player& player )
{
    mFrame          = mStartFrame;
    mGSptr->play( SEffect::SWING );
    player.setDI( DI::NONE );
    
    if( player.mustServe() )
    {
        player.serve();
        mGSptr->play( SEffect::HIT );
    }
}

/*
    Air Hitting State
 */

void JumpHitState::init(int startFrame, int endFrame)
{
    PlayerState::init(startFrame,endFrame);
    mGSptr = GameSound::instance();
}

void JumpHitState::handleInput(const Input input, Player& player)
{
    if( input == Input::LEFT)
    {
        player.setDI( DI::LEFT );
    }
    else if( input == Input::RIGHT)
    {
        player.setDI( DI::RIGHT );
    }
    else if( input == Input::DOWN)
    {
        player.setDI( DI::DOWN );
    }
    else if( input == Input::JUMP )
    {
        player.setDI( DI::UP );
    }
}

void JumpHitState::update(Player &player)
{
    // Stay on end frame when it is reached

    if( mFrame != mEndFrame )
    {
        mFrame++;
        player.setHitBox( mFrame );
    }
    else
    {
        player.setHitBox( 0 );
        // Change to jump without resetting the jump
        player.changeState( PSE::JUMP );
    }
    
}

void JumpHitState::enter( Player& player )
{
    mFrame          = mStartFrame;
    mGSptr->play( SEffect::SWING );
    player.setDI( DI::NONE );
}
