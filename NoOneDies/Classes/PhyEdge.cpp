#include "PhyEdge.h"

USING_NS_CC;

PhyEdge::PhyEdge()
{
}


PhyEdge::~PhyEdge()
{
}

bool PhyEdge::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	setContentSize(visibleSize);
	setPhysicsBody(PhysicsBody::createEdgeBox(visibleSize));

	return true;
}
