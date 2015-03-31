#ifndef INC_3B8C6296F12F440F8120893B785D9C69
#define INC_3B8C6296F12F440F8120893B785D9C69

#include <iostream>
#include <fstream>
#include <vector>

#include "Row.h"
#include "Common.h"

/*The grid world is a vecotr of rows whose ordering represents a top to bottom placement*/
class GridWorld
{
public:
	typedef std::vector<Row>::const_iterator gridWorldIt;

	GridWorld(int const i_gridWidth = 8, int const i_gridHeight = 8);
	GridWorld(std::vector<Row> i_gridWorldRows);
	GridWorld(const char* i_gridWorldFile);

	bool GetCell(Position i_cellPosition, Cell &io_cell) const;
	bool GetRow(int rowPosition, Row &io_row) const;
	Position GetStartingCellPosition() const { return m_startingCell; }
	Position GetGoalCellLocation() const { return m_goalCell; }

	bool bIsPositionValid(const Position i_position) const;
	bool bIsMoveValid(Position i_from, Position i_to) const;
	
	std::string const PrintGridWorld();

	bool Enter();
	void Leave(){ m_bOccupied = false; }
	bool Move(Position i_from, Position i_to);
	bool MoveDown();
	bool MoveLeft();
	bool MoveRight();
	bool MoveUp();

	gridWorldIt cbegin(){ return m_gridWorldRows.cbegin(); }
	gridWorldIt cend(){ return m_gridWorldRows.cend(); }

protected:
private:
	std::vector<Row> m_gridWorldRows;
	int m_width, m_height;
	Position m_startingCell;
	Position m_goalCell;
	Position m_occupant;
	bool m_bOccupied;

	bool AddRow(Row i_row);
};

#endif