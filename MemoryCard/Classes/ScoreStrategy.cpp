#include "ScoreStrategy.h"

ScoreStrategy::ScoreStrategy(): _continuous(0)
{
}

void ScoreStrategy::execute(ScoreData * score, CardData * cardA, CardData * cardB)
{
	if (cardA->number == cardB->number) {
		_continuous++;
		if (_continuous > score->maxContinuous) {
			score->maxContinuous = _continuous;
		}
		score->score += 100 * _continuous;
		score->energy += 100;
	}
	else if (cardA->flipCount > 0 || cardB->flipCount > 0) {
		score->energy -= 100;
		_continuous = 0;
	}

	cardA->flipCount++;
	cardB->flipCount++;
}
