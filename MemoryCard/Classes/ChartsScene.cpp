#include "ChartsScene.h"



Node * ChartsScene::createChart(int rank, int score)
{
	auto viewSize = Director::getInstance()->getVisibleSize();
	auto row = Node::create();
	auto r = ui::TextAtlas::create(StringUtils::format("%d", rank + 1), "number.png", 63, 83, "0");
	auto s = ui::TextAtlas::create(StringUtils::format("%d", score), "number.png", 63, 83, "0");
	r->setAnchorPoint(Vec2(0, 0.5));
	s->setAnchorPoint(Vec2(1, 0.5));
	r->setPosition(Vec2(30, 0));
	s->setPosition(Vec2(viewSize.width - 30, 0));
	row->addChild(r);
	row->addChild(s);
	row->setContentSize(Size(viewSize.width, 100));
	row->setAnchorPoint(Vec2(0.5, 0.5));

	return row;
}

ChartsScene::ChartsScene(): _background(nullptr), _backBtn(nullptr), _newScoreTitle(nullptr), _newScore(nullptr), _chartScoreTitle(nullptr)
{
}


ChartsScene::~ChartsScene()
{
}

bool ChartsScene::init()
{
	if (Layer::init() == false)
	{
		return false;
	}

	auto viewSize = Director::getInstance()->getVisibleSize();
	_background = Background::create();
	addChild(_background);

	_backBtn = ui::Button::create("back.png");
	_backBtn->setAnchorPoint(Vec2(0, 1));
	_backBtn->setPosition(Vec2(10, viewSize.height - 10));
	addChild(_backBtn);

	_newScoreTitle = Sprite::create("new_score.png");
	_newScoreTitle->setAnchorPoint(Vec2(0, 0.5f));
	_newScoreTitle->setPosition(Vec2(10, viewSize.height - 10));
	addChild(_newScoreTitle);

	_newScore = ui::TextAtlas::create("0", "number.png", 63, 83, "0");
	_newScore->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 + 200));
	auto newScore = UserDefault::getInstance()->getIntegerForKey(NEW_SCORE, 0);
	_newScore->setString(StringUtils::format("%d", newScore));
	addChild(_newScore);

	_chartScoreTitle = Sprite::create("charts_score.png");
	_chartScoreTitle->setAnchorPoint(Vec2(0, 0.5));
	_chartScoreTitle->setPosition(Vec2(10, viewSize.height / 2 + 100));
	addChild(_chartScoreTitle);

	for (int i = 0; i < 5; i++)
	{
		auto score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RANK_SCORE, i).c_str(), 0);
		auto row = createChart(i, score);
		row->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 + 50 - 100 * i));
		addChild(row);
	}

	_backBtn->addClickEventListener([](Ref* ref) {
		SceneMediator::getInstance()->gotoStartScene();
	});
	return true;
}

Scene * ChartsScene::createScene()
{
	auto layer = ChartsScene::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}
