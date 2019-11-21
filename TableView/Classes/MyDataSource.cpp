#include "MyDataSource.h"

USING_NS_CC;

bool MyDataSource::init()
{
	return true;
}

Size MyDataSource::cellSizeForTable(TableView * table)
{
	return Size(300, 50);
}

TableViewCell * MyDataSource::tableCellAtIndex(TableView * table, ssize_t idx)
{
	TableViewCell *cell = table->dequeueCell();
	LabelTTF *label;
	if (cell == NULL) {
		cell = TableViewCell::create();
		label = LabelTTF::create();
		label->setFontSize(30);
		label->setAnchorPoint(Point(0, 0));
		label->setTag(0);
		cell->addChild(label);
	}
	else {
		label = (LabelTTF*)cell->getChildByTag(0);
	}

	label->setString(StringUtils::format("Label %ld", idx));

	return cell;
}

ssize_t MyDataSource::numberOfCellsInTableView(TableView * table)
{
	return 100;
}
