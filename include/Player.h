//
//  Player.h
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/4/15.
//
//

/*
    Player embodies the main State of the player, i.e. it holds the information for which its PlayerStates communicate.
 
    Many classes also utilize public properites of Player such as the Player's ID and Direction.
    
    Creating a player will increment global number of players and the Player's ID will be the initial value. 
 
    For example: Starting with 0 players, after creation Player 1 will have ID 0 and the game will recognize 1 player instance.
 
    Player changes based on it's current state via '*this'
 
 */

#ifndef Kiwi_Player_h
#define Kiwi_Player_h

#include "cinder/Vector.h"
#include "cinder/gl/Texture.h"
#include "PlayerState.h"
#include "InputHandler.h"
#include <map>
#include <vector>

class PlayerState;
enum class PSE;
struct StateContainer;

enum class DI
{
    NONE, LEFT, RIGHT, DOWN, UP
};

class Player
{
  public:
    Player( const ci::Vec2f& pos, int &ID, const float dir, const bool willServe = false );
    virtual       ~Player();
    
// Public properties of a player
    const int                       ID_NUM;
    const float                     DIRECTION;  // Direction which the player faces
                                                //  1.0f = Towards rights of the screen
                                                // -1.0f = Towards left of the screen
// Initialization Methods
    void    init( const std::string& filepath );
    void    initState( PSE aPSE, int startFrame, int endFrame );
    void    setWidth( float w ) { mWidth = w; }
    void    addHitBox( int frame, const ci::Vec4f& hitBox );
    
// "Get" methods
    const ci::Vec2f&    getPos() const { return mPos; }
    const ci::Vec2f&    getDI() const { return mDI; }
    const float         getFrame() const { return mFrame; }
    const ci::Vec4f&    getHitBox() const{ return mHitBox; }
    const float         getWidth() const { return mWidth; }
    const bool          mustServe() const { return mMustServe; }
    
// State change methods
    void    changeState( PSE aPSE );  // Used to change between states
    void    enter();                  // Calls the entering method of state
    void    update( const Input in ); // Used in update loop; calls state's update method
    
    void    move( const ci::Vec2f& movement );
    void    setHitBox( int frame );   // Sets player hitbox based on frame
    
    void    setDI( const DI direction );
    
    void    reset( const ci::Vec2f& pos, bool serving = false );
                                    // Resets player position and serving status if needed

    void    serve();    // Sets mMustServe to false

  private:
// State
    std::shared_ptr<StateContainer> mSCPtr;     // Pointer to Container encapsulating player states
    PlayerState  *mState;    //
    
    ci::Vec2f    mPos;       // Position on screen
    float        mWidth;     // Width of player sprite used for various purposes
    bool         mMustServe;/*
                                                 Determines whether or not a person must serve.
                                                 
                                                 Having to serve:
                                                 1. Restricts movement to a SERVING BOX
                                                 2. Allows player only to MOVE and HIT
                                                 
                                                 By default, this variable is initialized to false
                                                 */
// Scene
    float   mFrame;     // Current frame of animation
    
// Physics
    DI                              mCurrentDI;
    ci::Vec2f                       mDI;        // Directional Influence
    ci::Vec4f                       mHitBox;    // Current set hitbox
    std::map< int, ci::Vec4f >      HitBoxData;
                                                /*  v.x = x position
                                                 v.y = y position
                                                 v.z = radius of hit
                                                 v.w = power of hit
                                                 */
};

using PlayerPtr = std::shared_ptr<Player>;
using PlayerPtrVec = std::vector<PlayerPtr>;

#endif
