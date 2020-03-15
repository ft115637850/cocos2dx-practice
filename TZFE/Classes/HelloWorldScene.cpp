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

 bool HelloWorld::onTouchBegan(cocos2d::Touch * t, cocos2d::Event * e)
 {
	 auto l = t->getLocation();
	 _firstX = l.x;
	 _firstY = l.y;
	 return true;
 }

 void HelloWorld::onTouchEnded(cocos2d::Touch * t, cocos2d::Event * e)
 {
	 auto l = t->getLocation();
	 auto distanceX = l.x - _firstX;
	 auto distanceY = l.y - _firstY;
	 bool hasMoved = false;
	 if (abs(distanceX) > abs(distanceY))
	 {
		 if (distanceX > 5)
		 {
			 log("moving right");
			 moveCardsToRight();
			 hasMoved = true;
			 
		 }
		 else if (distanceX < -5)
		 {
			 log("moving left");
			 moveCardsToLeft();
			 hasMoved = true;
		 }
	 }
	 else
	 {
		 if (distanceY > 5)
		 {
			 log("moving top");
			 moveCardsUp();
			 hasMoved = true;
		 }
		 else if (distanceY < -5)
		 {
			 log("moving down");
			 moveCardsDown();
			 hasMoved = true;
		 }
	 }

	 if (hasMoved)
	 {
		 if (isGameOver())
			 Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
		 else if (_cardCount < 4 * 4)
			 generateNewCards();
	 }

	 log("total cards: %d", _cardCount);
 }

 void HelloWorld::createCards()
 {
	 int cardWdith = (_visibleSize.width - 28) / 4;
	 for (int row = 0; row < 4; row++)
	 {
		 for (int col = 0; col < 4; col++)
		 {
			 CardSprite* card = CardSprite::createCard(0, cardWdith, cardWdith, cardWdith*col + 20, cardWdith*row + 20 + _visibleSize.height / 6);
			 addChild(card);
			 _cardsTable[row][col] = card;
		 }
	 }
 }

 void HelloWorld::moveCardsToLeft()
 {
	 for (int row = 0; row < 4; row++)
	 {
		 for (int col = 0; col < 3; col++)
		 {
			 for (int nextCol = col + 1; nextCol < 4; nextCol++)
			 {
				 if (_cardsTable[row][nextCol]->getNumber() > 0)
				 {
					 if (_cardsTable[row][col]->getNumber() <= 0)
					 { 
						 _cardsTable[row][col]->setNumber(_cardsTable[row][nextCol]->getNumber());
						 _cardsTable[row][nextCol]->setNumber(0);
						 col--;
					 }
					 else if (_cardsTable[row][col]->getNumber() == _cardsTable[row][nextCol]->getNumber())
					 {
						 _cardsTable[row][col]->setNumber(_cardsTable[row][nextCol]->getNumber() * 2);
						 _cardsTable[row][nextCol]->setNumber(0);
						 _score += _cardsTable[row][col]->getNumber();
						 _scoreDisplay->setString(StringUtils::format("%d", _score));
						 _cardCount--;
					 }
					 break;
				 }
			 }
		 }
	 }
 }

 void HelloWorld::moveCardsToRight()
 {
	 for (int row = 0; row < 4; row++)
	 {
		 for (int col = 3; col >= 0; col--)
		 {
			 for (int nextCol = col - 1; nextCol >= 0; nextCol--)
			 {
				 if (_cardsTable[row][nextCol]->getNumber() > 0)
				 {
					 if (_cardsTable[row][col]->getNumber() <= 0)
					 {
						 _cardsTable[row][col]->setNumber(_cardsTable[row][nextCol]->getNumber());
						 _cardsTable[row][nextCol]->setNumber(0);
						 col++;
					 }
					 else if (_cardsTable[row][col]->getNumber() == _cardsTable[row][nextCol]->getNumber())
					 {
						 _cardsTable[row][col]->setNumber(_cardsTable[row][nextCol]->getNumber() * 2);
						 _cardsTable[row][nextCol]->setNumber(0);
						 _score += _cardsTable[row][col]->getNumber();
						 _scoreDisplay->setString(StringUtils::format("%d", _score));
						 _cardCount--;
					 }
					 break;
				 }
			 }
		 }
	 }
 }

 void HelloWorld::moveCardsUp()
 {
	 for (int col = 0; col < 4; col++)
	 {
		 for (int row = 3; row >= 0; row--)
		 {
			 for (int nextRow = row - 1; nextRow >= 0; nextRow--)
			 {
				 if (_cardsTable[nextRow][col]->getNumber() > 0)
				 {
					 if (_cardsTable[row][col]->getNumber() <= 0)
					 {
						 _cardsTable[row][col]->setNumber(_cardsTable[nextRow][col]->getNumber());
						 _cardsTable[nextRow][col]->setNumber(0);
						 row++;
					 }
					 else if (_cardsTable[row][col]->getNumber() == _cardsTable[nextRow][col]->getNumber())
					 {
						 _cardsTable[row][col]->setNumber(_cardsTable[row][col]->getNumber() * 2);
						 _cardsTable[nextRow][col]->setNumber(0);
						 _score += _cardsTable[row][col]->getNumber();
						 _scoreDisplay->setString(StringUtils::format("%d", _score));
						 _cardCount--;
					 }
					 break;
				 }
			 }
		 }
	 }
 }

 void HelloWorld::moveCardsDown()
 {
	 for (int col = 0; col < 4; col++)
	 {
		 for (int row = 0; row < 3; row++)
		 {
			 for (int nextRow = row + 1; nextRow < 4; nextRow++)
			 {
				 if (_cardsTable[nextRow][col]->getNumber() > 0)
				 {
					 if (_cardsTable[row][col]->getNumber() <= 0)
					 {
						 _cardsTable[row][col]->setNumber(_cardsTable[nextRow][col]->getNumber());
						 _cardsTable[nextRow][col]->setNumber(0);
						 row--;
					 }
					 else if (_cardsTable[row][col]->getNumber() == _cardsTable[nextRow][col]->getNumber())
					 {
						 _cardsTable[row][col]->setNumber(_cardsTable[row][col]->getNumber() * 2);
						 _cardsTable[nextRow][col]->setNumber(0);
						 _score += _cardsTable[row][col]->getNumber();
						 _scoreDisplay->setString(StringUtils::format("%d", _score));
						 _cardCount--;
					 }
					 break;
				 }
			 }
		 }
	 }
 }

 void HelloWorld::generateNewCards()
 {
	 int i = CCRANDOM_0_1() * 4;
	 int j = CCRANDOM_0_1() * 4;
	 if (_cardsTable[i][j]->getNumber() > 0) {
		 generateNewCards();
	 }
	 else {
		 _cardsTable[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
		 _cardCount++;
	 }
 }

 bool HelloWorld::isGameOver()
 {
	 if (_cardCount < 4 * 4)
	 {
		 return false;
	 }

	 for (int i = 0; i < 4; i++)
		 for (int j = 0; j < 4; j++)
		 {
			 int num = _cardsTable[i][j]->getNumber();
			 if ((i + 1 < 4 && _cardsTable[i + 1][j]->getNumber() == num) ||
				 (i - 1 >= 0 && _cardsTable[i - 1][j]->getNumber() == num) ||
				 (j + 1 < 4 && _cardsTable[i][j + 1]->getNumber() == num) ||
				 (j - 1 >= 0 && _cardsTable[i][j - 1]->getNumber() == num))
				 return false;
		 }

	 return true;
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
	srand(time(NULL));
	_cardCount = 0;
	_score = 0;
	_visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	auto bg = LayerColor::create(Color4B(180, 170, 160, 255));
	addChild(bg);
	_scoreTitle = LabelTTF::create("Score:", "HirakakuProN-W6", 40);
	_scoreTitle->setPosition(_visibleSize.width / 5, _visibleSize.height - 150);
	addChild(_scoreTitle);
	_scoreDisplay = LabelTTF::create("0", "HirakakuProN-W6", 40);
	_scoreDisplay->setPosition(_visibleSize.width / 2, _visibleSize.height - 150);
	addChild(_scoreDisplay);
	createCards();
	generateNewCards();
	generateNewCards();
    return true;
}