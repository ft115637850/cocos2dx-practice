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

void HelloWorld::changeColor(float dt)
{
	auto sceneLayer = _tileMap->getLayer("scene");
	auto objectGroup = _tileMap->getObjectGroup("obj");
	auto obj = objectGroup->getObject("player");
	log("object props: %s", obj["type"].asString().c_str());

	auto tileSize = _tileMap->getTileSize();
	auto mapSize = _tileMap->getMapSize();

	//visibleSize.width                 actualx
	//----------------------------  =   -
	//tileSize.width*mapSize.width;     x
	auto colorObj = objectGroup->getObject("color");
	auto colorObjX = colorObj["x"].asInt() / 32;
	auto colorObjY = colorObj["y"].asInt() / 32;
	auto colorObjW = colorObj["width"].asInt() / 32;
	auto colorObjH = colorObj["height"].asInt() / 32;
	for (int x = colorObjX; x < colorObjX + colorObjW; x++)
	{
		for (int y = colorObjY; y < colorObjY + colorObjH; y++)
		{
			auto sprite = sceneLayer->getTileAt(Vec2(x, mapSize.height - y));
			sprite->setColor(Color3B(255, 0, 0));
		}
	}
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
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = experimental::TMXTiledMap::create("Tiled/test.tmx");
	_tileMap->setPosition(0, 0);
	addChild(_tileMap);

	auto mapProp = _tileMap->getProperties();
	auto str = mapProp["type"].asString();
	log("map prop: %s", str.c_str());

	auto sceneLayer = _tileMap->getLayer("scene");
	auto layerProp = sceneLayer->getProperties();
	log("layer props: %s", layerProp["type"].asString().c_str());

	auto tileProp = _tileMap->getPropertiesForGID(1).asValueMap();
	log("tile props: %s", tileProp["type"].asString().c_str());

	auto objectGroup = _tileMap->getObjectGroup("obj");
	auto obj = objectGroup->getObject("player");
	log("object props: %s", obj["type"].asString().c_str());

	auto tileSize = _tileMap->getTileSize();
	auto mapSize = _tileMap->getMapSize();

	auto player = Sprite::create("c.png");
	player->setPosition(obj["x"].asFloat(), obj["y"].asFloat());
	addChild(player);

	scheduleOnce(schedule_selector(HelloWorld::changeColor), 1);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this, sceneLayer, mapSize, tileSize, visibleSize, player](Touch* t, Event* e) {
		auto point = this->_tileMap->convertToNodeSpace(t->getLocation());
		point.x = static_cast<int>(point.x / tileSize.width);
		point.y = mapSize.height - static_cast<int>(point.y / tileSize.height) - 1;

		auto tile = sceneLayer->getTileAt(point);
		tile->setColor(Color3B(255, 0, 0));

		auto gid = sceneLayer->getTileGIDAt(point);
		auto p = this->_tileMap->getPropertiesForGID(gid).asValueMap();

		if (p["move"].isNull() != true && p["move"].asBool() == true)
		{
			player->setPosition(tile->getPosition());
		}
		return true;
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
