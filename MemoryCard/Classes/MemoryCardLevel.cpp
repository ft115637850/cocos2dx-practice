#include "MemoryCardLevel.h"
#include "CardFactory.h"



MemoryCardLevel::MemoryCardLevel(): _selCardA(nullptr), _selCardB(nullptr), _unfinishedCard(0)
{
	this->setCascadeOpacityEnabled(true);
}

MemoryCardLevel::~MemoryCardLevel()
{
	this->removeAllChildren();
}

MemoryCardLevel * MemoryCardLevel::create(LevelData levelData)
{
	MemoryCardLevel *cl = new MemoryCardLevel();
	if (cl&& cl->initWithLevelData(levelData)) {
		cl->autorelease();
		return cl;
	}

	CC_SAFE_DELETE(cl);
	return nullptr;
}

bool MemoryCardLevel::initWithLevelData(LevelData levelData)
{
	if (Layer::init() == false) {
		return false;
	}

	if ((levelData.rows*levelData.columns) % 2 != 0) {
		return false;
	}

	_levelData = levelData;
	initCardLaryout();
	initTouchEvent();

	return true;
}

void MemoryCardLevel::registerCallfunc(std::function<void(CardData*cardA, CardData*cardB)> pairCallback, std::function<void()> completeCallback)
{
	_pairCallback = pairCallback;
	_completeCallback = completeCallback;
}

void MemoryCardLevel::initCardLaryout()
{
	int backId = CCRANDOM_0_1() * 8;

	for (unsigned int row = 0; row < _levelData.rows; ++row) {
		std::vector<ICard*> r(_levelData.columns);
		_cardTable.push_back(r);
	}

	CardFactory factory;
	Vector<ICard*> cardList;
	unsigned int number = 0;
	for (number = 0; number < _levelData.rows*_levelData.columns; number++) {
		// Create card
		ICard* card = factory.createCard(backId, number / 2);
		cardList.pushBack(card);
	}
	
	this->_unfinishedCard = number;

	for (unsigned int row = 0; row < _levelData.rows; ++row) {
		for (unsigned int column = 0; column < _levelData.columns; ++column) {
			// int idx = CCRANDOM_0_1()*cardList.size();
			// auto card = cardList.at(idx);
			auto card = cardList.getRandomObject();
			cardList.eraseObject(card);
			card->getCardData()->row = row;
			card->getCardData()->column = column;

			// Set card position
			int space = 20;
			auto cardSize = card->getContentSize();
			card->setPosition(Vec2(
				(cardSize.width + space)*column + cardSize.width / 2,
				(cardSize.height + space)*row + cardSize.height / 2
			));
			_cardTable[row][column] = card;
			this->addChild(card);

			if (column == _levelData.columns - 1 && row == _levelData.rows - 1) {
				this->setContentSize(Size(
					(cardSize.width + space)*column + cardSize.width,
					(cardSize.height + space)*row + cardSize.height
				));
			}
		}
	}
}

void MemoryCardLevel::initTouchEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event) {
		Point locationInNode = this->convertToNodeSpace(touch->getLocation());
		Size s = this->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode)) {
			return true;
		}
		return false;
	};

	listener->onTouchEnded = [&](Touch* touch, Event* event) {
		Point locationInNode = this->convertToNodeSpace(touch->getLocation());
		ICard* selCard = nullptr;
		for (unsigned row = 0; row < _levelData.rows; row++) {
			auto cards = _cardTable[row];
			for (unsigned column = 0; column < _levelData.columns; column++) {
				auto card = cards[column];
				if (nullptr == card) {
					continue;
				}

				auto size = card->getContentSize();
				auto pos = card->getPosition();
				auto rect = Rect(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
				if (rect.containsPoint(locationInNode)) {
					selCard = card;
					break;
				}
			}

			if (selCard != nullptr) {
				break;
			}
		}

		if (nullptr == selCard || selCard == _selCardA) {
			return;
		}

		if (nullptr == _selCardA) {
			_selCardA = selCard;
			_selCardA->flipToFront();
		}
		else
		{
			_selCardB = selCard;

			auto dataA = _selCardA->getCardData();
			auto dataB = _selCardB->getCardData();

			if (_pairCallback != nullptr) {
				_pairCallback(dataA, dataB);
			}

			if (dataA->number == dataB->number) {
				// Match successful
				auto cardA = _selCardA;
				auto cardB = _selCardB;
				_selCardB->flipToFront([cardA, cardB]() {
					cardA->runAction(Sequence::create(
						Spawn::create(
							FadeOut::create(0.25),
							ScaleTo::create(0.25, 0.25), NULL),
						CallFunc::create([cardA]() { cardA->removeFromParent(); }),
						NULL));
					cardB->runAction(Sequence::create(
						Spawn::create(
							FadeOut::create(0.25),
							ScaleTo::create(0.25, 0.25), NULL),
						CallFunc::create([cardB]() { cardB->removeFromParent(); }),
						NULL));
				});

				_cardTable[dataA->row][dataA->column] = nullptr;
				_cardTable[dataB->row][dataB->column] = nullptr;
				_selCardA = nullptr;
				_selCardB = nullptr;
				_unfinishedCard -= 2;
				if (_unfinishedCard == 0 && _completeCallback != nullptr) {
					_completeCallback();
				}
			}
			else
			{
				// Match failure
				auto cardA = _selCardA;
				auto cardB = _selCardB;
				_selCardB->flipToFront([cardA, cardB]() {
					cardA->flipToBack();
					cardB->flipToBack();
				});
				_selCardA = nullptr;
				_selCardB = nullptr;
			}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
