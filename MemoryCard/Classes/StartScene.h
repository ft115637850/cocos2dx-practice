#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h";
#include "Background.h"
#include "ScoreStrategy.h"
#include "MemoryCardScene.h"
#include "SceneMediator.h"

USING_NS_CC;

class StartScene: public Layer
{
protected:
	Background* _background;
	Sprite* _logo;
	ui::Button* _startBtn;
	ui::Button* _chartBtn;
	ui::Button* _exitBtn;
public:
	StartScene();
	~StartScene();
	CREATE_FUNC(StartScene);
	virtual bool init();
	static Scene* createScene();
};

