//
//  Scene.h
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/11/15.
//
//

/*
    Scene is in charge of drawing all the aspects of the game which includes:
        + Player Sprites
        + Game Ball
        + Score and other Text Information
 */

#ifndef Kiwi_Scene_h
#define Kiwi_Scene_h

#include "Player.h"
#include "Ball.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "Score.h"
#include <vector>

struct SpriteInfo
{
    float width, sheetWidth;
};

using SpriteInfoVec = std::vector<SpriteInfo>; // Structure to hold sprite information

using SpriteVec = std::vector<ci::gl::Texture>; // Structure to hold Sprite Sheets in the form of textures

class Scene
{
  public:
    // General
    Scene( int w, int h, int numPlayers, const std::string& font_fileName,  int fontSize ); // Initializes vector sizes according to the number of players, as well as Font for Font Renderer
    virtual                 ~Scene();
    void                    draw();
    void                    pause();
    void                    resume();
    
    // Player
    void                    initPlayer( PlayerPtr player, const std::string& image_filename ); // Adds reference to player as well as loads their sprite sheet
    
    // Ball
    void                    initBall( BallPtr ball ); // Adds reference to games's ball
    
    // Score
    void                    initScore( ScorePtr score ); // Adds reference to game's Score
    
    // Background Image
    void                    loadBGTexture( const std::string& image_filename );
    
  private:
    // Player
    PlayerPtrVec            playerPtrs;          // Vector to hold ptrs to Players in game
    SpriteVec               playerSprites;       // Vector to hold Sprite Sheet Textures
    SpriteInfoVec           spriteInfo;          // Vector to hold Sprite Information
    const bool              DRAW_HITBOX = false;
    void                    drawPlayers();
    
    // Ball
    BallPtr                 mBallPtr;            // Ptr to the game's Ball instance
    void                    drawBall();
    
    // Score
    ScorePtr                mScorePtr;           // Ptr to the game's Score instance
    void                    drawScore();
    
    // Text
    ci::gl::TextureFontRef  mText;               // Item used to draw out the game's text
    
    // Background
    ci::gl::Texture         mBGTex;              // Image Texture for the game
    
    // Other
    bool                    isPaused = false;
    const float             WINDOW_WIDTH, WINDOW_HEIGHT;
    
};
using ScenePtr = std::shared_ptr<Scene>;

#endif
