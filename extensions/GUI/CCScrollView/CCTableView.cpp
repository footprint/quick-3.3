/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2010 Sangwoo Im

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCTableView.h"
#include "CCTableViewCell.h"

NS_CC_EXT_BEGIN

TableView* TableView::create()
{
    return TableView::create(nullptr, Size::ZERO);
}

TableView* TableView::create(TableViewDataSource* dataSource, Size size)
{
    return TableView::create(dataSource, size, nullptr);
}

TableView* TableView::create(TableViewDataSource* dataSource, Size size, Node *container)
{
    TableView *table = new (std::nothrow) TableView();
    table->initWithViewSize(size, container);
    table->autorelease();
    table->setDataSource(dataSource);
    table->_updateCellPositions();
    table->_updateContentSize();

    return table;
}

bool TableView::initWithViewSize(Size size, Node* container/* = nullptr*/)
{
    if (ScrollView::initWithViewSize(size,container))
    {
        CC_SAFE_DELETE(_indices);
        _indices        = new std::set<ssize_t>();
        _vordering      = VerticalFillOrder::BOTTOM_UP;
        this->setDirection(Direction::VERTICAL);

        ScrollView::setDelegate(this);
        return true;
    }
    return false;
}

TableView::TableView()
: _touchedCell(nullptr)
, _indices(nullptr)
, _dataSource(nullptr)
, _tableViewDelegate(nullptr)
, _oldDirection(Direction::NONE)
, _isUsedCellsDirty(false)
{

}

TableView::~TableView()
{
    CC_SAFE_DELETE(_indices);
}

void TableView::setVerticalFillOrder(VerticalFillOrder fillOrder)
{
    if (_vordering != fillOrder)
    {
        _vordering = fillOrder;
        if (!_cellsUsed.empty())
        {
            this->reloadData();
        }
    }
}

TableView::VerticalFillOrder TableView::getVerticalFillOrder()
{
    return _vordering;
}

void TableView::reloadData()
{
    _oldDirection = Direction::NONE;

    for(const auto &cell : _cellsUsed) {
        if(_tableViewDelegate != nullptr) {
            _tableViewDelegate->tableCellWillRecycle(this, cell);
        }

        _cellsFreed.pushBack(cell);
        
        cell->reset();
        if (cell->getParent() == this->getContainer())
        {
            this->getContainer()->removeChild(cell, true);
        }
    }

    _indices->clear();
    _cellsUsed.clear();
    
    this->_updateCellPositions();
    this->_updateContentSize();
    if (_dataSource->numberOfCellsInTableView(this) > 0)
    {
        this->scrollViewDidScroll(this);
    }
}

TableViewCell *TableView::cellAtIndex(ssize_t idx)
{
    if (_indices->find(idx) != _indices->end())
    {
        for (const auto& cell : _cellsUsed)
        {
            if (cell->getIdx() == idx)
            {
                return cell;
            }
        }
    }

    return nullptr;
}

//footprint:索引偏移量
void TableView::scrollToIndex(ssize_t idx, bool animated)
{
    ssize_t num = _dataSource->numberOfCellsInTableView(this);
    if (num > 0) {
        Vec2 max = this->maxContainerOffset();
        const Vec2 min = this->minContainerOffset();
        
        if (this->getDirection() == Direction::VERTICAL) {
            for (ssize_t i = 0; i < (num - (idx + 1)); i++) {
                const Size cellSize = _dataSource->tableCellSizeForIndex(this, i);
                max.y -= cellSize.height;
                if (max.y < min.y) {
                    max.y = min.y;
                    break;
                }
            }
        }else {
            for (ssize_t i = 0; i < (num - (idx + 1)); i++) {
                const Size cellSize = _dataSource->tableCellSizeForIndex(this, i);
                max.x -= cellSize.width;
                if (max.x < min.x) {
                    max.x = min.x;
                    break;
                }
            }
        }
        this->setContentOffset(max, animated);
    }
}

