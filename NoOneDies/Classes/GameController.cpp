#include "GameController.h"

USING_NS_CC;

void GameController::resetFrameCount()
{
	currentFrameIdx = 0;
	nextFrameCount = rand() % 120 + 100;
}

void GameController::addBlock()
{
	auto block = RandomBlock::create();
	block->setPositionY(block->getContentSize().height / 2 + _positionY);
	_layer->addChild(block);
}

bool GameController::init(cocos2d::Layer * layer, float positionY)
{
	_layer = layer;
	_positionY = positionY;
	auto visibleSize = Director::getInstance()->getVisibleSize();

	edge = PhyEdge::create();
	edge->setPositionY(positionY);
	edge->setContentSize(visibleSize);
	_layer->addChild(edge);

	auto ground = Sprite::create();
	ground->setColor(Color3B(0, 0, 0));
	ground->setTextureRect(Rect(0, 0, visibleSize.width, 3));
	/*ground->setContentSize(Size(visibleSize.width, 3));*/
	ground->setPosition(visibleSize.width / 2, 1.5 + positionY);
	_layer->addChild(ground);

	hero = Hero::create();
	hero->setPosition(50, hero->getContentSize().height/2 + positionY);
	_layer->addChild(hero);

	resetFrameCount();
	return true;
}

void GameController::onUpdate()
{
	currentFrameIdx++;
	if (currentFrameIdx >= nextFrameCount)
	{
		resetFrameCount();
		addBlock();
	}
}

bool GameController::histTestPoint(Vec2 point)
{
	return edge->getBoundingBox().containsPoint(point);
}

void GameController::onUsrTouch()
{
	hero->getPhysicsBody()->setVelocity(Vec2(0, 400));
}

GameController * GameController::create(cocos2d::Layer * layer, float positionY)
{
	auto _ins = new GameController();
	_ins->init(layer, positionY);
	_ins->autorelease();
	return _ins;
}
