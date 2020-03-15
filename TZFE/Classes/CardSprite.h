#pragma once
#include "cocos2d.h"

class CardSprite: public cocos2d::Sprite
{
private:
	int number;
	cocos2d::LabelTTF* numberDisplay;
public:
	int getNumber();
	void setNumber(int num);
	static CardSprite* createCard(int number, int width, int height, float xAxis, float yAxis);
	bool initCard(int number, int width, int height, float xAxis, float yAxis);
};

