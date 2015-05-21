//
//  State.h
//  Kiwi
//
//  Created by Jacinth Nguyen on 2/4/15.
//
//

#ifndef Kiwi_State_h
#define Kiwi_State_h

#include "Player.h"
#include "InputHandler.h"
#include "GameSound.h"

class Player;

class PlayerState
{
  public:
    virtual void init( int startFrame, int endFrame ) = 0;
    virtual void handleInput( const Input input, Player& player ) = 0;
    virtual void update( Player& player ) = 0;
    virtual void enter( Player& player ) = 0;
    const int getFrame() const { return mFrame; }
    
  protected:
    int mFrame, mStartFrame, mEndFrame;
};

// Player is Idle
class IdleState: public PlayerState
{
  public:
    virtual void init( int startFrame, int endFrame );
    virtual void handleInput( const Input input, Player& player );
    virtual void update( Player& player );
    virtual void enter( Player& player );
};

// Player is moving forwards
class FRunningState: public PlayerState
{
  public:
    virtual void init( int startFrame, int endFrame );
    virtual void handleInput( const Input input, Player& player );
    virtual void update( Player& player );
    virtual void enter( Player& player );
    
  private:
    const float MOVE_SPEED = 18.0f;
    
    GameSoundPtr    mGSptr;
};

// Player is moving backwards
class BRunningState: public PlayerState
{
  public:
    virtual void init( int startFrame, int endFrame );
    virtual void handleInput( const Input input, Player& player );
    virtual void update( Player& player );
    virtual void enter( Player& player );
    
  private:
    const float MOVE_SPEED = -18.0f;
    
    GameSoundPtr    mGSptr;
};


// Player is jumping
class JumpingState: public PlayerState
{
  public:
    virtual void init( int startFrame, int endFrame );
    virtual void handleInput( const Input input, Player& player );
    virtual void update( Player& player );
    virtual void enter( Player& player );
    
  private:
    
    const int   JUMP_SPEED  = 20, NORMAL_JUMP_HEIGHT = 40, MAX_JUMP_HEIGHT = 180,
                HIT_DELAY = 5, ARIEL_SPEED = 10, FALL_SPEED = 18;
    
    int         mCurrentJump = 0, mJumpHeight = 0, mHitDelay = 0, mArielMomentum = 0;
    
    bool        mFalling = false;
    
    GameSoundPtr    mGSptr;
};

// Player is landing
class LandingState: public PlayerState
{
public:
    virtual void init( int startFrame, int endFrame );
    virtual void handleInput( const Input input, Player& player );
    virtual void update( Player& player );
    virtual void enter( Player& player );
};

// Player is hitting from the ground
class HittingState: public PlayerState
{
  public:
    virtual void init( int startFrame, int endFrame );
    virtual void handleInput( const Input input, Player& player );
    virtual void update( Player& player );
    virtual void enter( Player& player );
    
  private:
    GameSoundPtr    mGSptr;
};

// Player is hitting from the air
class JumpHitState: public PlayerState
{
  public:
    virtual void init( int startFrame, int endFrame );
    virtual void handleInput( const Input input, Player& player );
    virtual void update( Player& player );
    virtual void enter( Player& player );
    
private:
    GameSoundPtr    mGSptr;
};

// Player state enums
enum class PSE
{
    IDLE, FRUN, BRUN, JUMP, LAND, GHIT, JHIT
};

struct StateContainer
{
    IdleState        mIdle;
    FRunningState    mFRunning;
    BRunningState    mBRunning;
    JumpingState     mJumping;
    LandingState     mLanding;
    HittingState     mHitting;
    JumpHitState     mJumpHit;
};

#endif
