#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "Background.h"
#include "UserData.h"
#include "SceneMediator.h"


USING_NS_CC;

class ChartsScene: public Layer
{

protected:
	Background* _background;
	ui::Button* _backBtn;
	Sprite* _newScoreTitle;
	ui::TextAtlas* _newScore;
	Sprite* _chartScoreTitle;
	std::vector<Node*> _chartList;
	Node* createChart(int rank, int score);
public:
	ChartsScene();
	~ChartsScene();
	CREATE_FUNC(ChartsScene);
	virtual bool init();
	static Scene* createScene();
};

