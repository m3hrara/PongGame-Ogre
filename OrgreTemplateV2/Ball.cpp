#include "Ball.h"
#include "Game.h"
#include "Paddle.h"

/// <summary>
/// Constructor for the Ball class
/// </summary>
Ball::Ball()
{
	Speed = 0.6f;
	Score = 0;
	Lives = 5;
	paddle = nullptr;
	direction = Ogre::Vector3(-1, 1, 0);
	ballNode = nullptr;
}

/// <summary>
/// Ball update function to give it movement
/// </summary>
void Ball::Update(const Ogre::FrameEvent& fe)
{
	/// move ball every frame
	ballNode->translate(direction * Speed);
	if (Lives == 0)
	{
		direction = Ogre::Vector3(0, 0, 0);
		ballNode->setPosition(0, 20, 0);
	}
}

void Ball::ReflectX()
{
	direction = Ogre::Vector3(-1 * direction.x, direction.y, direction.z);
}

void Ball::ReflectY()
{
	direction = Ogre::Vector3(direction.x, -1 * direction.y, direction.z);
}

int Ball::GetLives()
{
	return Lives;
}

int Ball::GetScore()
{
	return Score;
}

void Ball::Respawn()
{
	direction = Ogre::Vector3(-1, 1, 0);
	ballNode->setPosition(0, 20, 0);
}

/// <summary>
/// Check collision between ball and paddle + bounds
/// </summary>
void Ball::CollisionCheck(Paddle* ref)
{
	// check collision with paddle
	AxisAlignedBox ballBox = ballNode->_getWorldAABB();
	AxisAlignedBox paddleBox = ref->GetPaddleNode()->_getWorldAABB();
	if (ballBox.intersects(paddleBox))
	{
		ReflectY();
		Score++;
	}
	/// check collision with boundries
	if (ballNode->getPosition().x > 52)
	{
		ReflectX();
	}
	else if (ballNode->getPosition().x < -52)
	{
		ReflectX();
	}
	else if (ballNode->getPosition().y > 40)
	{
		ReflectY();
	}
	else if (ballNode->getPosition().y < -50)
	{
		Respawn();
		Lives--;
		std::cout << "Lives: " << Lives << std::endl;
	}
}
void Ball::SetNode(Ogre::SceneNode* node)
{
	ballNode = node;
}
/// <summary>
/// This function sets the initial position and scale of the ball
/// </summary>
void Ball::Setup()
{
	ballNode->setPosition(0, 0, 0);
	ballNode->setScale(0.08f, 0.08f, 0.08f);
}
void Ball::SetLives(int lives)
{
	Lives = lives;
}
void Ball::SetScore(int score)
{
	Score = score;
}
Ball::~Ball() {}