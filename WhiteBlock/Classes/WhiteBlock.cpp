#include "WhiteBlock.h"

USING_NS_CC;

Vector<WhiteBlock*> * WhiteBlock::blocks = new Vector<WhiteBlock*>();

bool WhiteBlock::initWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor)
{
	Sprite::init();
	visibleSize = Director::getInstance()->getVisibleSize();
	setContentSize(size);
	setAnchorPoint(Point::ZERO);
	setTextureRect(Rect(0, 0, size.width, size.height));
	setColor(color);

	auto l = Label::create();
	l->setString(label);
	l->setSystemFontSize(fontSize);
	l->setTextColor(textColor);
	addChild(l);
	l->setPosition(size.width / 2, size.height / 2);
	return true;
}

WhiteBlock * WhiteBlock::createWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor)
{
	auto b = new WhiteBlock();
	b->initWithArgs(color, size, label, fontSize, textColor);
	b->autorelease();
	blocks->pushBack(b);
	return b;
}

void WhiteBlock::removeBlock()
{
	auto c = getColor();
	log("remove color (%d,%d,%d)", c.r, c.g, c.b);
	removeFromParent();
	blocks->eraseObject(this);
}

void WhiteBlock::setLineIndex(int v)
{
	this->lineIndex = v;
}

int WhiteBlock::getLineIndex()
{
	return this->lineIndex;
}

void WhiteBlock::moveDown()
{
	this->lineIndex--;
	runAction(Sequence::create(MoveTo::create(0.1f, Point(getPositionX(), lineIndex * visibleSize.height / 4)),
		CallFunc::create([this]() {
			if (lineIndex < 0)
			{
				this->removeBlock();
			}
		}),
		NULL));
}
