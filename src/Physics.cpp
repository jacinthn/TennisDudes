//
//  Physics.cpp
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/18/15.
//
//

#include "Physics.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

template <typename T>
T clip(const T& n, const T& lower, const T& upper) {
    return std::max(lower, std::min(n, upper));
}

Physics::Physics( float ground ):
    GROUND( ground )
{
    mGSPtr = GameSound::instance();
}

Physics::~Physics()
{
}

void Physics::detect()
{
    if(!mBall)
        return;
    
    if(!mBall->isServed())
    {
        mBall->update();
        return;
    }
    
    if( mBall->isLive() )
    {
        // Use where the ball is speculated to fly for calculation
        Vec2f specPos = mBall->position() + mBall->velocity();
        
        // If ball will go through ground, make it bounce
        if( specPos.y <= GROUND )
        {
            mBall->bounce( GROUND );
            mBall->update();
            return;
        }
        
        // See if ball will go through net
        /*
        if( specPos.y <= GROUND + 60.0f )
        {
            float x1 = mBall->position().x, x2 = specPos.x;
            
            if( (x1 <= 0.0f && x2 >= 0.0f ) || (x1 >= 0.0f && x2 <= 0.0f ) )
            {
                mBall->net(mBall->position());
                return;
            }
        }
        */
        // Perform normal player collision
        {
            
            for( int i = 0; i < mPlayerPtrs.size(); i++ )
            {
                Vec4f hitBox = mPlayerPtrs[i]->getHitBox();
                
                // See if hit box is valid, i.e. its size is greater than 0
                if( hitBox.z > 0.0f )
                {
                    // Calculate distance vs radius
                    float radiusTotal = hitBox.z + mBall->RADIUS + 10.0f;
                    Vec2f v = mBall->position() - hitBox.xy();
                    
                    float ls = v.lengthSquared();
                    
                    if( ls < (radiusTotal * radiusTotal ) )
                    {
                        if(BALL_ASSIST)
                        {
                            // If ball is hit close to ground, make it go up
                            if( hitBox.y < ( GROUND + 120.0f ) )
                            {
                                // Use the second vector to add directional influence
                                mBall->impact( hitBox.xy(), mPlayerPtrs[i]->getDI() );
 
                            }
                            // Otherwise, spike it from the air
                            else
                            {
                                mBall->impact( hitBox.xy(), mPlayerPtrs[i]->getDI() );
                            }
                        }
                        else
                        {
                            mBall->impact( hitBox.xy(), v * hitBox.w );
                        }
                        
                        mGSPtr->play( SEffect::HIT );
                    }
                }
            }
        }
    }
    
    //Update ball after resolving collisions
    mBall->update();
}

void Physics::addPlayer(PlayerPtr ptr)
{
    mPlayerPtrs.push_back(ptr);
}

void Physics::setBall(BallPtr ptr)
{
    mBall = ptr;
}

void Physics::setScorePtr(ScorePtr ptr)
{
    mScorePtr = ptr;
}