void TableView::updateCellAtIndex(ssize_t idx)
{
    if (idx == CC_INVALID_INDEX)
    {
        return;
    }
    long countOfItems = _dataSource->numberOfCellsInTableView(this);
    if (0 == countOfItems || idx > countOfItems-1)
    {
        return;
    }

    TableViewCell* cell = this->cellAtIndex(idx);
    if (cell)
    {
        this->_moveCellOutOfSight(cell);
    }
    cell = _dataSource->tableCellAtIndex(this, idx);
    this->_setIndexForCell(idx, cell);
    this->_addCellIfNecessary(cell);
}

void TableView::insertCellAtIndex(ssize_t idx)
{
    if (idx == CC_INVALID_INDEX)
    {
        return;
    }

    //footprint:插入视图之前先更新数据源
    long countOfItems = _dataSource->numberOfCellsInTableView(this);
    if (0 == countOfItems || idx > countOfItems-1)
    {
        return;
    }

    auto cell = cellAtIndex(idx);
    bool found = nullptr != cell; //footprint:改位置的cell是否可视
    
    this->_updateCellPositions();
    this->_updateContentSize();
    
    //footprint:重建索引&重排位置
    _indices->clear();
    for (ssize_t i = 0; i < _cellsUsed.size(); ++i)
    {
        cell = _cellsUsed.at(i);
        ssize_t index = cell->getIdx();
        if (index >= idx)
        {
            ++index;
        }
        _indices->insert(index);
        this->_setIndexForCell(index, cell);
    }
    //footprint:只在可视的情况下插入cell
    if (found)
    {
        //insert a new cell
        cell = _dataSource->tableCellAtIndex(this, idx);
        this->_setIndexForCell(idx, cell);
        this->_addCellIfNecessary(cell);
    }
    //footprint:更新视图
    this->scrollViewDidScroll(this);
    //footprint:更新空白区域
    if (found)
    {
        this->deaccelerateScrolling(0);
    }
}

void TableView::removeCellAtIndex(ssize_t idx)
{
    if (idx == CC_INVALID_INDEX)
    {
        return;
    }

//footprint:删除视图之前先更新数据源，所以idx可能超过数据源的大小
//    long uCountOfItems = _dataSource->numberOfCellsInTableView(this);
//    if (0 == uCountOfItems || idx > uCountOfItems-1)
//    {
//        return;
//    }

    ssize_t newIdx = 0;

    TableViewCell* cell = this->cellAtIndex(idx);
    if (!cell)
    {
        return;
    }

    newIdx = _cellsUsed.getIndex(cell);

    //remove first
    this->_moveCellOutOfSight(cell);

    this->_updateCellPositions();
    this->_updateContentSize(); //footprint:需要更新视图大小
    
    //footprint:重新建立索引
    _indices->clear();
    
    //footprint:更新删除单元格之前的位置和索引
    for (ssize_t i = 0; i < newIdx; ++i) {
        cell = _cellsUsed.at(i);
        _indices->insert(cell->getIdx());
        this->_setIndexForCell(cell->getIdx(), cell);
    }
    //footprint:更新删除单元格之后的位置和索引
    for (ssize_t i = _cellsUsed.size()-1; i >= newIdx; i--)
    {
        cell = _cellsUsed.at(i);
        _indices->insert(cell->getIdx() - 1);
        this->_setIndexForCell(cell->getIdx() - 1, cell);
    }
    //footprint:更新视图
    this->scrollViewDidScroll(this);
    //footprint:更新空白区域
    this->deaccelerateScrolling(0);
}

TableViewCell *TableView::dequeueCell()
{
    TableViewCell *cell;

    if (_cellsFreed.empty()) {
        cell = nullptr;
    } else {
        cell = _cellsFreed.at(0);
        cell->retain();
        _cellsFreed.erase(0);
        cell->autorelease();
    }
    return cell;
}

