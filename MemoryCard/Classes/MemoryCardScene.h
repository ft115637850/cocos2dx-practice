#pragma once
#include "cocos2d.h"
#include "ScoreStrategyBase.h"
#include "MemoryCardLevel.h"
#include "Background.h"
#include "EnergyBar.h"
#include "ScoreText.h"

USING_NS_CC;

class MemoryCardScene : public Layer {
protected:
	int _nowLevel;
	int _allLevel;
	std::vector<LevelData> _levelDataList;
	LevelData _nowLevelData;
	MemoryCardLevel* _nowLevelLayer;
	std::shared_ptr<ScoreStrategyBase> _scoreStrategy;
	ScoreData _scoreData;
	Background* _background;
	EnergyBar* _energybar;
	ScoreText* _scoreText;
public:
	MemoryCardScene();
	virtual ~MemoryCardScene();
	static Scene* createScene(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
	static MemoryCardScene* create(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
	bool initWithScoreStrategy(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
	void initLevelDataList();
	virtual void update(float t);
	void newGame();
	void nextLevel();
};