//
//  Score.cpp
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/26/15.
//
//

#include "Score.h"

Score::Score():
    mLeftPoints(0),
    mRightPoints(0),
    mLGamesWon(0),
    mRGamesWon(0),
    mLeftTerm( "0"),
    mRightTerm( "0" )
{

}

Score::~Score()
{
}

void Score::LeftScore()
{
    // Love going to 15
    if( mLeftPoints == 0 )
    {
        mLeftTerm = "15";
        mLeftPoints = 1;
    }
    
    // 15 going to 30
    else if( mLeftPoints == 1 )
    {
        mLeftTerm = "30";
        mLeftPoints = 2;
    }
    
    // 30 going to
    else if( mLeftPoints == 2 )
    {
        // If opponents points are at 30, 15, or Love
        if( mRightPoints <= 2 )
        {
            // Set score to 40
            mLeftTerm = "40";
            // Go to game point
            mLeftPoints = 4;
        }
        // Else if opponent is at 40
        else if( mRightPoints == 4 )
        {
            // Set both players to Deuce
            mLeftTerm = "Deuce";
            // Go to Deuce
            mLeftPoints = 3;
            
            mRightTerm = "Deuce";
            mRightPoints = 3;
        }
    }
    
    // Deuce Purgatory
    else if( mLeftPoints == 3 )
    {
        // If opponent is at Advantage
        if( mRightPoints == 4 )
        {
            // Opponent goes back to Desuce
            mRightTerm = "Deuce";
            mRightPoints = 3;
        }
        // If opponent is at Deuce
        else
        {
            // Go to Advantage
            mLeftTerm = "Advantage";
            mLeftPoints = 4;
        }
    }
    
    // Advantage
    else if( mLeftPoints == 4 )
    {
        mLeftTerm = "Game";
        mLGamesWon++;
        mGameOver = true;
    }
    
}

void Score::RightScore()
{
    // Love going to 15
    if( mRightPoints == 0 )
    {
        mRightTerm = "15";
        mRightPoints = 1;
    }
    
    // 15 going to 30
    else if( mRightPoints == 1 )
    {
        mRightTerm = "30";
        mRightPoints = 2;
    }
    
    // 30 going to
    else if( mRightPoints == 2 )
    {
        // If opponents points are at 30, 15, or Love
        if( mLeftPoints <= 2 )
        {
            // Set score to 40
            mRightTerm = "40";
            mRightPoints = 4;
        }
        // Else if opponent is at 40
        else if( mLeftPoints == 4 )
        {
            // Set both players to Deuce
            mRightTerm = "Deuce";
            mRightPoints = 3;
            
            mLeftTerm = "Deuce";
            mLeftPoints = 3;
        }
    }
    
    // Deuce Purgatory
    else if( mRightPoints == 3 )
    {
        // If opponent is at Advantage
        if( mLeftPoints == 4 )
        {
            // Set opponent to Deuce
            mLeftTerm = "Deuce";
            mLeftPoints = 3;
        }
        else
        {
            // Go to Advantage
            mRightTerm = "Advantage";
            mRightPoints = 4;
        }
    }
    
    // Game point
    else if( mRightPoints == 4 )
    {
        mRightTerm = "Game";
        mRGamesWon++;
        mGameOver = true;
    }
    
}

void Score::reset( bool resetGames )
{
    mLeftPoints = mRightPoints = 0;
    mLeftTerm = mRightTerm = "0";
    mGameOver = false;
    
    if( resetGames )
    {
        mRGamesWon = mLGamesWon = 0;
    }
}
