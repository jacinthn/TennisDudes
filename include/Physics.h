//
//  Physics.h
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/15/15.
//
//

#ifndef GreenApple_Physics_h
#define GreenApple_Physics_h

#include "Player.h"
#include "Ball.h"
#include "GameSound.h"
#include "Score.h"
#include <vector>

class Physics
{
  public:
    Physics( float ground );
    virtual ~Physics();
    
    void detect();
    void addPlayer( PlayerPtr ptr );
    void setBall( BallPtr ptr );
    void setScorePtr( ScorePtr ptr );
    
  private:
    PlayerPtrVec mPlayerPtrs;
    BallPtr      mBall;
    GameSoundPtr mGSPtr;
    ScorePtr     mScorePtr;
    
    const float GROUND;
        
    const bool BALL_ASSIST = true;
    
};

using PhysicsPtr = std::shared_ptr<Physics>;

#endif
