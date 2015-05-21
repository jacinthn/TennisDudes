//
//  GameSound.cpp
//  Kiwi
//
//  Created by Jacinth Nguyen on 2/12/15.
//
//

#include "GameSound.h"
#include "cinder/Timeline.h"
#include "cinder/app/AppBasic.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;

GameSoundPtr GameSound::sGlobalSound;

GameSound::GameSound(): mCurrentEffect( SEffect::NONE )
{
    init();
}

GameSound::~GameSound()
{
}

GameSoundPtr GameSound::instance()
{
    // Make GameSound if it is not instantiated
    if( !sGlobalSound ) {
        sGlobalSound = std::make_shared<GameSound>();
    }
    
    return sGlobalSound;
}

void GameSound::init()
{
	

    /*
//  Sound effects
	mJumpNoise = audio::load(loadAsset( "Jump.mp3" ), ctx->getSampleRate());
	mHitNoise = audio::load(loadAsset( "BallHit.mp3" ), ctx->getSampleRate());
	mStepNoise = audio::load(loadAsset( "Step.mp3" ), ctx->getSampleRate());
	mSwingNoise = audio::load(loadAsset( "Swing.mp3" ), ctx->getSampleRate());

	mEffectPlayer = ctx->makeNode(new audio::BufferPlayerNode());

	// Gain controls the volume
	mGain2 = ctx->makeNode(new audio::GainNode(1.0f));

	mEffectPlayer >> mGain2 >> ctx->getOutput();
    */

	mCurrentEffect = SEffect::NONE;
    
    mJumpNoise = audio::Voice::create( audio::load( loadAsset( "Jump.mp3" ) ) );
    mHitNoise = audio::Voice::create( audio::load( loadAsset( "BallHit.mp3" ) ) );
    mStepNoise = audio::Voice::create( audio::load( loadAsset( "Step.mp3" ) ) );
    mSwingNoise = audio::Voice::create( audio::load( loadAsset( "Swing.mp3" ) ) );
    
    // Point current noise to arbitrary sound
    mCurrentNoise = &mJumpNoise;
    
//  Music
    auto ctx = audio::Context::master();
    mTitleScreenTrack = audio::load( loadAsset( "Drumbeat.mp3" ), ctx->getSampleRate() ) ;
    mMatchTrack = audio::load( loadAsset( "MatchTheme.mp3" ), ctx->getSampleRate() ) ;
    
    mMusicPlayer = ctx->makeNode( new audio::BufferPlayerNode() );
    
    // Gain controls the volume
    mGain = ctx->makeNode( new audio::GainNode( 1.0f ) );
    
    // connect and enable the context
    mMusicPlayer >> mGain >> ctx->getOutput();
    ctx->enable();
    
    mCurrentSong = MusicTrack::NONE;

}

void GameSound::play( SEffect effect )
{
    // If it is the same effect
    if( mCurrentEffect == effect )
    {
        if( !mCurrentNoise->get()->isPlaying() )
            mCurrentNoise->get()->start();
    }
    else
    {
        // Change to the new effect
        mCurrentEffect = effect;
        
        // Stop the current noise
        if( mCurrentNoise->get()->isPlaying() )
            mCurrentNoise->get()->stop();
        
        // Switch to the correct noise
        if( effect == SEffect::JUMP )
        {
            mCurrentNoise = &mJumpNoise;
        }
        else if( effect == SEffect::STEP )
        {
            mCurrentNoise = &mStepNoise;
        }
        else if( effect == SEffect::SWING )
        {
            mCurrentNoise = &mSwingNoise;
        }
        
        // Play the new noise
        mCurrentNoise->get()->start();
    }
}

void GameSound::play( MusicTrack song )
{
    if( mCurrentSong != song )
    {
        // Change to the new song
        mCurrentSong = song;
        
        mMusicPlayer->stop();
        
        // Switch to the correct noise
        if( song == MusicTrack::NONE )
        {
            return;
        }
        else if( song == MusicTrack::TITLE )
        {
            mMusicPlayer->loadBuffer( mTitleScreenTrack );
            mMusicPlayer->setLoopEnabled();
            mMusicPlayer->setLoopEndTime( mTitleScreenTrack->getNumSeconds() );
        }
        else if( song == MusicTrack::MATCH )
        {
            mMusicPlayer->loadBuffer( mMatchTrack );
            mMusicPlayer->setLoopEnabled();
            mMusicPlayer->setLoopEndTime( mMatchTrack->getNumSeconds() );
        
        }
        
        // Play the new noise
        mMusicPlayer->start();
    }
}

void GameSound::pause()
{
	if( mCurrentNoise->get()->isPlaying() )
        mCurrentNoise->get()->pause();
    
    mMusicPlayer->stop();
}

void GameSound::resume()
{
    mCurrentNoise->get()->start();
    mMusicPlayer->start();
}

void GameSound::stop()
{
    mCurrentNoise->get()->stop();
    mMusicPlayer->stop();
}