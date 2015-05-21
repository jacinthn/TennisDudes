//
//  Player.cpp
//  Kiwi
//
//  Created by Jacinth Nguyen on 2/4/15.
//
//

#include "Player.h"
#include "cinder/Filesystem.h"
#include "Util.h"
#include <fstream>

using namespace ci;
using namespace std;

Player::Player( const ci::Vec2f& pos, int &ID, const float dir, const bool willServe ):
    mFrame( 0.0f ),
    mPos(pos),
    mHitBox( ci::Vec4f::zero() ),
    ID_NUM(ID), DIRECTION(dir),
    mWidth(0.0f),
    mMustServe( willServe ),
    mCurrentDI( DI::NONE ),
    mDI( Vec2f::zero() )
{
    ID++;
    mSCPtr = std::make_shared<StateContainer>();
    HitBoxData[0] = ci::Vec4f::zero();
    setHitBox(0);
    changeState( PSE::IDLE );
    enter();
    
}

Player::~Player()
{
}

void Player::update(const Input in)
{
    mState->handleInput(in, *this);
    mState->update( *this );
    
    // Texture sampling should start at 0, but frames are counted starting at 1
    // Thus we offset the current frame by -1
    mFrame = float(mState->getFrame()-1);
}

void Player::init(const std::string &filepath)
{
    if( !fs::exists(filepath) )
    {
        cinder::app::console() << "Player::init: Failed to find file: " << filepath << std::endl;
        exit(-1);
    }
    
    string  param;
    int     numItems;
    
    ifstream file(filepath);
    int fileLength = GetFileLength( file );
    assert( fileLength > 0 );
    
    file >> param;
    
    while( !file.eof() )
    {
        // Init Sprite and States
        if( param == "Sprite" )
        {
            file >> numItems;
            IgnoreLine( file, fileLength );
            
            int start, end;
            
            for( int i = 0; i < numItems; i++ )
            {
                file >> param;
                
                if( param == "Width" )
                {
                    float w;
                    file >> w;
                    setWidth(w);
                }
                
                else if( param == "Idle" )
                {
                    file >> start >> end;
                    initState( PSE::IDLE, start, end );
                }
                
                else if( param == "Ground" )
                {
                    file >> start >> end;
                    initState( PSE::GHIT, start, end );
                }
                
                else if( param == "Forward" )
                {
                    file >> start >> end;
                    initState( PSE::FRUN, start, end );
                }
                
                else if( param == "Backward" )
                {
                    file >> start >> end;
                    initState( PSE::BRUN, start, end );
                }
                
                else if( param == "Jump" )
                {
                    file >> start >> end;
                    initState( PSE::JUMP, start, end );
                }
                
                else if( param == "Land" )
                {
                    file >> start >> end;
                    initState( PSE::LAND, start, end );
                }
                
                else if( param == "Air" )
                {
                    file >> start >> end;
                    initState( PSE::JHIT, start, end );
                }

                IgnoreLine( file, fileLength );
            }
        }
        // End init Sprite and States
        
        // Init Hitboxes
        else if( param == "Hitbox" )
        {
            file >> numItems;
            int key;
            
            if( DIRECTION > 0.0f )
            {
                for(int i = 0; i < numItems; i++ )
                {
                    Vec4f hitBox = Vec4f::zero();
                    
                    file >> key >> hitBox.x >> hitBox.y >> hitBox.z >> hitBox.w;
                    addHitBox( key, hitBox );
                }
            }
            else
            {
                for(int i = 0; i < numItems; i++ )
                {
                    Vec4f hitBox = Vec4f::zero();
                    
                    file >> key >> hitBox.x >> hitBox.y >> hitBox.z >> hitBox.w;
                    hitBox.x = -hitBox.x + mWidth;
                    addHitBox( key, hitBox );
                }
            }
            
        }
        file >> param;
    }
    
}

void Player::initState( PSE aPSE, int startFrame, int endFrame )
{
    if( aPSE == PSE::IDLE)
        mSCPtr->mIdle.init( startFrame, endFrame );
    
    else if( aPSE == PSE::FRUN)
        mSCPtr->mFRunning.init( startFrame, endFrame );
    
    else if( aPSE == PSE::BRUN)
        mSCPtr->mBRunning.init( startFrame, endFrame );
    
    else if( aPSE == PSE::JUMP)
        mSCPtr->mJumping.init( startFrame, endFrame );
    
    else if( aPSE == PSE::LAND)
        mSCPtr->mLanding.init( startFrame, endFrame );
    
    else if( aPSE == PSE::GHIT)
        mSCPtr->mHitting.init( startFrame, endFrame );
    
    else if( aPSE == PSE::JHIT)
        mSCPtr->mJumpHit.init( startFrame, endFrame );
    
}

