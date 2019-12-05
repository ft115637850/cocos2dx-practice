#pragma once
#include "cocos2d.h"

USING_NS_CC;
class ImageFadeOut : public Node
{
protected:
	ClippingNode* _displayImage;
	DrawNode* _displayClipping;
	Image* _image;
	int _pointAMovingDistance;	// the route distance between the point A and the end point
	int _pointBMovingDistance;	// the route distance between the point B and the end point
public:
	ImageFadeOut();
	virtual ~ImageFadeOut();
	static ImageFadeOut* create(std::string image);
	bool initWithImage(std::string image);
	virtual void update(float d);
};

