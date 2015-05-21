//
//  GameSound.h
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/12/15.
//
//

/*
    GameSound handles sound effects from various sources which include:
        + Player actions
        + Physics engine
        + Etc.
 
    GameSound is also a singleton which is allocated upon its first use via Static Shared Pointers.
 */
#ifndef Kiwi_Audio_h
#define Kiwi_Audio_h

#include "cinder/app/AppNative.h"
#include "cinder/audio/Voice.h"
#include "cinder/audio/Source.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/NodeEffects.h"
#include "cinder/audio/SamplePlayerNode.h"

#include "cinder/audio/Context.h"

class GameSound;

using GameSoundPtr = std::shared_ptr<GameSound>;

enum class SEffect
{
	NONE, JUMP, HIT, STEP, SWING
};

enum class MusicTrack
{
    NONE, TITLE, MATCH
};

class GameSound
{
  public:
    GameSound(); // Calls Init() upon construction
    virtual ~GameSound();
    void    play( SEffect effect ); // Stops current sound effect and plays new effect
    void    play( MusicTrack song );
    void    pause();
    void    resume();
    void    stop();
    
    static GameSoundPtr     instance(); // Creates an instance of GameSound if it doesn't exist and returns a Static Pointer
    
  private:
    void                    init(); // Loads the sounds which contains hardcoded filenames
    
    static GameSoundPtr     sGlobalSound;
    
    /*
	ci::audio::BufferPlayerNodeRef mEffectPlayer;
    ci::audio::SourceFileRef     mJumpNoise,
								 mHitNoise,
								 mStepNoise,
                                 mSwingNoise;
    */
    
    ci::audio::VoiceRef    *mCurrentNoise,
                                mJumpNoise,
                                mHitNoise,
                                mStepNoise,
                                mSwingNoise;
    
    SEffect                 mCurrentEffect;
    
    ci::audio::BufferPlayerNodeRef mMusicPlayer;
    ci::audio::SourceFileRef       mTitleScreenTrack;
    ci::audio::SourceFileRef       mMatchTrack;
    ci::audio::GainNodeRef         mGain;
    
    MusicTrack              mCurrentSong;
};

#endif
