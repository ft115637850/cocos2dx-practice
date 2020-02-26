#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class ScoreText: public Node
{
protected:
	ui::TextAtlas* _text;
	int _score;
public:
	ScoreText();
	virtual ~ScoreText();
	virtual bool init();
	void updateView(int value);
	CREATE_FUNC(ScoreText);
};

