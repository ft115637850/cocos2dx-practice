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

#define RED_BIT_MASK	0b1000
#define GREEN_BIT_MASK	0b0100
#define BLUE_BIT_MASK	0b0010
#define EDGE_BIT_MASK	0b0001

void HelloWorld::onEnter()
{
	Scene::onEnter();
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0, -1000));
	auto bounds = Node::create();
	bounds->setContentSize(visibleSize);
	bounds->setPhysicsBody(PhysicsBody::createEdgeBox(bounds->getContentSize()));
	bounds->getPhysicsBody()->setContactTestBitmask(EDGE_BIT_MASK);
	addChild(bounds);
	this->addBox(Vec2(visibleSize.width / 2, visibleSize.height / 2));
}

void HelloWorld::addBox(Vec2 & position)
{
	auto r = Sprite::create();
	r->setTextureRect(Rect(0, 0, 50, 50));
	auto physicsBody = PhysicsBody::createBox(r->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	//physicsBody->setGravityEnable(false);
	/*physicsBody->setVelocity(Vec2(cocos2d::random(-500, 500),
	cocos2d::random(-500, 500)));*/

	r->addComponent(physicsBody);
	r->setPosition(position);
	switch (rand()%3)
	{
	case 0:
		r->setColor(Color3B(255, 0, 0));
		r->getPhysicsBody()->setContactTestBitmask(RED_BIT_MASK);
		break;
	case 1:
		r->setColor(Color3B(0, 255, 0));
		r->getPhysicsBody()->setContactTestBitmask(GREEN_BIT_MASK);
		break;
	case 2:
		r->setColor(Color3B(0, 0, 255));
		r->getPhysicsBody()->setContactTestBitmask(BLUE_BIT_MASK);
		break;
	default:
		break;
	}

	addChild(r);
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
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch* t, Event* e) {
		this->addBox(t->getLocation());
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [](PhysicsContact& contact) {
		switch (contact.getShapeA()->getBody()->getContactTestBitmask() |
			contact.getShapeB()->getBody()->getContactTestBitmask())
		{
		case RED_BIT_MASK| RED_BIT_MASK:
			log("red contact red");
			break;
		case RED_BIT_MASK | GREEN_BIT_MASK:
			log("red contact green");
			break;
		case RED_BIT_MASK | BLUE_BIT_MASK:
			log("red contact blue");
			break;
		case RED_BIT_MASK | EDGE_BIT_MASK:
			log("red contact edge");
			break;
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}

