#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class PauseBox: public Layer
{
protected:
	std::function<void()> _continueCallback;
	std::function<void()> _endGameCallback;
public:
	PauseBox();
	virtual ~PauseBox();
	CREATE_FUNC(PauseBox);
	virtual bool init();
	virtual void registerCallback(std::function<void()> continueCallback, std::function<void()> endGameCallback);
};

