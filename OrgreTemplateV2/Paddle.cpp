#include "Paddle.h"
#include "Game.h"
using namespace Ogre;

/// <summary>
/// Constructor for the Paddle class
/// </summary>
Paddle::Paddle()
{
	moveDirection = Vector3(0, 0, 0);
	move = Vector3(0, 0, 0);
}
/// <summary>
/// Set the initial position and size of the paddle
/// </summary>
void Paddle::Setup()
{
	paddleNode->setPosition(0, -35, 0);
	paddleNode->setScale(0.1f, 0.01f, 1.0f);
}

void Paddle::SetNode(Ogre::SceneNode* node)
{
	paddleNode = node;
}
/// <summary>
/// Get a reference to the paddlenode
/// </summary>
SceneNode* Paddle::GetPaddleNode()
{
	return paddleNode;
}

Paddle::~Paddle()
{}