//
//  Game.h
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/28/15.
//
//

#ifndef GreenApple_Game_h
#define GreenApple_Game_h

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Player.h"
#include "PlayerState.h"
#include "InputHandler.h"
#include "Scene.h"
#include "Physics.h"
#include "Score.h"
#include "GameState.h"
#include "cinder/params/Params.h"

class Game
{
  public:
    Game( int windowWidth, int windowHeight );
    virtual ~Game();
    
    void init();
    bool keyDown( const ci::app::KeyEvent& event );
    void keyUp( const ci::app::KeyEvent& event );
    void update();
    void draw();
    void exit();
    void shutdown();
    
  private:
    InputModPtr                 mInput;
    PlayerPtr                   P1, P2;
    BallPtr                     mBall;
    PhysicsPtr                  mPhysics;
    ScenePtr                    mScene;
    GameSoundPtr                mGSPtr;
    ScorePtr                    mScore;
    GameStatePtr                mGameState;
    
    int                         mNumPlayers;
    
    bool                        PAUSED;
    const bool                  mDEBUG = false;
    
    const float                 WINDOW_WIDTH, WINDOW_HEIGHT;
    
    ci::params::InterfaceGlRef  mParams;
    ci::Vec3f                   TEST_DI;
};

using GamePtr = std::shared_ptr<Game>;

#endif
