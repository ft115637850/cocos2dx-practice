#include "MemoryCardScene.h"

MemoryCardScene::MemoryCardScene() :_scoreData({}), _nowLevelLayer(nullptr)
{
	_scoreData.energy = 1000;
}

MemoryCardScene::~MemoryCardScene()
{
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

	_scoreStrategy = scoreStrategy;
	newGame();
	return true;
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
	auto level = _nowLevelLayer = MemoryCardLevel::create(data);
	auto levelSize = level->getContentSize();
	level->setAnchorPoint(Vec2(0.5, 0.5));
	level->ignoreAnchorPointForPosition(false);
	level->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto scale = visibleSize.height / (levelSize.height + 40);
	level->setScale(scale);
	level->registerCallfunc([this](CardData* cardA, CardData* cardB) {
		_scoreStrategy->execute(&_scoreData, cardA, cardB);
		CCLOG("Score:%d, Energy:%d, maxContinuous:%d", _scoreData.score, _scoreData.energy, _scoreData.maxContinuous);
	}, []() {
		CCLOG("Complete");
	});
	this->addChild(level);
}
