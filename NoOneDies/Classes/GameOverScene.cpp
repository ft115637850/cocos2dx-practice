#include "GameOverScene.h"

USING_NS_CC;

bool GameOverScene::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	LayerColor::initWithColor(Color4B::WHITE);
	auto label = Label::create();
	label->setString("Game Over");
	label->setSystemFontSize(40);
	label->setColor(Color3B::BLACK);
	label->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(label);
	return true;
}

cocos2d::Scene * GameOverScene::createScene()
{
	auto s = Scene::create();
	auto l = GameOverScene::create();
	s->addChild(l);
	return s;
}
