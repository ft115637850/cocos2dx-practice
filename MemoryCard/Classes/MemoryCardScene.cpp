#include "MemoryCardScene.h"

MemoryCardScene::MemoryCardScene() :_scoreData({}), _nowLevelLayer(nullptr)
{
	_scoreData.energy = 1000;
}

MemoryCardScene::~MemoryCardScene()
{
	this->unscheduleUpdate();
}

Scene * MemoryCardScene::createScene(std::shared_ptr<ScoreStrategyBase> scoreStrategy)
{
	auto scene = Scene::create();
	auto layer = MemoryCardScene::create(scoreStrategy);
	scene->addChild(layer);
	return scene;
}

MemoryCardScene * MemoryCardScene::create(std::shared_ptr<ScoreStrategyBase> scoreStrategy)
{
	MemoryCardScene* scene = new MemoryCardScene();
	if (scene && scene->initWithScoreStrategy(scoreStrategy)) {
		scene->autorelease();
		return scene;
	}

	CC_SAFE_DELETE(scene);
	return nullptr;
}

bool MemoryCardScene::initWithScoreStrategy(std::shared_ptr<ScoreStrategyBase> scoreStrategy)
{
	if (Layer::init() == false) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	_scoreStrategy = scoreStrategy;
	_background = Background::create();
	this->addChild(_background);
	_energybar = EnergyBar::create();
	_energybar->setPosition(visibleSize.width / 2, visibleSize.height - 40.0f);
	this->addChild(_energybar);
	_scoreText = ScoreText::create();
	_scoreText->setPosition(visibleSize.width - 20, visibleSize.height - 33);
	_scoreText->setScale(0.75);
	this->addChild(_scoreText);
	newGame();
	this->scheduleUpdate();
	return true;
}

void MemoryCardScene::update(float t)
{
	Layer::update(t);
	_scoreData.energy -= this->_nowLevelData.loss*t;
	if (_scoreData.energy > 1000)
	{
		_scoreData.energy = 1000;
	}
	else if (_scoreData.energy < 0)
	{
		_scoreData.energy = 0;
	}

	_energybar->updateView(_scoreData.energy);
	_scoreText->updateView(_scoreData.score);
}

void MemoryCardScene::newGame()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*CardFactory fac;
	auto card = fac.createCard(5, 3);
	card->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	addChild(card);
	card->flipToFront();*/
	LevelData data = {};
	data.rows = 4;
	data.columns = 3;
	data.loss = 5;
	_nowLevelData = data;
	auto level = _nowLevelLayer = MemoryCardLevel::create(data);
	auto levelSize = level->getContentSize();
	level->setAnchorPoint(Vec2(0.5, 0.5));
	level->ignoreAnchorPointForPosition(false);
	level->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto scale = visibleSize.height / (levelSize.height + 200);
	level->setScale(scale);
	level->setPositionY(level->getPositionY() - 60 * scale);

	level->registerCallfunc([this](CardData* cardA, CardData* cardB) {
		_scoreStrategy->execute(&_scoreData, cardA, cardB);
		CCLOG("Score:%d, Energy:%d, maxContinuous:%d", _scoreData.score, _scoreData.energy, _scoreData.maxContinuous);
	}, []() {
		CCLOG("Complete");
	});
	this->addChild(level);
}
