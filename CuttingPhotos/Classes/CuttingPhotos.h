#pragma once
#include "cocos2d.h"

USING_NS_CC;

class CuttingPhotos : public Layer
{
public:
	CuttingPhotos();
	virtual ~CuttingPhotos();
	static CuttingPhotos* create(const char* photo, unsigned int rows=3, unsigned int columns=3);
	void restart();
private:
	unsigned int _rows;
	unsigned int _columns;
	unsigned int _sliceWidth;
	unsigned int _sliceHeight;
	std::vector<std::vector<Sprite*>> _slices;
	bool initWithPhoto(const char* photo, unsigned int rows, unsigned int columns);
	bool initSlices(const char* photo);
	void initTouchEventListener();
	void move(int x, int y);
};

