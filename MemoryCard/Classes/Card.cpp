#include "Card.h"



void Card::flipFromTo(Node * a, Node * b, const std::function<void()>& callback)
{
	if (nullptr == a || nullptr == b) {
		return;
	}

	a->stopAllActions();
	b->stopAllActions();

	a->setVisible(true);
	a->setScaleX(1);

	b->setVisible(false);
	b->setScaleX(0);

	auto flipB = [a, b, callback]() {
		a->setVisible(false);
		b->setVisible(true);

		CallFunc* func = nullptr;
		if (callback != nullptr) {
			func = CallFunc::create(callback);
		}

		b->runAction(Sequence::create(ScaleTo::create(0.25f, 1.0f, 1.0f), func, NULL));
	};
	a->runAction(Sequence::create(ScaleTo::create(0.25f, 0, 1.0f), CallFunc::create(flipB), NULL));
}

Card::Card(): _backImage(nullptr), _frontImage(nullptr), _state(CardState::BACK)
{
	this->setCascadeColorEnabled(true);
}


Card::~Card()
{
	this->removeAllChildren();
}

void Card::flipToBack(const std::function<void()>& callback)
{
	if (_state == CardState::BACK) {
		return;
	}

	flipFromTo(_frontImage, _backImage, callback);
	_state = CardState::BACK;
}

void Card::flipToFront(const std::function<void()>& callback)
{
	if (_state == CardState::FRONT) {
		return;
	}

	flipFromTo(_backImage, _frontImage, callback);
	_state = CardState::FRONT;
}

CardState Card::getCardState() const
{
	return _state;
}

void Card::setCardData(CardData data)
{
	_cardData = data;
}

CardData * Card::getCardData()
{
	return &_cardData;
}

Node* Card::getBackImage() const
{
	return _backImage;
}

void Card::setBackImage(Node *var)
{
	if (nullptr == var) {
		return;
	}

	if (nullptr != _backImage) {
		_backImage->removeFromParent();
	}

	_backImage = var;
	_backImage->setCascadeOpacityEnabled(true);
	addChild(_backImage);
}

Node* Card::getFrontImage() const
{
	return _frontImage;
}

void Card::setFrontImage(Node *var)
{
	if (nullptr == var) {
		return;
	}

	if (nullptr != _frontImage) {
		_frontImage->removeFromParent();
	}

	_frontImage = var;
	_frontImage->setCascadeOpacityEnabled(true);
	_frontImage->setVisible(false);
	addChild(_frontImage);
}