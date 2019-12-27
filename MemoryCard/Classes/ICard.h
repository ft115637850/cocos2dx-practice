#pragma once

#include <functional>
#include "CardData.h"
#include "CardState.h"
#include "cocos2d.h"
USING_NS_CC;

class ICard: public Node {
public:
	virtual void flipToBack(const std::function<void()> &callback=nullptr) = 0;
	virtual void flipToFront(const std::function<void()> &callback = nullptr) = 0;
	virtual CardState getCardState() const = 0;
	virtual void setCardData(CardData data) = 0;
	virtual CardData* getCardData() = 0;
};