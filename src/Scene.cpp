//
//  Scene.cpp
//  Kiwi
//
//  Created by Jacinth Nguyen on 2/11/15.
//
//

#include "Scene.h"

using namespace ci;
using namespace ci::app;

Scene::Scene( int w, int h, int numPlayers, const std::string& font_filename, int fontSize ): WINDOW_WIDTH( w ), WINDOW_HEIGHT( h )
{
    playerPtrs      = PlayerPtrVec( numPlayers );
    playerSprites   = SpriteVec( numPlayers );
    spriteInfo      = SpriteInfoVec( numPlayers );
    mText = gl::TextureFont::create( Font( loadAsset( font_filename ), fontSize ) );
}

Scene::~Scene()
{
}

void Scene::initPlayer( PlayerPtr player, const std::string& image_filename )
{
    int ID = player->ID_NUM;
    
    // Init Sprite and Info
    playerSprites[ID] = ci::gl::Texture( loadImage( loadAsset(image_filename) ) );
    spriteInfo[ID].sheetWidth = playerSprites[ID].getWidth();
    spriteInfo[ID].width = player->getWidth();
    playerPtrs[ID] = player;
}

void Scene::initBall(BallPtr ball)
{
    mBallPtr = ball;
}

void Scene::initScore(ScorePtr score )
{
    mScorePtr = score;
}

void Scene::loadBGTexture(const std::string &image_filename)
{
    mBGTex = ci::gl::Texture( ci::loadImage( ci::app::loadAsset(image_filename) ) );
}


void Scene::draw()
{
    // clear out the window with black
    gl::clear( Color( 0, 0, 0 ) );
    
    gl::setViewport( getWindowBounds() );
    gl::setMatricesWindowPersp( getWindowSize(), 15.0f, -1.0f, 1000.0f );
    
    // Draw the background image
    gl::draw( mBGTex, getWindowBounds() );
    
    gl::pushMatrices();
    
    // Invert y axis to make it point upwards
    //   * Note this is only required because we are using base OpenGL commands to draw the player and not Cinder's
    gl::scale(1, -1);
    
    // Move to set the origin to bottom left corner
    gl::translate( 0.0f, -(float)WINDOW_HEIGHT );
    
    // Move to center screen
    gl::translate( WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f, 0.0f );
    
    drawPlayers();
    drawBall();
    
    gl::popMatrices();
    
    drawScore();
    
    // Draw pause screen
    if( isPaused )
    {
        gl::enableAlphaBlending();
        
        // Draw rectangle to darken the screen
        gl::color( 0.5f, 0.5f, 0.5f, 0.5f );
        gl::drawSolidRect( Rectf(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT) );
        
        // Draw the word PAUSED
        gl::color( 1.0f, 1.0f, 1.0f, 1.0f );
        glEnable( GL_TEXTURE_2D );
        mText->drawString("PAUSED", Vec2f( WINDOW_WIDTH/2.2f, WINDOW_HEIGHT/2.0f ) );
        mText->drawString("Press 'Esc' to resume", Vec2f( WINDOW_WIDTH/3.2f, WINDOW_HEIGHT/1.75f ) );
        mText->drawString("Press 'Q' to exit TENNIS DUDES", Vec2f( WINDOW_WIDTH/3.2f, WINDOW_HEIGHT/1.50f ) );
        glDisable( GL_TEXTURE_2D );
        
        gl::disableAlphaBlending();
    }

}

void Scene::pause()
{
    isPaused = true;
}

void Scene::resume()
{
    isPaused = false;
}

void Scene::drawPlayers()
{
    for( int i = 0; i < playerPtrs.size(); i++ )
    {
        PlayerPtr    player = playerPtrs[i];
        gl::Texture &sprite = playerSprites[i];
        SpriteInfo  &info   = spriteInfo[i];
        
        // Draw Player
        gl::pushMatrices();
        
        gl::translate( player->getPos() );
        
        // Invert y axis to draw the image normally
        //  * Note that this is done after the translation
        gl::scale(1, -1);
        
        gl::enableAlphaBlending();
        glEnable(GL_TEXTURE_2D);
        
        sprite.enableAndBind();
        glBegin(GL_QUADS);
        
        float frame = player->getFrame();
        
        glTexCoord2f( (info.width * frame)/info.sheetWidth, 0 );
        glVertex2f( 0, 0);
        
        glTexCoord2f( (info.width * frame + info.width)/info.sheetWidth, 0 );
        glVertex2f( info.width, 0 );
        
        glTexCoord2f( (info.width * frame + info.width)/ info.sheetWidth, 1 );
        glVertex2f( info.width, info.width);
        
        glTexCoord2f( (info.width * frame)/info.sheetWidth, 1 );
        glVertex2f( 0, info.width);
        
        glEnd();
        
        sprite.unbind();
        
        glDisable(GL_TEXTURE_2D);
        gl::disableAlphaBlending();
        
        gl::popMatrices();

        // Draw Hit Box for testing purposes
        if(DRAW_HITBOX)
        {
            ci::Vec4f box = player->getHitBox();
            
            if( box.z > 0.0f )
            {
                gl::pushMatrices();
                gl::drawSolidCircle( box.xy(), box.z );
                gl::popMatrices();
            }
        }
        
        if( player->mustServe() )
        {
            gl::pushMatrices();
            gl::scale(1, -1);
            glEnable( GL_TEXTURE_2D );
            gl::enableAlphaBlending();
            mText->drawString( "PLAYER " + std::to_string(i+1) + " SERVE", Vec2f( WINDOW_WIDTH * (-0.2f/2.0f), -WINDOW_HEIGHT * 0.40f ) );
            gl::disableAlphaBlending();
            glDisable( GL_TEXTURE_2D );
            gl::popMatrices();
        }
    }
    
}

void Scene::drawBall()
{
    if( mBallPtr->isServed() )
    {
        gl::pushMatrices();
        
        gl::translate( mBallPtr->position() );
        gl::drawSolidCircle( Vec2f::zero(), mBallPtr->RADIUS );
        
        gl::popMatrices();
    }
}

void Scene::drawScore()
{
    gl::pushMatrices();
    glEnable( GL_TEXTURE_2D );
    gl::enableAlphaBlending();

    // Draw Left Scores
    mText->drawString( "SCORE: " + mScorePtr->getLeftScore(), Vec2f( WINDOW_WIDTH * 0.15f, WINDOW_HEIGHT * 0.9f ) );
    mText->drawString( "GAMES: " + std::to_string(mScorePtr->getLGamesWon()), Vec2f( WINDOW_WIDTH * 0.15f, WINDOW_HEIGHT * 0.95f ) );
    
    
    
    // Draw Right Scores
    mText->drawString( "SCORE: " + mScorePtr->getRightScore(), Vec2f( WINDOW_WIDTH * 0.65f, WINDOW_HEIGHT * 0.9f ) );
    mText->drawString( "GAMES: " + std::to_string(mScorePtr->getRGamesWon()), Vec2f( WINDOW_WIDTH * 0.65f, WINDOW_HEIGHT * 0.95f ) );
    
    
    
    gl::disableAlphaBlending();
    glDisable( GL_TEXTURE_2D );
    gl::popMatrices();
}