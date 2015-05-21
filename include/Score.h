//
//  Score.h
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/26/15.
//
//

#ifndef GreenApple_Score_h
#define GreenApple_Score_h

class Score
{
  public:
    Score();
    virtual ~Score();
    
    void LeftScore(), RightScore();
    void reset( bool resetGames = false );
    
    const std::string& getLeftScore() const { return mLeftTerm; }
    const std::string& getRightScore() const { return mRightTerm; }
    const int getLGamesWon() const { return mLGamesWon; }
    const int getRGamesWon() const { return mRGamesWon; }
    const bool gameOver() const { return mGameOver; }
    
  private:
    int         mLeftPoints, mRightPoints,
                mLGamesWon, mRGamesWon;
    std::string mLeftTerm, mRightTerm;
    bool        mGameOver = false;
    
};
using ScorePtr = std::shared_ptr<Score>;

#endif
