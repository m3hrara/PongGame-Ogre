#pragma once
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include <iostream>
#include "Ball.h"
#include "Paddle.h"
using namespace Ogre;
using namespace OgreBites;

/// This class takes care of the main game
class Game
    : public ApplicationContext
    , public InputListener
{
private:
    OgreBites::TrayListener myTrayListener;
    OgreBites::TrayManager* mTrayMgr;
    OgreBites::Label* mInfoLabel;
    OgreBites::Label* mFpsLabel;
    OgreBites::Label* mFps;
    OgreBites::Label* mScoreLabel;
    OgreBites::Label* mTpuLabel;
    OgreBites::Label* mLivesLabel;
    
    SceneManager* scnMgr;
    SceneNode* ballNode;
    SceneNode* paddleNode;
    Root* root;
    Ball* BallObject;
    Paddle* PaddleObject;

public:
    OgreBites::Label* scoreLabel;
    OgreBites::Label* livesLabel;
    OgreBites::Label* mTpu;

public:
    Game();
    SceneManager* GetSceneManager();
    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    void createScene();
    void createCamera();
    void createFrameListener();
    virtual ~Game() {}
};