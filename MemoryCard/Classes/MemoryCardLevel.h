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
	unsigned int _unfinishedCard;
	ICard* _selCardA;
	ICard* _selCardB;
	std::function<void(CardData* cardA, CardData* cardB)> _pairCallback;
	std::function<void()> _completeCallback;
public:
	MemoryCardLevel();
	virtual ~MemoryCardLevel();
	static MemoryCardLevel* create(LevelData levelData);
	virtual bool initWithLevelData(LevelData levelData);
	void registerCallfunc(std::function<void(CardData* cardA, CardData* cardB)> pairCallback, 
		std::function<void()> completeCallback);
protected:
	void initCardLaryout();
	void initTouchEvent();
};