TableViewCell *TableView::dequeueCell(const std::string &reuseID)
{
    for (auto iter = _cellsFreed.begin(); iter != _cellsFreed.end(); ++iter)
    {
        auto cell = (*iter);
        if (cell->getReuseIdentifier() == reuseID)
        {
            cell->retain();
            _cellsFreed.erase(iter);
            cell->autorelease();
            return cell;
        }
    }
    return nullptr;
}

void TableView::_addCellIfNecessary(TableViewCell * cell)
{
    if (cell->getParent() != this->getContainer())
    {
        this->getContainer()->addChild(cell);
    }
    _cellsUsed.pushBack(cell);
    _indices->insert(cell->getIdx());
    _isUsedCellsDirty = true;
    _sortUsedCell();
}

void TableView::_updateContentSize()
{
    Size size = Size::ZERO;
    ssize_t cellsCount = _dataSource->numberOfCellsInTableView(this);

    if (cellsCount > 0)
    {
        float maxPosition = _vCellsPositions[cellsCount];

        switch (this->getDirection())
        {
            case Direction::HORIZONTAL:
                size = Size(maxPosition, _viewSize.height);
                break;
            default:
                size = Size(_viewSize.width, maxPosition);
                break;
        }
    }

    this->setContentSize(size);

	if (_oldDirection != _direction)
	{
		if (_direction == Direction::HORIZONTAL)
		{
			this->setContentOffset(Vec2(0,0));
		}
		else
		{
			this->setContentOffset(Vec2(0,this->minContainerOffset().y));
		}
		_oldDirection = _direction;
	}

}

Vec2 TableView::_offsetFromIndex(ssize_t index)
{
    Vec2 offset = this->__offsetFromIndex(index);

    const Size cellSize = _dataSource->tableCellSizeForIndex(this, index);
    if (_vordering == VerticalFillOrder::TOP_DOWN)
    {
        offset.y = this->getContainer()->getContentSize().height - offset.y - cellSize.height;
    }
    return offset;
}

Vec2 TableView::__offsetFromIndex(ssize_t index)
{
    Vec2 offset;
    Size  cellSize;

    switch (this->getDirection())
    {
        case Direction::HORIZONTAL:
            offset = Vec2(_vCellsPositions[index], 0.0f);
            break;
        default:
            offset = Vec2(0.0f, _vCellsPositions[index]);
            break;
    }

    return offset;
}

long TableView::_indexFromOffset(Vec2 offset)
{
    long index = 0;
    const long maxIdx = _dataSource->numberOfCellsInTableView(this) - 1;

    if (_vordering == VerticalFillOrder::TOP_DOWN)
    {
        offset.y = this->getContainer()->getContentSize().height - offset.y;
    }
    index = this->__indexFromOffset(offset);
    if (index != -1)
    {
        index = MAX(0, index);
        if (index > maxIdx)
        {
            index = CC_INVALID_INDEX;
        }
    }

    return index;
}

long TableView::__indexFromOffset(Vec2 offset)
{
    long low = 0;
    long high = _dataSource->numberOfCellsInTableView(this) - 1;
    float search;
    switch (this->getDirection())
    {
        case Direction::HORIZONTAL:
            search = offset.x;
            break;
        default:
            search = offset.y;
            break;
    }

    while (high >= low)
    {
        long index = low + (high - low) / 2;
        float cellStart = _vCellsPositions[index];
        float cellEnd = _vCellsPositions[index + 1];

        if (search >= cellStart && search <= cellEnd)
        {
            return index;
        }
        else if (search < cellStart)
        {
            high = index - 1;
        }
        else
        {
            low = index + 1;
        }
    }

    if (low <= 0) {
        return 0;
    }

    return -1;
}

