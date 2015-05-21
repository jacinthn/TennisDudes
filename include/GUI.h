//
//  GUI.h
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/28/15.
//
//

#ifndef GreenApple_GUI_h
#define GreenApple_GUI_h

#include "cinder/app/AppNative.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/gl/Texture.h"

using namespace ci;
using namespace ci::app;

enum MenuItems
{
    START, CONTROLS, CREDITS, TIPS
};

class GUI
{
  public:
    GUI( int windowWidth, int windowHeight );
    virtual ~GUI();
    
    void init( int titleSize, int menuSize );
    void update();
    void draw();
    bool keyDown( const KeyEvent& event );
    
  private:
    gl::Texture OrangeGuy, BlueGuy;
    
    gl::TextureFontRef TitleFont;
    gl::TextureFontRef MenuFont;
    
    int     MenuIndex;
    
    const float WINDOW_WIDTH, WINDOW_HEIGHT;
    // Set to value of last item in MenuItems
    const int MENU_INDEX_MAX = MenuItems::TIPS;
};

using GUIptr = std::shared_ptr<GUI>;
#endif
