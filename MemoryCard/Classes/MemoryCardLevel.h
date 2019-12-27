#pragma once
#include "cocos2d.h"
#include <vector>
#include "ICard.h"
#include "LevelData.h"


USING_NS_CC;

class MemoryCardLevel : public Layer
{
private:
	LevelData _levelData;
	std::vector<std::vector<ICard*>> _cardTable;
	int _unfinishedCard;
public:
	MemoryCardLevel();
	virtual ~MemoryCardLevel();
	static MemoryCardLevel* create(LevelData levelData);
	virtual bool initWithLevelData(LevelData levelData);
protected:
	void initCardLaryout();
};