void TableView::_moveCellOutOfSight(TableViewCell *cell)
{
    if(_tableViewDelegate != nullptr) {
        _tableViewDelegate->tableCellWillRecycle(this, cell);
    }

    _cellsFreed.pushBack(cell);
    _cellsUsed.eraseObject(cell);
    _isUsedCellsDirty = true;
     _sortUsedCell();
    
    _indices->erase(cell->getIdx());
    cell->reset();
    
    if (cell->getParent() == this->getContainer())
    {
        this->getContainer()->removeChild(cell, true);;
    }
}

void TableView::_setIndexForCell(ssize_t index, TableViewCell *cell)
{
    cell->setAnchorPoint(Vec2(0.0f, 0.0f));
    cell->setPosition(this->_offsetFromIndex(index));
    cell->setIdx(index);
}

void TableView::_updateCellPositions()
{
    long cellsCount = _dataSource->numberOfCellsInTableView(this);
    _vCellsPositions.resize(cellsCount + 1, 0.0);

    if (cellsCount > 0)
    {
        float currentPos = 0;
        Size cellSize;
        for (int i=0; i < cellsCount; i++)
        {
            _vCellsPositions[i] = currentPos;
            cellSize = _dataSource->tableCellSizeForIndex(this, i);
            switch (this->getDirection())
            {
                case Direction::HORIZONTAL:
                    currentPos += cellSize.width;
                    break;
                default:
                    currentPos += cellSize.height;
                    break;
            }
        }
        _vCellsPositions[cellsCount] = currentPos;//1 extra value allows us to get right/bottom of the last cell
    }

}

//footprint
void TableView::_sortUsedCell()
{
    if (_isUsedCellsDirty)
    {
        _isUsedCellsDirty = false;
        std::sort(_cellsUsed.begin(), _cellsUsed.end(), [](TableViewCell *a, TableViewCell *b) -> bool{
            return a->getIdx() < b->getIdx();
        });
    }
}

void TableView::scrollViewDidScroll(ScrollView* view)
{
    long countOfItems = _dataSource->numberOfCellsInTableView(this);
    if (0 == countOfItems)
    {
        return;
    }

    //footprint:排序放入公共的接口
    _sortUsedCell();
    
    if(_tableViewDelegate != nullptr) {
        _tableViewDelegate->scrollViewDidScroll(this);
    }

    ssize_t startIdx = 0, endIdx = 0, idx = 0, maxIdx = 0;
    Vec2 offset = this->getContentOffset() * -1;
    maxIdx = MAX(countOfItems-1, 0);

    if (_vordering == VerticalFillOrder::TOP_DOWN)
    {
        offset.y = offset.y + _viewSize.height/this->getContainer()->getScaleY();
    }
    startIdx = this->_indexFromOffset(offset);
	if (startIdx == CC_INVALID_INDEX)
	{
		startIdx = countOfItems - 1;
	}

    if (_vordering == VerticalFillOrder::TOP_DOWN)
    {
        offset.y -= _viewSize.height/this->getContainer()->getScaleY();
    }
    else
    {
        offset.y += _viewSize.height/this->getContainer()->getScaleY();
    }
    offset.x += _viewSize.width/this->getContainer()->getScaleX();

    endIdx   = this->_indexFromOffset(offset);
    if (endIdx == CC_INVALID_INDEX)
	{
		endIdx = countOfItems - 1;
	}
    
#if 0 // For Testing.
    for (int i = 0; i < _cellsUsed.size(); ++i) {
        TableViewCell* pCell = _cellsUsed.at(i);
        log("cells Used index %d, value = %zd", i, pCell->getIdx());
    }
    log("---------------------------------------");
    for (int i = 0; i < _cellsFreed.size(); ++i) {
        TableViewCell* pCell = _cellsFreed.at(i);
        log("cells freed index %d, value = %zd", i, pCell->getIdx());
    }
    log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
#endif

    if (!_cellsUsed.empty())
    {
        auto cell = _cellsUsed.at(0);
        idx = cell->getIdx();
        
        while(idx < startIdx)
        {
            this->_moveCellOutOfSight(cell);
            if (!_cellsUsed.empty())
            {
                cell = _cellsUsed.at(0);
                idx = cell->getIdx();
            }
            else
            {
                break;
            }
        }
    }
    if (!_cellsUsed.empty())
    {
        auto cell = _cellsUsed.back();
        idx = cell->getIdx();

        while(idx <= maxIdx && idx > endIdx)
        {
            this->_moveCellOutOfSight(cell);
            if (!_cellsUsed.empty())
            {
                cell = _cellsUsed.back();
                idx = cell->getIdx();
            }
            else
            {
                break;
            }
        }
    }
    
#if 0 // For Testing.
    for (int i = 0; i < _cellsUsed.size(); ++i) {
        TableViewCell* pCell = _cellsUsed.at(i);
        log("cells Used index %d, value = %zd", i, pCell->getIdx());
    }
    log("---------------------------------------");
    for (int i = 0; i < _cellsFreed.size(); ++i) {
        TableViewCell* pCell = _cellsFreed.at(i);
        log("cells freed index %d, value = %zd", i, pCell->getIdx());
    }
    log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
#endif

    for (long i = startIdx; i <= endIdx; i++)
    {
        if (_indices->find(i) != _indices->end())
        {
            continue;
        }
        this->updateCellAtIndex(i);
    }
    
#if 0 // For Testing.
    for (int i = 0; i < _cellsUsed.size(); ++i) {
        TableViewCell* pCell = _cellsUsed.at(i);
        log("cells Used index %d, value = %zd", i, pCell->getIdx());
    }
    log("---------------------------------------");
    for (int i = 0; i < _cellsFreed.size(); ++i) {
        TableViewCell* pCell = _cellsFreed.at(i);
        log("cells freed index %d, value = %zd", i, pCell->getIdx());
    }
    log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
#endif
}

