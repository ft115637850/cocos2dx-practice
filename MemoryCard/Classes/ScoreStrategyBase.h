#pragma once
#include "ScoreData.h"
#include "CardData.h"

class ScoreStrategyBase
{
public:
	virtual void execute(ScoreData* score, CardData* cardA, CardData* cardB) = 0;
};