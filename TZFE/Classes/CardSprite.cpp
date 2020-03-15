#include "CardSprite.h"

USING_NS_CC;

int CardSprite::getNumber()
{
	return number;
}

void CardSprite::setNumber(int num)
{
	number = num;
	if (number > 0)
	{
		numberDisplay->setString(StringUtils::format("%d", number));
	}
	else {
		numberDisplay->setString("");
	}
}

CardSprite * CardSprite::createCard(int number, int width, int height, float xAxis, float yAxis)
{
	CardSprite* c = new CardSprite();
	if (c && c->initCard(number, width, height, xAxis, yAxis))
	{
		c->autorelease();
		return c;
	}
	CC_SAFE_DELETE(c);
	return nullptr;
}

bool CardSprite::initCard(int number, int width, int height, float xAxis, float yAxis)
{
	if (Sprite::init() == false) {
		return false;
	}

	auto bg = LayerColor::create(Color4B(200, 190, 180, 255), width - 15, height - 15);
	bg->setPosition(xAxis, yAxis);
	numberDisplay = LabelTTF::create("", "HirakakuProN-W6", 100);
	numberDisplay->setPosition(bg->getContentSize().width / 2, bg->getContentSize().height / 2);
	bg->addChild(numberDisplay);
	addChild(bg);

	setNumber(number);
	return true;
}
