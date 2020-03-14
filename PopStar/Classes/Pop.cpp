#include "Pop.h"

USING_NS_CC;

int Pop::getNumber()
{
	return number;
}

void Pop::setNumber(int num)
{
	number = num;
	switch (number)
	{
	case -1:
		colorBg->setColor(Color3B(200, 190, 180));
		break;
	case 0:
		colorBg->setColor(Color3B(250, 230, 40));
		break;
	case 1:
		colorBg->setColor(Color3B(40, 180, 250));
		break;
	case 2:
		colorBg->setColor(Color3B(130, 220, 110));
		break;
	case 3:
		colorBg->setColor(Color3B(250, 80, 130));
		break;
	case 4:
		colorBg->setColor(Color3B(180, 50, 250));
		break;
	}
}

Pop * Pop::createPop(int number, int width, int height, float xAxis, float yAxis)
{
	Pop* p =new Pop();
	if (p && p->initPop(number, width, height, xAxis, yAxis))
	{
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool Pop::initPop(int number, int width, int height, float xAxis, float yAxis)
{
	if (Sprite::init() == false) {
		return false;
	}

	colorBg = LayerColor::create(Color4B(200, 190, 180, 255), width - 5, height - 5);
	colorBg->setPosition(xAxis, yAxis);
	addChild(colorBg);
	setNumber(number);
	return true;
}
