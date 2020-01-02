#pragma once
#include "cocos2d.h"
#include "ScoreStrategyBase.h"
#include "MemoryCardLevel.h"

USING_NS_CC;

class MemoryCardScene : public Layer {
protected:
	MemoryCardLevel* _nowLevelLayer;
	std::shared_ptr<ScoreStrategyBase> _scoreStrategy;
	ScoreData _scoreData;
public:
	MemoryCardScene();
	virtual ~MemoryCardScene();
	static Scene* createScene(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
	static MemoryCardScene* create(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
	bool initWithScoreStrategy(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
	virtual void newGame();
};