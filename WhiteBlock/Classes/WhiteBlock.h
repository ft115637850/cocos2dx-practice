#pragma once

#include "cocos2d.h"

class WhiteBlock : public cocos2d::Sprite
{
private:
	int lineIndex;
	cocos2d::Size visibleSize;
public:
	static cocos2d::Vector<WhiteBlock*> * blocks;
	virtual bool initWithArgs(cocos2d::Color3B color, cocos2d::Size size, std::string label, float fontSize, cocos2d::Color4B textColor);
	static WhiteBlock* createWithArgs(cocos2d::Color3B color, cocos2d::Size size, std::string label, float fontSize, cocos2d::Color4B textColor);
	void removeBlock();
	void setLineIndex(int v);
	int getLineIndex();
	void moveDown();
};