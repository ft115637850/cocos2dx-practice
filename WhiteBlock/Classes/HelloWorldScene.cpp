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

    visibleSize = Director::getInstance()->getVisibleSize();
	startGame();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* t, Event* e) {
		for(auto it = WhiteBlock::blocks->begin(); it!= WhiteBlock::blocks->end();it++)
		{
			WhiteBlock* b = *it;
			if (b->getLineIndex() == 1 && b->getBoundingBox().containsPoint(t->getLocation()))
			{
				if (b->getColor() == Color3B::BLACK)
				{
					b->setColor(Color3B::GRAY);
					this->moveDown();
				}
				else if (b->getColor() == Color3B::GREEN)
				{
					this->moveDown();
				}
				else
				{
					MessageBox("Game Over", "Ê§°Ü");
				}
				break;
			}
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::addStartLine()
{
	isEnd = false;
	lineCnt = 0;
	auto b = WhiteBlock::createWithArgs(Color3B::YELLOW, Size(visibleSize.width, visibleSize.height/4), "", 20, Color4B::BLACK);
	addChild(b);
	b->setLineIndex(0);
}

void HelloWorld::addEndLine()
{
	isEnd = true;
	auto b = WhiteBlock::createWithArgs(Color3B::GREEN, visibleSize, "Game Over", 32, Color4B::BLACK);
	addChild(b);
	b->setLineIndex(4);
}

void HelloWorld::addNormalLine(int lineIdx)
{
	WhiteBlock *b;
	int blackIndex = rand() % 4;
	for (int i = 0; i < 4; i++)
	{
		b = WhiteBlock::createWithArgs(blackIndex == i ? Color3B::BLACK : Color3B::WHITE, Size(visibleSize.width / 4 - 1, visibleSize.height / 4 - 1), "", 20, Color4B::BLACK);
		addChild(b);
		b->setPosition(i*visibleSize.width / 4, lineIdx*visibleSize.height / 4);
		b->setLineIndex(lineIdx);
	}
	lineCnt++;
}

void HelloWorld::startGame()
{
	addStartLine();
	addNormalLine(1);
	addNormalLine(2);
	addNormalLine(3);
}

void HelloWorld::moveDown()
{
	if (!isEnd)
	{
		if (lineCnt< 50)
		{
			addNormalLine(4);
		}
		else
		{
			addEndLine();
		}
	}

	for (auto it = WhiteBlock::blocks->begin(); it != WhiteBlock::blocks->end(); it++)
	{
		(*it)->moveDown();
	}
}
