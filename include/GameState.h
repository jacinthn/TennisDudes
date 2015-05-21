//
//  GameState.h
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/26/15.
//
//

#ifndef GreenApple_GameState_h
#define GreenApple_GameState_h

#include "Player.h"
#include "Ball.h"
#include "Score.h"

/*
    Manages the state of the game by enforcing the rules, settings the score, setting player positions, etc.
 */
class GameState
{
  public:
    GameState( int numPlayers, BallPtr ball, ScorePtr score, float left, float right, const ci::Vec2f& p1pos = ci::Vec2f::zero(), const ci::Vec2f& p2pos = ci::Vec2f::zero() );
    virtual ~GameState();
    
    // Initialization
    void         addPlayer( PlayerPtr ptr );
    
    // Loop
    void         update();
    
    // Exit
    void         reset();
    
  private:
    // Attributes
    PlayerPtrVec mPlayers;
    BallPtr      mBallPtr;
    ScorePtr     mScorePtr;
    
    const float  LEFT_EDGE, RIGHT_EDGE;
    
    std::vector<ci::Vec2f> mInitialPositions;
    
    int          mCSID = 0; // Current Server ID

    int          mGames = 0;
    
    // Methods
    void         resetRound();
    void         switchServer();
};

using GameStatePtr = std::shared_ptr<GameState>;
#endif
