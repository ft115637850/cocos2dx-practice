#include "StartScene.h"



StartScene::StartScene(): _background(nullptr), _logo(nullptr), _startBtn(nullptr), _chartBtn(nullptr), _exitBtn(nullptr)
{
}


StartScene::~StartScene()
{
}

bool StartScene::init()
{
	if (Layer::init() == false)
	{
		return false;
	}

	auto viewSize = Director::getInstance()->getVisibleSize();
	_background = Background::create();
	this->addChild(_background);

	_logo = Sprite::create("logo.png");
	_logo->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 + 200));
	this->addChild(_logo);

	_startBtn = ui::Button::create("start.png");
	_startBtn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 - 80));
	this->addChild(_startBtn);
	
	_chartBtn = ui::Button::create("charts.png");
	_chartBtn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 - 200));
	this->addChild(_chartBtn);

	_exitBtn = ui::Button::create("exit.png");
	_exitBtn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 - 320));
	this->addChild(_exitBtn);

	_startBtn->addClickEventListener([](Ref* ref) {
		SceneMediator::getInstance()->gotoGameScene();
	});

	_chartBtn->addClickEventListener([](Ref* ref) {
		SceneMediator::getInstance()->gotoChartsScene();
	});
	
	return true;
}

Scene * StartScene::createScene()
{
	auto layer = StartScene::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}
