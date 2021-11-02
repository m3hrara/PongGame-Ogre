#pragma once
#include "Paddle.h"

/// This class does setup and update for ball
class Ball
{
public:
	Ball();
	void Update(const Ogre::FrameEvent& fe);
	void ReflectX();
	void ReflectY();
	int GetLives();
	int GetScore();
	void Respawn();
	void CollisionCheck(Paddle* ref);
	void Setup();
	void SetNode(Ogre::SceneNode* node);
	void SetLives(int lives);
	void SetScore(int score);
	~Ball();
public:
	float Speed;
	int Score;
	int Lives;
	Paddle* paddle;
	Ogre::Vector3 direction;
	Ogre::SceneNode* ballNode;
};