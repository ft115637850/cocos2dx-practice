#ifndef  _MY_DATASOURCE_H_
#define  _MY_DATASOURCE_H_
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MyDataSource : public TableViewDataSource, public Object
{
public:
	bool init();
	CREATE_FUNC(MyDataSource);
public:
	/**
	* cell height for a given table.
	*
	* @param table table to hold the instances of Class
	* @return cell size
	*/
	virtual Size cellSizeForTable(TableView *table);
	/**
	* a cell instance at a given index
	*
	* @param idx index to search for a cell
	* @return cell found at idx
	*/
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	/**
	* Returns number of cells in a given table view.
	*
	* @return number of cells
	*/
	virtual ssize_t numberOfCellsInTableView(TableView *table);
};

#endif // _MY_DATASOURCE_H_