#include "RandomBlock.h"

USING_NS_CC;

RandomBlock::RandomBlock()
{
}


RandomBlock::~RandomBlock()
{
}

bool RandomBlock::init()
{
	if (Sprite::init() == false)
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size s = Size((random() % 20) + 5, (random() % 30) + 10);
	setTextureRect(Rect(0, 0, s.width, s.height));
	setColor(Color3B(0, 0, 0));
	setContentSize(s);
	setPhysicsBody(PhysicsBody::createBox(s));
	getPhysicsBody()->setDynamic(false);
	getPhysicsBody()->setContactTestBitmask(1);
	setPositionX(visibleSize.width);
	scheduleUpdate();
	return true;
}

void RandomBlock::update(float dt)
{
	this->setPositionX(getPositionX() - 4);
	if (getPositionX() < 0)
	{
		unscheduleUpdate();
		removeFromParent();
	}
}
