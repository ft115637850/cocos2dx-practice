#pragma once

#include "ICard.h"
#include "cocos2d.h"
USING_NS_CC;
class CardFactory
{
public:
	virtual ICard* createCard(int backId, unsigned int number);
};

