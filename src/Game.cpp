//
//  Game.cpp
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/28/15.
//
//

#include "Game.h"
#include "cinder/app/App.h"
#include "Resources.h"


using namespace ci;
using namespace ci::app;
using namespace std;

Game::Game( int windowWidth, int windowHeight ): WINDOW_WIDTH( windowWidth ), WINDOW_HEIGHT( windowHeight ), PAUSED( false ), mNumPlayers( 0 ), TEST_DI(ci::Vec3f::zero()), mParams( params::InterfaceGl::create( "Tennis Dudes Debug", Vec2i( 300, 300 ) ) )
{
}

Game::~Game()
{
}

void Game::init()
{
    // Initialize score
    mScore = std::make_shared<Score>();
    
    // Initialize player and states
    // Calculate player positions based on window size
    Vec2f P1pos = Vec2f( -WINDOW_WIDTH/2.0f, -64.0f );
    Vec2f P2Pos = Vec2f( WINDOW_WIDTH/2.0f - 110.0f, -64.0f ); // P2 position hardcoded, fix later
    
    // Player 1
    P1 = std::make_shared<Player>( P1pos, mNumPlayers, 1.0f, true );
    P1->init( getAssetPath( "TennisGuy.si" ).string() );
    
    // Player 2
    P2 = std::make_shared<Player>( P2Pos, mNumPlayers, -1.0f );
    P2->init( getAssetPath( "TennisGuy.si" ).string() );
    
    // Initialize Input (must be done anytime after player initialization )
    mInput  = std::make_shared<InputHandler>( mNumPlayers );
    
    // Initialize Ball
    mBall = std::make_shared<Ball>( P1 );
    
    // Initialize Sounds
    mGSPtr  = GameSound::instance();
    
    // Initialize Textures must be done after Players and Ball
    mScene  = std::make_shared<Scene>( WINDOW_WIDTH, WINDOW_HEIGHT, mNumPlayers, "PressStart2P.ttf", 20 );
    mScene->loadBGTexture( "Court.png" );
    mScene->initPlayer( P1, "TennisGuy.png" );
    mScene->initPlayer( P2, "TennisGuy2.png" );
    mScene->initBall( mBall );
    mScene->initScore( mScore );
    
    // Initialize Physics engine
    // ** Hard coded GROUND value, change sometime
    mPhysics = std::make_shared<Physics>( -174.0f );
    mPhysics->addPlayer( P1 );
    mPhysics->addPlayer( P2 );
    mPhysics->setBall( mBall );
    mPhysics->setScorePtr( mScore );
    
    // Finally, initialize game state
    mGameState = make_shared<GameState>( mNumPlayers, mBall, mScore, -WINDOW_WIDTH/2.0f, WINDOW_WIDTH/2.0f, P1pos, P2Pos );
    mGameState->addPlayer( P1 );
    mGameState->addPlayer( P2 );
    
    mParams->addParam("P1 DI", &TEST_DI );
}

bool Game::keyDown( const ci::app::KeyEvent& event )
{
    if( PAUSED )
    {
        // Unpause the game
        if( event.getCode() == KeyEvent::KEY_ESCAPE )
        {
            PAUSED = false;
            mScene->resume(); // Deactivates pause screen
            mGSPtr->resume(); // Resumes sound
        }
        else if( event.getChar() == 'q' )
        {
            return true;
        }
        return false;
    }
    
    // Pause the game when Escape is pressed
    if( event.getCode() == KeyEvent::KEY_ESCAPE )
    {
        PAUSED = true;
        mGSPtr->pause(); // Pauses the currently playing sound
        mScene->pause(); // Pausing the scene activates the pause sceen
        mInput->pause(); // Pausing the input will clear all previous inputs
    }

// Developer commands
    else if(mDEBUG)
    {
        // Reset ball to bounce in front of Right Player
        if( event.getChar() == '0' )
        {
            mBall->reset( Vec2f( WINDOW_WIDTH/4.0f, -10.0f) , Vec2f( 0.0f, 0.0f ) );
        }
        
        // Reset ball to bounce in front of Left Player
        else if( event.getChar() == '9' )
        {
            mBall->reset( Vec2f( -WINDOW_WIDTH/4.0f, -10.0f) , Vec2f( 0.0f, 0.0f ) );
        }
        
        // Reset game score including the games won
        else if( event.getChar() == '1' )
        {
            mScore->reset( true );
        }
        else if( event.getChar() == '2' )
        {
            mScore->LeftScore();
        }
        else if( event.getChar() == '3' )
        {
            mScore->RightScore();
        }
    }

// Handle input normally
    else
    {
        mInput->toggle( event );
    }
    
    return false;
}

void Game::keyUp( const ci::app::KeyEvent& event )
{
    // While game is paused, do not affect the keys
    if( PAUSED )
        return;
    
    // Let input know that key is no longer pressed
    mInput->untoggle( event );
}

void Game::update()
{
    if( PAUSED )
        return;
    
    auto v = P1->getDI();
    TEST_DI.x = v.x;
    TEST_DI.y = v.y;
    
    // Update players based on their current state
    P1->update( mInput->getInput( P1->ID_NUM ) );
    P2->update( mInput->getInput( P2->ID_NUM ) );
    
    // Solve for collisions (as well as update the ball
    mPhysics->detect();
    
    // Update game state accordingly
    mGameState->update();
    
}

void Game::draw()
{
    mScene->draw();
    
    if(mDEBUG)
    {
        mParams->draw();
    }
}

void Game::exit()
{
    mGSPtr->stop();
    mInput->pause(); // Pause clear input data, same thing as resetting it
    mGameState->reset();
}

void Game::shutdown()
{
}