#pragma once
#include "cocos2d.h"
#include "ChartsScene.h"
#include "StartScene.h"
#include "MemoryCardScene.h"
#include "ScoreStrategy.h"

USING_NS_CC;

class SceneMediator
{
protected:
	static SceneMediator* _instance;

public:
	static SceneMediator* getInstance();
	void gotoStartScene();
	void gotoGameScene();
	void gotoChartsScene();
};

