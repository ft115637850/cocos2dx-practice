#pragma once

#include <cocos2d.h>
#include "PhyEdge.h"
#include "Hero.h"
#include "RandomBlock.h"

class GameController: public cocos2d::Ref
{
private:
	cocos2d::Layer* _layer;
	float _positionY;
	int currentFrameIdx;
	int nextFrameCount;
	void resetFrameCount();
	void addBlock();
	PhyEdge* edge;
	Hero* hero;
public:
	virtual bool init(cocos2d::Layer* layer, float positionY);
	virtual void onUpdate();
	bool histTestPoint(Vec2 point);
	void onUsrTouch();
	static GameController* create(cocos2d::Layer* layer, float positionY);
};

