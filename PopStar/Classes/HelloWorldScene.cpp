/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

void HelloWorld::createPopTable()
{
	srand(time(NULL));
	_popWidth = (_visibleSize.width - 28) / 10;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			int num = rand() % 5;
			auto p = Pop::createPop(num, _popWidth, _popWidth, _popWidth*i + 20, _popWidth*j + 20 + _visibleSize.height / 5);
			p->xIdx = i;
			p->yIdx = j;
			addChild(p);
			_popTable[i][j] = p;
		}
	}
}

bool HelloWorld::onTouchPop(cocos2d::Touch * t, cocos2d::Event * e)
{
	auto l = t->getLocation();
	if (l.x < 20 || l.x > _popWidth * 10 + 20 || l.y < 20 + _visibleSize.height / 5 || l.y > _popWidth * 10 + 20 + _visibleSize.height / 5)
	{
		return true;
	}

	int i = (l.x - 20) / _popWidth;
	int j = (l.y - 20 - _visibleSize.height / 5) / _popWidth;
	if (i >= 0 && i < 10 && j >= 0 && j < 10)
	{
		auto p = _popTable[i][j];
		log("%d,%d", p->xIdx, p->yIdx);
		if (canBeCleared(p))
		{
			clearPops(p);
			shuffle();
			if (isGameOver())
				Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::create()));
		}
	}
	return true;
}

bool HelloWorld::canBeCleared(Pop * p)
{
	if (p->yIdx + 1 < 10)
	{
		auto upPop = _popTable[p->xIdx][p->yIdx + 1];
		if (p->getNumber() == upPop->getNumber())
			return true;
	}

	if (p->yIdx - 1 >= 0)
	{
		auto downPop = _popTable[p->xIdx][p->yIdx - 1];
		if (p->getNumber() == downPop->getNumber())
			return true;
	}

	if (p->xIdx - 1 >= 0)
	{
		auto leftPop = _popTable[p->xIdx - 1][p->yIdx];
		if (p->getNumber() == leftPop->getNumber())
			return true;
	}

	if (p->xIdx + 1 < 10)
	{
		auto rightPop = _popTable[p->xIdx + 1][p->yIdx];
		if (p->getNumber() == rightPop->getNumber())
			return true;
	}

	return false;
}

bool HelloWorld::isGameOver()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			if (_popTable[i][j]->getNumber() == -1)
				continue;

			if (canBeCleared(_popTable[i][j]))
				return false;
		}

	return true;
}

void HelloWorld::clearPops(Pop * p)
{
	int clearNumber = p->getNumber();
	if (clearNumber == -1)
		return;

	p->setNumber(-1);
	newClearedPops.pushBack(p);
	if (p->yIdx + 1 < 10)
	{
		auto upPop = _popTable[p->xIdx][p->yIdx + 1];
		if (clearNumber == upPop->getNumber())
		{
			clearPops(upPop);
		}
	}

	if (p->yIdx - 1 >= 0)
	{
		auto downPop = _popTable[p->xIdx][p->yIdx - 1];
		if (clearNumber == downPop->getNumber())
			clearPops(downPop);
	}

	if (p->xIdx - 1 >= 0)
	{
		auto leftPop = _popTable[p->xIdx - 1][p->yIdx];
		if (clearNumber == leftPop->getNumber())
			clearPops(leftPop);
	}

	if (p->xIdx + 1 < 10)
	{
		auto rightPop = _popTable[p->xIdx + 1][p->yIdx];
		if (clearNumber == rightPop->getNumber())
			clearPops(rightPop);
	}
}

void HelloWorld::moveBlankToTop(Pop * p)
{
	if (p->yIdx == 9)
		return;

	auto movingPop = p;
	for (int j = p->yIdx + 1; j < 10; j++)
	{
		auto upper = _popTable[p->xIdx][j];
		if (upper->getNumber() == -1)
			continue;

		movingPop->setNumber(upper->getNumber());
		upper->setNumber(-1);
		movingPop = upper;
	}
}

void HelloWorld::shuffle()
{
	std::vector<int> shuffleColumns;
	// Top to Down
	for (auto p : newClearedPops)
	{
		if (shuffleColumns.size() == 0)
		{
			shuffleColumns.push_back(p->xIdx);
		}
		else
		{
			int min = shuffleColumns[shuffleColumns.size() - 1];
			int max = (*shuffleColumns.begin());
			if (p->xIdx != min && p->xIdx != max)
			{
				if (p->xIdx < min)
				{
					shuffleColumns.push_back(p->xIdx);
				}
				else if (p->xIdx > max)
				{
					shuffleColumns.insert(shuffleColumns.begin(), p->xIdx);
				}
			}
		}

		moveBlankToTop(p);
	}

	newClearedPops.clear();

	// Right to Left
	for (int col : shuffleColumns)
	{
		log("check column %d", col);
		if (_popTable[col][0]->getNumber() == -1)
		{
			log("empty column %d", col);
			for (int movingCol = col+1; movingCol < 10; movingCol++)
			{
				if (_popTable[movingCol][0]->getNumber() == -1)
					break;

				for (int moveingRow = 0; moveingRow < 10; moveingRow++)
				{
					_popTable[movingCol - 1][moveingRow]->setNumber(_popTable[movingCol][moveingRow]->getNumber());
					_popTable[movingCol][moveingRow]->setNumber(-1);
				}
			}
		}
	}
	shuffleColumns.clear();
}

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	_visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = LayerColor::create(Color4B(180, 170, 160, 255));
	addChild(bg);
	this->createPopTable();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchPop, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}