#include "ImageFadeOut.h"



ImageFadeOut::ImageFadeOut() : _pointAMovingDistance(0), _pointBMovingDistance(0)
{
}


ImageFadeOut::~ImageFadeOut()
{
}

ImageFadeOut * ImageFadeOut::create(std::string image)
{
	auto imageFafeOut = new ImageFadeOut();
	if (imageFafeOut == nullptr || imageFafeOut->initWithImage(image) == false) {
		CC_SAFE_DELETE(imageFafeOut);
		return nullptr;
	}
	return imageFafeOut;
}

bool ImageFadeOut::initWithImage(std::string image)
{
	if (Node::init() == false) {
		return false;
	}

	_displayClipping = DrawNode::create();
	auto display = Sprite::create(image);
	display->setAnchorPoint(Vec2(0, 0));
	this->setContentSize(display->getContentSize());

	Vec2 points[4];
	points[0] = Vec2(0, 0);
	points[1] = Vec2(0, _contentSize.height);
	points[2] = _contentSize;
	points[3] = Vec2(_contentSize.width, 0);
	_displayClipping->drawPolygon(points, 4, Color4F(1.0f, 1.0f, 1.0f, 1.0f), 0, Color4F(0, 0, 0, 0));
	_displayClipping->setAnchorPoint(Vec2(0, 0));
	_displayClipping->setContentSize(_contentSize);

	_displayImage = ClippingNode::create(_displayClipping);
	_displayImage->addChild(display);
	addChild(_displayImage);

	this->setAnchorPoint(Vec2(0.5, 0.5));
	_pointAMovingDistance = _pointBMovingDistance = _contentSize.width + _contentSize.height;
	this->scheduleUpdate();
	return true;
}

void ImageFadeOut::update(float d)
{
	const int step = 10;
	_pointAMovingDistance -= step;
	_pointBMovingDistance -= step;
	if (_pointAMovingDistance < 0) {
		this->unscheduleUpdate();
		return;
	}

	// two point
	Vec2 pointA(
		_pointAMovingDistance > _contentSize.width ? 0 : _contentSize.width - _pointAMovingDistance,
		_pointAMovingDistance > _contentSize.width ? _contentSize.height - (_pointAMovingDistance - _contentSize.width) : _contentSize.height
	);
	Vec2 pointB(
		_pointBMovingDistance > _contentSize.height ? _contentSize.width - (_pointBMovingDistance - _contentSize.height) : _contentSize.width,
		_pointBMovingDistance > _contentSize.height ? 0 : _contentSize.height - _pointBMovingDistance
	);

	// clipping points
	Vec2 points[5];
	int pointCnt = 0;
	if (_pointAMovingDistance > _contentSize.width) {
		points[pointCnt++] = pointA;
		points[pointCnt++] = Vec2(0, _contentSize.height);
		points[pointCnt++] = _contentSize;
	}
	else {
		points[pointCnt++] = pointA;
		points[pointCnt++] = _contentSize;
	}

	if (_pointBMovingDistance > _contentSize.height) {
		points[pointCnt++] = Vec2(_contentSize.width, 0);
		points[pointCnt++] = pointB;
	}
	else {
		points[pointCnt++] = pointB;
	}

	_displayClipping->clear();
	_displayClipping->drawPolygon(points, pointCnt, Color4F(200.0f, 100.0f, 1.0f, 1.0f), 0, Color4F(0, 0, 0, 0));
}
