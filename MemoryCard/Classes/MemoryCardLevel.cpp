#include "MemoryCardLevel.h"
#include "CardFactory.h"



MemoryCardLevel::MemoryCardLevel()
{
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
	return true;
}

void MemoryCardLevel::initCardLaryout()
{
	int backId = CCRANDOM_0_1() * 8;

	for (int row = 0; row < _levelData.rows; ++row) {
		std::vector<ICard*> r(_levelData.columns);
		_cardTable.push_back(r);
	}

	CardFactory factory;
	int number = 0;
	for (int row = 0; row < _levelData.rows; ++row) {
		for (int column = 0; column < _levelData.columns; ++column) {
			// Create card
			ICard* card = factory.createCard(backId, number / 2);
			card->getCardData()->row = row;
			card->getCardData()->column = column;
			number++;

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
	this->_unfinishedCard = number;
}
