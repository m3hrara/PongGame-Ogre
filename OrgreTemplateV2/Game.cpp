/*
GAME3121 Assignment 1
Pong in Ogre
Jaan Sangha 101264598
Mehrara Sarabi 101247463
*/

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include <iostream>
#include "Game.h"
using namespace Ogre;
using namespace OgreBites;

Vector3 translate = Vector3(0, 0, 0);

/// This class is the main frame listener that updates the game
class GameFrameListener : public FrameListener
{
private:
    Timer timer;
    Ball* ballRef;
    Paddle* paddleRef;
    Game* gameRef;

public:
    GameFrameListener(Ball* ball, Paddle* paddle, Game* game)
    {
        timer.reset();
        ballRef = ball;
        paddleRef = paddle;
        gameRef = game;
    }

    bool frameStarted(const FrameEvent& evt)
    {
        ///move paddle
        paddleRef->GetPaddleNode()->translate(translate * evt.timeSinceLastFrame * 30);
        translate = Vector3(0, 0, 0);
        ///update labels
        gameRef->scoreLabel->setCaption(std::to_string(ballRef->GetScore()));
        gameRef->livesLabel->setCaption(std::to_string(ballRef->GetLives()));
        gameRef->mTpu->setCaption(std::to_string(timer.getMilliseconds() / 1000));
        ///collision check on ball
        ballRef->CollisionCheck(paddleRef);
        ///move ball
        ballRef->Update(evt);

        return true;
    }

    bool frameEnded(const FrameEvent& evt)
    {
        return true;
    }
};

/// Game Constructor
Game::Game()
    : ApplicationContext("Pong")
{
    ///create ball and paddle objects in scene
    BallObject = new Ball();
    PaddleObject = new Paddle();
}


/// This function returns a reference to the scene manager when called
SceneManager* Game::GetSceneManager()
{
    return scnMgr;
}


/// Function that is called when the application starts
void Game::setup()
{
    ApplicationContext::setup();
    addInputListener(this);

    root = getRoot();
    scnMgr = root->createSceneManager();

    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

    Light* light = scnMgr->createLight("MainLight");
    SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);

    lightNode->setPosition(20, 80, 50);

    createScene();
    createCamera();
    createFrameListener();
}


/// Check for Keypress inputs
bool Game::keyPressed(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        break;
    case 'a':
        if (paddleNode->getPosition().x >-42)
        {
            translate = Ogre::Vector3(-20, 0, 0);
        }
        break;
    case 'd':
        if (paddleNode->getPosition().x < 42)
        {
            translate = Ogre::Vector3(20, 0, 0);
        }
        break;
    case 'r':
    {   
        BallObject->SetLives(5); 
        BallObject->SetScore(0);
        BallObject->Respawn();
    }
        break;
    default:
        break;
    }
    return true;
}

/// This function initially creates the visual scene objects
void Game::createScene()
{
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

    ///create tray manager and labels
    mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());
    scnMgr->addRenderQueueListener(mOverlaySystem);

    addInputListener(mTrayMgr);

    mInfoLabel = mTrayMgr->createLabel(TL_TOP, "TInfo", "Pong Game", 250);

    mTrayMgr->showFrameStats(TL_TOPRIGHT);
    mTrayMgr->toggleAdvancedFrameStats();

    mScoreLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Score", "Score:", 150);
    scoreLabel = mTrayMgr->createLabel(TL_TOPLEFT, "score", std::to_string(BallObject->GetScore()), 150);

    mTpuLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "Time", "Time:", 150);
    mTpu = mTrayMgr->createLabel(TL_TOPRIGHT, "tpu", "0", 150);

    mLivesLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Lives", "Lives:", 150);
    livesLabel = mTrayMgr->createLabel(TL_TOPLEFT, "lives", std::to_string(BallObject->GetLives()), 150);

    ///create ball
    Ogre::Entity* ballEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_SPHERE);
    ballEntity->setMaterialName("Examples/BeachStones");
    ballNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    ballNode->attachObject(ballEntity);
    BallObject->SetNode(ballNode);
    BallObject->Setup();

    ///create paddle
    Ogre::Entity* paddleEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_PLANE);
    paddleEntity->setMaterialName("Examples/GrassFloor");
    paddleNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    paddleNode->attachObject(paddleEntity);
    PaddleObject->SetNode(paddleNode);
    PaddleObject->Setup();
}


/// This function creates the camera that the user will have in their viewport
void Game::createCamera()
{
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5);
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 100);
    camNode->lookAt(Vector3(0, 0, 0), Node::TS_WORLD);

    getRenderWindow()->addViewport(cam);
}

/// This creates a new frame listener of the existing frame listener class
void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new GameFrameListener(BallObject, PaddleObject, this);
    mRoot->addFrameListener(FrameListener);
}

/// Main game loop 
int main(int argc, char** argv)
{
    try
    {
        Game app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}