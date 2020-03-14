#pragma once
#include "cocos2d.h"

class Pop: public cocos2d::Sprite
{
private:
	int number;
	cocos2d::LayerColor* colorBg;
public:
	int xIdx;
	int yIdx;
	int getNumber();
	void setNumber(int num);
	static Pop* createPop(int number, int width, int height, float xAxis, float yAxis);
	bool initPop(int number, int width, int height, float xAxis, float yAxis);

};

