#include "CardSprite.h"

USING_NS_CC;

int CardSprite::getNumber()
{
	return number;
}

void CardSprite::setNumber(int num)
{
	number = num;
	if (number >= 1024)
	{
		numberDisplay->setFontSize(40);
	}
	else if (number >= 128)
	{
		numberDisplay->setFontSize(60);
	}
	else if (number >= 16)
	{
		numberDisplay->setFontSize(90);
	}
	else
	{
		numberDisplay->setFontSize(100);
	}

	switch (number)
	{
	case 0:
		numberDisplay->setColor(Color3B(200, 190, 180));
		break;
	case 2:
		numberDisplay->setColor(Color3B(240, 230, 220));
		break;
	case 4:
		numberDisplay->setColor(Color3B(240, 220, 200));
		break;
	case 8:
		numberDisplay->setColor(Color3B(240, 180, 120));
		break;
	case 16:
		numberDisplay->setColor(Color3B(240, 140, 90));
		break;
	case 32:
		numberDisplay->setColor(Color3B(240, 120, 90));
		break;
	case 64:
		numberDisplay->setColor(Color3B(240, 90, 60));
		break;
	case 128:
		numberDisplay->setColor(Color3B(240, 90, 60));
		break;
	case 256:
		numberDisplay->setColor(Color3B(240, 200, 70));
		break;
	case 512:
		numberDisplay->setColor(Color3B(240, 200, 70));
		break;
	case 1024:
		numberDisplay->setColor(Color3B(0, 130, 0));
		break;
	default:
		numberDisplay->setColor(Color3B(0, 130, 0));
		break;
	}


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
