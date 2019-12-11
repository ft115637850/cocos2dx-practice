#include "CuttingPhotos.h"


CuttingPhotos::CuttingPhotos():_rows(3),_columns(3)
{
}


CuttingPhotos::~CuttingPhotos()
{
	this->removeAllChildren();
}

CuttingPhotos * CuttingPhotos::create(const char * photo, unsigned int rows, unsigned int columns)
{
	CuttingPhotos *cp = new CuttingPhotos();
	if (cp && cp->initWithPhoto(photo, rows, columns)) {
		cp->autorelease();
		return cp;
	}

	CC_SAFE_DELETE(cp);
	return nullptr;
}

void CuttingPhotos::restart()
{
}

bool CuttingPhotos::initWithPhoto(const char * photo, unsigned int rows, unsigned int columns)
{
	if (Layer::init()) {
		_rows = rows;
		_columns = columns;
		if (initSlices(photo)) {
			return true;
		}
	}
	return false;
}

bool CuttingPhotos::initSlices(const char * photo)
{
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(photo);
	if (texture == nullptr) {
		return false;
	}

	for (int i = 0; i < _rows; i++) {
		std::vector<Sprite*> row;
		for (int j = 0; j < _columns; j++) {
			row.push_back(nullptr);
		}
		_slices.push_back(row);
	}

	auto size = texture->getContentSize();
	_sliceWidth = size.width / _columns;
	_sliceHeight = size.height / _rows;
	this->setContentSize(size);

	auto endSlice = Sprite::createWithTexture(texture, Rect((_columns - 1)*_sliceWidth, (_rows - 1)*_sliceHeight, _sliceWidth, _sliceHeight));
	endSlice->setAnchorPoint(Vec2(0, 0));
	endSlice->setPosition((_columns - 1)*_sliceWidth, 0);
	endSlice->setOpacity(100);
	this->addChild(endSlice);
	_slices[_rows - 1][_columns - 1] = nullptr;

	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _columns; j++) {
			if (i == _rows - 1 && j == _columns - 1) {
				break;
			}

			Sprite *slice = Sprite::createWithTexture(texture, Rect(j*_sliceWidth, i*_sliceHeight, _sliceWidth, _sliceHeight));
			slice->setAnchorPoint(Vec2(0, 0));
			slice->setPosition(j*_sliceWidth, size.height - (i+1)*_sliceHeight);
			this->addChild(slice);
			_slices[i][j] = slice;
		}
	}

	return true;
}

void CuttingPhotos::initTouchEventListener()
{
}

void CuttingPhotos::move(int x, int y)
{
}
