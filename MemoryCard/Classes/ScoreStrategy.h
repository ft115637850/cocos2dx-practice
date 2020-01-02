#pragma once

#include "ScoreStrategyBase.h"

class ScoreStrategy : public ScoreStrategyBase
{
private:
	int _continuous;
public:
	ScoreStrategy();
	virtual void execute(ScoreData* score, CardData* cardA, CardData* cardB);
};