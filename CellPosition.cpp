#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum);
}

bool CellPosition::SetVCell(int v)
{
	if (v >= 0 && v < NumVerticalCells)
	{
		vCell = v;
		return true;
	}
	return false;
}

bool CellPosition::SetHCell(int h)
{
	if (h >= 0 && h < NumHorizontalCells)
	{
		hCell = h;
		return true;
	}
	return false;
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	return (vCell >= 0 && vCell < NumVerticalCells &&
		hCell >= 0 && hCell < NumHorizontalCells);
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this);
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	int v = cellPosition.VCell();
	int h = cellPosition.HCell();

	return (NumVerticalCells - 1 - v) * NumHorizontalCells + h + 1;
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	if (cellNum < 1 || cellNum > NumVerticalCells * NumHorizontalCells)
		return CellPosition(-1, -1);

	int v = NumVerticalCells - 1 - (cellNum - 1) / NumHorizontalCells;
	int h = (cellNum - 1) % NumHorizontalCells;

	CellPosition position;
	position.SetVCell(v);
	position.SetHCell(h);

	return position;
}

void CellPosition::AddCellNum(int addedNum, Direction direction)
{
	int cellNum = GetCellNum();

	if (direction == UP)
		cellNum += addedNum * NumHorizontalCells;

	else if (direction == DOWN)
		cellNum -= addedNum * NumHorizontalCells;

	else if (direction == RIGHT)
		cellNum += addedNum;

	else if (direction == LEFT)
		cellNum -= addedNum;

	if (cellNum < 1 || cellNum > NumVerticalCells * NumHorizontalCells)
		return;

	CellPosition newPos = GetCellPositionFromNum(cellNum);

	vCell = newPos.VCell();
	hCell = newPos.HCell();
}