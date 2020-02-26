#include "EnergyBar.h"



EnergyBar::EnergyBar() : _percentage(0)
{
}


EnergyBar::~EnergyBar()
{

}

bool EnergyBar::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	_progress = ProgressTimer::create(Sprite::create("energy_front.png"));
	_progress->setType(cocos2d::ProgressTimer::Type::BAR);
	_progress->setMidpoint(Vec2(0, 0));
	_progress->setBarChangeRate(Vec2(1, 0));

	_background = Sprite::create("energy_back.png");
	this->addChild(_background);
	this->addChild(_progress);
	this->setContentSize(_background->getContentSize());
	updateView(1000.0f);
	return true;
}

void EnergyBar::updateView(int value)
{
	auto percentage = value / 1000.0f*100.f;
	// _progress->setPercentage(percentage);
	if (abs(percentage - _percentage) > 1.0f)
	{
		_progress->runAction(EaseBackOut::create(ProgressTo::create(0.25f, percentage)));
		_percentage = percentage;
	}	
}
