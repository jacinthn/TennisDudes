//
//  GameState.cpp
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/26/15.
//
//

#include "GameState.h"

using namespace ci;

GameState::GameState( int numPlayers, BallPtr ball, ScorePtr score, float left, float right, const ci::Vec2f& p1pos, const ci::Vec2f& p2pos ):
    mBallPtr( ball ),
    mScorePtr( score ),
    LEFT_EDGE( left ),
    RIGHT_EDGE( right )
{
    mPlayers = PlayerPtrVec(numPlayers);
    mInitialPositions = std::vector<ci::Vec2f>( numPlayers );
    mInitialPositions[0] = p1pos;
    mInitialPositions[1] = p2pos;
}

GameState::~GameState()
{
}

// Initialization
void GameState::addPlayer( PlayerPtr ptr )
{
    mPlayers[ ptr->ID_NUM  ] = ptr;
}

// Loop
void GameState::update()
{
    Vec2f pos = mBallPtr->position();
    
    if( pos.x < LEFT_EDGE )
    {
        mScorePtr->RightScore();
        if( mScorePtr->gameOver() )
        {
            mScorePtr->reset();
            switchServer();
        }
        resetRound();
    }
    else if( pos.x > RIGHT_EDGE )
    {
        mScorePtr->LeftScore();
        if( mScorePtr->gameOver() )
        {
            mScorePtr->reset();
            switchServer();
        }
        resetRound();
    }
}

void GameState::reset()
{
    mGames = 0;
    mCSID = 0;
    resetRound();
    mScorePtr->reset(true);
}

void GameState::resetRound()
{
    // Reset the players
    for( int i = 0; i < mPlayers.size(); i++ )
    {
        // If the server ID and the player match up, set them to serve
        mPlayers[i]->reset( mInitialPositions[i], (i) == mCSID );
    }

    // Set the ball to be held by the server
    mBallPtr->reset(mPlayers[mCSID]);
}

void GameState::switchServer()
{
    if( mCSID == 0 )
        mCSID = 1;
    else
        mCSID = 0;
}