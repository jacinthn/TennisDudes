#include "cinder/app/AppNative.h"
#include "Game.h"
#include "GUI.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class GreenApple : public AppNative {

  public:
    void prepareSettings( Settings* settings );
    void setup();
    void keyDown( KeyEvent event );
    void keyUp( KeyEvent event );
    void update();
    void draw();
    void shutdown();
    
  private:
    GamePtr         mGame;
    GUIptr          mGUI;
    GameSoundPtr    mSound;
    int             mModuleIndex;
    const int       MODULE_GUI = 0, MODULE_GAME = 1;
};

void GreenApple::prepareSettings( Settings* settings )
{
    settings->setFrameRate( 30.0f );
    settings->setWindowSize( 1366, 768 );
    settings->setResizable( false );
    settings->setTitle( "Tennis Dudes" );
}

void GreenApple::setup()
{
    mGame = make_shared<Game>( getWindowWidth(), getWindowHeight() );
    mGame->init();
    
    mGUI = make_shared<GUI>( getWindowWidth(), getWindowHeight() );
    
    mSound = GameSound::instance();
    
    mModuleIndex = MODULE_GUI;
    mSound->play( MusicTrack::TITLE ); // Play the Title Theme first
}

void GreenApple::keyDown( KeyEvent event )
{
    if ( mModuleIndex == MODULE_GAME )
    {
        if( mGame->keyDown( event ) )
        {
            quit();
        }
    }
    else if( mModuleIndex == MODULE_GUI )
    {
        // If value is received from keypress, then start has been selected
        if( mGUI->keyDown( event ) )
        {
            mModuleIndex = MODULE_GAME;
            mSound->play( MusicTrack::MATCH ); // Play the Match theme
        }
    }
}

void GreenApple::keyUp( KeyEvent event )
{
    if ( mModuleIndex == MODULE_GAME )
    {
        mGame->keyUp(event);
    }
    else if( mModuleIndex == MODULE_GUI )
    {
        return;
    }
}

void GreenApple::update()
{
    if( mModuleIndex == MODULE_GAME )
    {
        mGame->update();
    }
    else if ( mModuleIndex == MODULE_GUI )
    {
        mGUI->update();
    }
}

void GreenApple::draw()
{
    if( mModuleIndex == MODULE_GAME )
    {
        mGame->draw();
    }
    else if ( mModuleIndex == MODULE_GUI )
    {
        mGUI->draw();
    }
}

void GreenApple::shutdown()
{
    // Bug in Cinder requires manual destruction of GameSound
    mSound->~GameSound();
}

CINDER_APP_NATIVE( GreenApple, RendererGl )
