#pragma once
#include "cocos2d.h"
USING_NS_CC;

class EnergyBar: public Node
{
protected:
	ProgressTimer* _progress;
	Sprite* _background;
	float _percentage;
public:
	EnergyBar();
	virtual ~EnergyBar();
	CREATE_FUNC(EnergyBar);
	virtual bool init();
	void updateView(int value);
};

