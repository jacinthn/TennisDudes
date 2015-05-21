//
//  Ball.h
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/15/15.
//
//

#ifndef GreenApple_Ball_h
#define GreenApple_Ball_h

#include "Player.h"

class Ball
{
  public:
    Ball( const PlayerPtr server );
    Ball( const ci::Vec2f& pos, const ci::Vec2f& vel );
    
    // Response to player hitting ball
    void impact( const ci::Vec2f& loc, const ci::Vec2f& force );
    // Response to ball hitting ground
    void bounce( const float height );
    // Response to ball hitting net
    void net( const ci::Vec2f& loc);
    
    void serve();
    
    void reset( const ci::Vec2f& pos, const ci::Vec2f& vel );
    void reset( PlayerPtr server );
    
    const ci::Vec2f& position() const { return mPos; }
    const ci::Vec2f& velocity() const { return mVel; }
    const bool isLive() const { return mIsLive; }
    const bool isServed() const { return mServed; }
    const int  getBounces() const { return mBounces; }
    
    void update();
    
    const float RADIUS = 6.0f;
    
  private:
    ci::Vec2f   mPos;
    ci::Vec2f   mVel;
    ci::Vec2f   mServerDisplacement;
    
    int         mBounces;
    bool        mIsLive;
    PlayerPtr   mServer;
    bool        mServed;
    
    // Constant Values
    const float GRAVITY = 1.0f,
                BOUNCE_DAMPEN = 1.0f,
                ROLL_DAMPEN = 0.02f,
                MAX_UP_VEL = 20.0f;
    
    // *** Note: Look for good values
    const ci::Vec2f LEFT_SIDE_SERVE_VEL  = ci::Vec2f(  25.0f, 13.0f ),
                    RIGHT_SIDE_SERVE_VEL = ci::Vec2f( -27.0f, 16.0f );
};

using BallPtr = std::shared_ptr<Ball>;

#endif
