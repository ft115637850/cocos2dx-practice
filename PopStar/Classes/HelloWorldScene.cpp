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