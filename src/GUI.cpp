//
//  GUI.cpp
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/28/15.
//
//

#include "GUI.h"
#include "Resources.h"


GUI::GUI( int windowWidth, int windowHeight ): WINDOW_WIDTH( windowWidth ), WINDOW_HEIGHT( windowHeight ), MenuIndex( 0 )
{
    init( 45, 20 );
}

GUI::~GUI()
{
}

void GUI::init( int titleSize, int menuSize )
{
    TitleFont = gl::TextureFont::create( Font( loadAsset("PressStart2P.ttf"), titleSize ) );
	MenuFont = gl::TextureFont::create(Font(loadAsset("PressStart2P.ttf"), menuSize));
    
    OrangeGuy = gl::Texture( loadImage( loadAsset("OrangeGuy.png") ) );
    BlueGuy = gl::Texture( loadImage( loadAsset("BlueGuy.png") ) );
}

void GUI::update()
{
    
}

void GUI::draw()
{
    gl::clear();
    
    gl::enable( GL_TEXTURE_2D );
    gl::enableAlphaBlending();
    
    // Draw Title
    TitleFont->drawString( "TENNIS DUDES",
                          Vec2f( WINDOW_WIDTH * (1.2f/4.0f),
                                WINDOW_HEIGHT * (1.0f/8.0f) ) );
    
    // Draw Menu Items
    MenuFont->drawString( "START 2P",
                         Vec2f( WINDOW_WIDTH * (0.90f/2.0f),
                               WINDOW_HEIGHT * (6.0f/9.0f) ) );
    
    MenuFont->drawString( "CONTROLS",
                         Vec2f( WINDOW_WIDTH * (0.90f/2.0f),
                               WINDOW_HEIGHT * (6.75f/9.0f) ) );
    
    MenuFont->drawString( "CREDITS",
                         Vec2f( WINDOW_WIDTH * (0.90f/2.0f),
                                WINDOW_HEIGHT * (7.50f/9.0f) ) );

	MenuFont->drawString("TIPS",
						 Vec2f(WINDOW_WIDTH * (0.90f / 2.0f),
								WINDOW_HEIGHT * (8.25f / 9.0f)));
    
    // Draw corresponding menu pieces
    if( MenuIndex == MenuItems::START )
    {
        // Selection arrow
        MenuFont->drawString( ">",
                             Vec2f( WINDOW_WIDTH * (0.85f/2.0f),
                                   WINDOW_HEIGHT * (6.0f/9.0f) ) );
        // vs.
        TitleFont->drawString( "VS.",
                             Vec2f( WINDOW_WIDTH * (0.94f/2.0f),
                                   WINDOW_HEIGHT * (0.9f/2.0f) ) );
        
        // Orange Guy texture
        gl::draw( OrangeGuy, Rectf( WINDOW_WIDTH * (2.0f/8.0f),
                                   WINDOW_HEIGHT * (1.0f/4.0f),
                                   WINDOW_WIDTH * (3.0f/8.0f),
                                   WINDOW_HEIGHT * (2.0f/4.0f) ) );
        // Blue Guy texture
        gl::draw( BlueGuy, Rectf( WINDOW_WIDTH * (5.0f/8.0f),
                                 WINDOW_HEIGHT * (1.0f/4.0f),
                                 WINDOW_WIDTH * (6.0f/8.0f),
                                 WINDOW_HEIGHT * (2.0f/4.0f) ) );
    }
    else if( MenuIndex == MenuItems::CONTROLS )
    {
        // Selection arrow
        MenuFont->drawString( ">",
                            Vec2f( WINDOW_WIDTH * (0.85f/2.0f),
                                   WINDOW_HEIGHT * (6.75f/9.0f) )
                             );
    
        // Orange Guy texture
        gl::draw( OrangeGuy, Rectf( WINDOW_WIDTH * (2.0f/8.0f),
                                    WINDOW_HEIGHT * (1.0f/4.0f),
                                    WINDOW_WIDTH * (3.0f/8.0f),
                                    WINDOW_HEIGHT * (2.0f/4.0f) ) );
        
        // P1 Controls
        MenuFont->drawString( "P1 \n\nX: Left \nV: Right \nD: Jump\nC: Down \nShift: Hit/Serve \nEsc: Pause",
                             Vec2f( WINDOW_WIDTH * (0.80f/8.0f),
                                    WINDOW_HEIGHT * (1.2f/4.0f) ) );

        
        // Blue Guy texture
        gl::draw( BlueGuy, Rectf( WINDOW_WIDTH * (5.0f/8.0f),
                                   WINDOW_HEIGHT * (1.0f/4.0f),
                                   WINDOW_WIDTH * (6.0f/8.0f),
                                   WINDOW_HEIGHT * (2.0f/4.0f) ) );
        // P2 Controls
        MenuFont->drawString( "P2 \n\nLeft: Left \nRight: Right \nUp: Jump\nDown: Down\n,: Hit/Serve \nEsc:Pause",
                             Vec2f( WINDOW_WIDTH * (6.0f/8.0f),
                                   WINDOW_HEIGHT * (1.2f/4.0f) ) );
    }
    else if( MenuIndex == MenuItems::CREDITS )
    {
        // Selection Arrow
        MenuFont->drawString( ">", Vec2f( WINDOW_WIDTH * (0.85f/2.0f),
                                         WINDOW_HEIGHT * (7.5f/9.0f) ) );
        
        // Credits
        // P1 Controls
        MenuFont->drawString( "Programmed, Drawn,\nand Sound Produced by: Jacinth Nguyen \n\nSprites created using Aseprite \n\nSound Effects created using Bfxr \n\nMusic created using MilkyTracker \n\nFont: \"Press Start\" by Codeman38",
                             Vec2f( WINDOW_WIDTH * (1.0f/8.0f),
                                   WINDOW_HEIGHT * (1.2f/4.0f) ) );
    }
	else if (MenuIndex == MenuItems::TIPS)
	{
		// Selection Arrow
		MenuFont->drawString(">", Vec2f(WINDOW_WIDTH * (0.85f / 2.0f),
										WINDOW_HEIGHT * (8.25f / 9.0f)));

		// Credits
		// P1 Controls
		MenuFont->drawString("+ Tapping a direction right after swinging will\n\tinfluence the trajectory of the ball.\n\tUse this to trick your opponent!\n\n+ During the Serving Phase, the receiver is able\n\tto move freely.\n\tUse this to position yourself accordingly.",
			Vec2f(WINDOW_WIDTH * (1.0f / 8.0f),
			WINDOW_HEIGHT * (1.2f / 4.0f)));
	}
    
    gl::disableAlphaBlending();
    gl::disable( GL_TEXTURE_2D );
}

bool GUI::keyDown( const KeyEvent& event )
{
    // Scroll up on menu
    if( event.getCode() == KeyEvent::KEY_UP )
    {
        // If selection goes beyond beginning
        MenuIndex--;
        if(MenuIndex < 0 )
        {
            // Go to bottom menu option
            MenuIndex = MENU_INDEX_MAX;
        }
        return false;
    }
    // Scroll down on menu
    else if( event.getCode() == KeyEvent::KEY_DOWN )
    {
        // If selection goes past menu ending
        MenuIndex++;
        if(MenuIndex > MENU_INDEX_MAX )
        {
            // Go to top menu option
            MenuIndex = 0;
        }
    }
    // Selecting an item in the menu
    else if( event.getCode() == KeyEvent::KEY_RETURN )
    {
        // Start the game
        if( MenuIndex == START )
        {
            return true;
        }
    }
    return false;
}
