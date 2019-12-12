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

bool CuttingPhotos::initWithPhoto(const char * photo, unsigned int rows, unsigned int columns)
{
	if (Layer::init()) {
		_rows = rows;
		_columns = columns;
		if (initSlices(photo)) {
			initTouchEventListener();
			restart();
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
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* t, Event* e) {
		auto locInNode = this->convertToNodeSpace(t->getLocation());
		auto layoutSize = this->getContentSize();
		Rect layout = Rect(0, 0, layoutSize.width, layoutSize.height);
		if (layout.containsPoint(locInNode)) {
			return true;
		}
		else {
			return false;
		}
	};

	listener->onTouchEnded = [&](Touch* t, Event* e) {
		auto locInNode = this->convertToNodeSpace(t->getLocation());
		int x = _rows - static_cast<int>(floor(locInNode.y / this->_sliceHeight)) - 1;
		int y = static_cast<int>(floor(locInNode.x / this->_sliceWidth));
		this->move(x, y, false);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void CuttingPhotos::move(int x, int y, bool isStarting)
{
	auto currentSlice = this->_slices[x][y];
	if (currentSlice == nullptr) {
		return;
	}

	Point targetPosition;
	if (x < _rows - 1 && _slices[x + 1][y] == nullptr) {
		targetPosition.x = x + 1;
		targetPosition.y = y;
	}
	else if (x > 0 && _slices[x - 1][y] == nullptr) {
		targetPosition.x = x - 1;
		targetPosition.y = y;
	}
	else if (y < _columns - 1 && _slices[x][y + 1] == nullptr) {
		targetPosition.x = x;
		targetPosition.y = y + 1;
	}
	else if (y > 0 && _slices[x][y - 1] == nullptr) {
		targetPosition.x = x;
		targetPosition.y = y - 1;
	}
	else {
		return;
	}

	if (isStarting) {
		currentSlice->setPosition(targetPosition.y* _sliceWidth, (_rows - targetPosition.x - 1)*_sliceHeight);
	}
	else {
		currentSlice->runAction(MoveTo::create(0.25f, Vec2(targetPosition.y* _sliceWidth, (_rows - targetPosition.x - 1)*_sliceHeight)));
	}
	
	_slices[x][y] = nullptr;
	_slices[targetPosition.x][targetPosition.y] = currentSlice;
}

bool CuttingPhotos::isMovableSlice(int x, int y) {
	if (x < _rows - 1 && _slices[x + 1][y] == nullptr) {
		return true;
	}
	else if (x > 0 && _slices[x - 1][y] == nullptr) {
		return true;
	}
	else if (y < _columns - 1 && _slices[x][y + 1] == nullptr) {
		return true;
	}
	else if (y > 0 && _slices[x][y - 1] == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

std::vector<Point> CuttingPhotos::findAllMovableSlices()
{
	std::vector<Point> list;
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _columns; j++) {
			if (i == _rows - 1 && j == _columns - 1) {
				break;
			}
			if (isMovableSlice(i, j)) {
				list.push_back(Point(i, j));
			}
		}
	}
	return list;
}

void CuttingPhotos::restart()
{
	/* The code below could generate slices that can never recover
	*
	*
	Vector<Sprite*> list;
	for (int i = 0; i < _rows; i++) {
	for (int j = 0; j < _columns; j++) {
	auto slice = _slices[i][j];
	if (slice != nullptr) {
	list.pushBack(slice);
	}
	}
	}

	for (int i = 0; i < _rows; i++) {
	for (int j = 0; j < _columns; j++) {
	if (i == _rows - 1 && j == _columns - 1) {
	break;
	}

	auto length = list.size();
	auto randIdx = static_cast<int>(CCRANDOM_0_1()*length);
	auto slice = list.at(randIdx);
	_slices[i][j] = slice;
	list.erase(randIdx);
	slice->setPosition(j* _sliceWidth, (_rows - i - 1)*_sliceHeight);
	}
	}*/
	
	unsigned int shiftCount = 30;
	for (unsigned int idx = 0; idx < shiftCount; idx++) {
		auto lst = findAllMovableSlices();
		auto length = lst.size();
		auto randIdx = static_cast<int>(CCRANDOM_0_1()*length);
		auto slice = lst.at(randIdx);
		move(slice.x, slice.y, true);
	}
}
