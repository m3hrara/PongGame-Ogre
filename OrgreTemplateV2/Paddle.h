#pragma once
#include "Ogre.h"
using namespace Ogre;

/// This class does setup and update for paddle
class Paddle
{
public:
	Paddle();
	void Setup();
	void SetNode(SceneNode* node);
	SceneNode* GetPaddleNode();
	~Paddle();
public:
	Vector3 moveDirection;
	Vector3 move;
	Entity* paddleEntity;
	SceneNode* paddleNode;
};
