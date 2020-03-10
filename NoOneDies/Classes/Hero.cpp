#include "Hero.h"

USING_NS_CC;

Hero::Hero()
{
}


Hero::~Hero()
{
}

bool Hero::init()
{
	if (Sprite::init() == false)
	{
		return false;
	}
	
	Size s = Size(44, 52);
	setContentSize(s);
	setAnchorPoint(Vec2(0, 0));
	setPhysicsBody(PhysicsBody::createBox(s));
	getPhysicsBody()->setRotationEnable(false);
	getPhysicsBody()->setContactTestBitmask(1);
	runAction(RepeatForever::create(FlashTool::readJsonSpriteSheet("Hero.json", 0.2f)));

	return true;
}