void TableView::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    if (!this->isVisible()) {
        return;
    }

    if (_touchedCell){
		Rect bb = this->getBoundingBox();
		bb.origin = _parent->convertToWorldSpace(bb.origin);

		if (bb.containsPoint(pTouch->getLocation()) && _tableViewDelegate != nullptr)
        {
            _tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
            _tableViewDelegate->tableCellTouched(this, _touchedCell);
        }

        _touchedCell = nullptr;
    }

    ScrollView::onTouchEnded(pTouch, pEvent);
}

bool TableView::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    for (Node *c = this; c != nullptr; c = c->getParent())
    {
        if (!c->isVisible())
        {
            return false;
        }
    }

    bool touchResult = ScrollView::onTouchBegan(pTouch, pEvent);

    if(_touches.size() == 1)
    {
        long index;
        Vec2 point;

        point = this->getContainer()->convertTouchToNodeSpace(pTouch);

        index = this->_indexFromOffset(point);
		if (index == CC_INVALID_INDEX)
		{
			_touchedCell = nullptr;
		}
        else
		{
			_touchedCell  = this->cellAtIndex(index);
		}

        if (_touchedCell && _tableViewDelegate != nullptr)
        {
            _tableViewDelegate->tableCellHighlight(this, _touchedCell);
        }
    }
    else if (_touchedCell)
    {
        if(_tableViewDelegate != nullptr)
        {
            _tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
        }

        _touchedCell = nullptr;
    }

    return touchResult;
}

void TableView::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    ScrollView::onTouchMoved(pTouch, pEvent);

    if (_touchedCell && isTouchMoved())
    {
        if(_tableViewDelegate != nullptr)
        {
            _tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
        }

        _touchedCell = nullptr;
    }
}

void TableView::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
    ScrollView::onTouchCancelled(pTouch, pEvent);

    if (_touchedCell)
    {
        if(_tableViewDelegate != nullptr)
        {
            _tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
        }

        _touchedCell = nullptr;
    }
}

NS_CC_EXT_END
