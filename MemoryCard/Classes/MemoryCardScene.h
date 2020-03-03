#pragma once
#include "cocos2d.h"
#include "ScoreStrategyBase.h"
#include "MemoryCardLevel.h"
#include "Background.h"
#include "EnergyBar.h"
#include "ScoreText.h"
#include "PauseBox.h"
#include "UserData.h"
#include "SceneMediator.h"

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
    ui::Button* _pauseButton;
public:
	MemoryCardScene();
	virtual ~MemoryCardScene();
	static Scene* createScene(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
	static MemoryCardScene* create(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
	bool initWithScoreStrategy(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
	void initLevelDataList();
	void initUI();
	virtual void update(float t);
	void newGame();
	void nextLevel();
};