void Player::changeState( PSE aPSE )
{
    if( aPSE == PSE::IDLE)
        mState = &mSCPtr->mIdle;

    else if( aPSE == PSE::FRUN)
        mState = &mSCPtr->mFRunning;
    
    else if( aPSE == PSE::BRUN)
        mState = &mSCPtr->mBRunning;
    
    else if( aPSE == PSE::JUMP)
        mState = &mSCPtr->mJumping;
    
    else if( aPSE == PSE::LAND)
        mState = &mSCPtr->mLanding;
    
    else if( aPSE == PSE::GHIT)
        mState = &mSCPtr->mHitting;
    
    else if( aPSE == PSE::JHIT)
        mState = &mSCPtr->mJumpHit;
    
}
void Player::enter()
{
    mState->enter( *this );
}

void Player::move(const ci::Vec2f &movement)
{
    // If player is obligated to serve the ball
    if( mMustServe )
    {
        // Restrict player movment
        if( DIRECTION > 0.0f )
        {
            
            // Bind player within screen bounds
            // *** Note: Test serve barrier value
            if( (mPos.x+ movement.x + mWidth) < -500.0f && (mPos.x+ movement.x) > -683.0f )
            {
                mPos += movement;
            }
            else
            {
                // If player is at boundary, only update the jump
                mPos.y += movement.y;
            }
        }
        else
        {
            if( (mPos.x+ movement.x ) > 500.0f && (mPos.x+ movement.x + mWidth) < 683.0f )
            {
                mPos += movement;
            }
            else
            {
                mPos.y += movement.y;
            }
        }
        
    }
    // Otherwise...
    else
    {
        // Move freely
        if( DIRECTION > 0.0f )
        {
            
            // Bind player within screen bounds
            if( (mPos.x+ movement.x + mWidth) < 0.0f && (mPos.x+ movement.x) > -683.0f )
            {
                mPos += movement;
            }
            else
            {
                // If player is at boundary, only update the jump
                mPos.y += movement.y;
            }
        }
        else
        {
            if( (mPos.x+ movement.x ) > 0.0f && (mPos.x+ movement.x + mWidth) < 683.0f )
            {
                mPos += movement;
            }
            else
            {
                mPos.y += movement.y;
            }
        }
    }
}

// Sets the player's current hitbox
void Player::setHitBox(int frame)
{
    if( HitBoxData.find( frame ) != HitBoxData.end() )
    {
        Vec4f& hb = HitBoxData[frame];
        mHitBox.x = mPos.x + hb.x;
        mHitBox.y = mPos.y - hb.y; // Y is subtracted as the origin is at the top-left
        mHitBox.z = hb.z;
        mHitBox.w = hb.w;
    }
}

void Player::addHitBox(int frame, const ci::Vec4f &hitBox)
{
    auto it = HitBoxData.insert( std::make_pair( frame, hitBox ) );
    if( !it.second )
    {
        ci::app::console() << "Frame " << frame << " was overwritten. Please check your input data. \n";
    }
}

void Player::serve()
{
    mMustServe = false;
}

void Player::reset( const ci::Vec2f& pos, bool serving )
{
    mPos = pos;
    changeState( PSE::IDLE );
    mMustServe = serving;
    setHitBox(0);
}

void Player::setDI(const DI direction)
{
    if( direction == DI::NONE )
    {
        mDI.x = 0.0f;
        mDI.y = 0.0f;
    }
    else if( direction == DI::LEFT )
    {
        mDI.x = -3.0f * DIRECTION;
        mDI.y = 0.0f;
    }
    else if( direction == DI::RIGHT )
    {
        mDI.x = 3.0f * DIRECTION;
        mDI.y = 0.0f;
    }
    else if( direction == DI::DOWN )
    {
        mDI.x = 2.0f * DIRECTION;
        mDI.y = -4.0f;
    }
    else if( direction == DI::UP )
    {
        mDI.x = -2.0f * DIRECTION;
        mDI.y = 4.0f;
    }
}