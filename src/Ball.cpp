//
//  Ball.cpp
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/18/15.
//
//

#include "Ball.h"
#include "cinder/Rand.h"

using namespace ci;

Ball::Ball( const PlayerPtr server ):
    mServer( server ),
    mPos( Vec2f::zero() ),
    mServerDisplacement( Vec2f::zero() ),
    mBounces( 0 ),
    mIsLive( true ),
    mServed( false )
{
    
    // Calculate and set the initial point of the ball's server
    float w = mServer->getWidth();
    
    if( mServer->DIRECTION > 0.0f )
    {
        mServerDisplacement = Vec2f( w * 3.0f/4.0f, -w/2.0f );
    }
    else
    {
        mServerDisplacement = Vec2f( -w * 1.0f/4.0f, -w/2.0f );
    }
    
    mPos = mServer->getPos() + mServerDisplacement;
}

Ball::Ball( const ci::Vec2f& pos, const ci::Vec2f& vel ):
    mPos( pos ),
    mVel( vel ),
    mBounces( 0 ),
    mIsLive( true ),
    mServed( true )
{
}

// Response to player hitting ball
void Ball::impact(const ci::Vec2f &loc, const ci::Vec2f &force)
{
    mPos = loc;
    
    if( loc.x <= 0.0f )
    {
        mVel.x = 15.0f + force.x;
    }
    else
    {
        mVel.x = -(15.0f + force.x );
    }

    mVel.y = 20.0f + force.y;
    mBounces = 0;
}

// Response to ball hiting ground
void Ball::bounce(const float height)
{
    
    // Set the y velocity of the ball to fly up with a little less strength than it had coming down
    float upVel = -mVel.y - BOUNCE_DAMPEN;
    
    // If ball loses y velocity, set it equaly to 0
    if( upVel <= 0.5f )
    {
        mVel.y = 0.0f;
        mIsLive = false;
    }
    else
    {
        mVel.y = std::min( upVel, MAX_UP_VEL );
    }
    
    mBounces++;
}

void Ball::net(const ci::Vec2f &loc)
{
    mVel.x = -mVel.x * 0.3f;
    mVel.y = -2.0f;
}

void Ball::serve()
{
    mServed = true;
    
    if( mServer->DIRECTION > 0.0f )
    {
        mVel = LEFT_SIDE_SERVE_VEL;
    }
    else
    {
        mVel = RIGHT_SIDE_SERVE_VEL;
    }
}

void Ball::update()
{
    if( mServed )
    {
        mPos += mVel;
        // As long as ball is bouncing, i.e. moving up or down the y-axis, factor in gravity
        if( mIsLive )
        {
            mVel.y -= GRAVITY;
        }
        else
        {
            // Otherwise as long as ball is moving either in the positive or negative X direction, dampen the roll until it stops
            if( mVel.x > 0.0f )
            {
                mVel.x = mVel.x - ROLL_DAMPEN;
                if( mVel.x < 0.0f )
                {
                    mVel.x = 0.0f;
                }
            }
            else if( mVel.x < 0.0f )
            {
                mVel.x = mVel.x + ROLL_DAMPEN;
                if( mVel.x > 0.0f )
                {
                    mVel.x = 0.0f;
                }
            }
        }
    }
    else
    {
        mPos = mServer->getPos() + mServerDisplacement;
        
        if( !mServer->mustServe() )
            serve();
    }
}

void Ball::reset(const ci::Vec2f &pos, const ci::Vec2f &vel)
{
    mPos = pos;
    mVel = vel;
    mBounces = 0;
    mServed = true;
    mIsLive = true;
}

void Ball::reset( PlayerPtr server )
{
    mServed = false;
    mPos = Vec2f::zero();
    mVel = Vec2f::zero();
    mBounces = 0;
    mIsLive = true;
    
    // Change server if different
    if( server != mServer )
        mServer = server;
}