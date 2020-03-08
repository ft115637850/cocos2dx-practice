#pragma once

#include "cocos2d.h"

class PhyEdge :public cocos2d::Node
{
public:
	PhyEdge();
	~PhyEdge();
	virtual bool init();
	CREATE_FUNC(PhyEdge);
};

