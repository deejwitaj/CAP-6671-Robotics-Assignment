#ifndef INC_3B8C6296F12F440F8120893B785D9C69
#define INC_3B8C6296F12F440F8120893B785D9C69

#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include "Row.h"
#include "Common.h"
#include "RewardsMap.h"
#include "QMap.h"

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
	int GetHeight() const{ return m_height; }
	int GetWidth() const{ return m_width; }
	Position GetStartingCellPosition() const { return m_startingCell; }
	Position GetGoalCellLocation() const { return m_goalCell; }

	bool bIsGoal(Position const i_position) const;
	bool bIsPositionValid(const Position i_position) const;
	bool bIsMoveValid(Position i_from, Position i_to) const;
	
	std::string const PrintGridWorld();

	bool Enter();
	bool Enter(Position i_position);
	void Leave(){ m_bOccupied = false; }
	double MoveDown(std::list<Action> &io_validMoves);
	double MoveLeft(std::list<Action> &io_validMoves);
	double MoveRight(std::list<Action> &io_validMoves);
	double MoveUp(std::list<Action> &io_validMoves);

	gridWorldIt begin(){ return m_gridWorldRows.cbegin(); }
	gridWorldIt end(){ return m_gridWorldRows.cend(); }

protected:
private:
	std::vector<Row> m_gridWorldRows;
	int m_width, m_height;
	Position m_startingCell;
	Position m_goalCell;
	Position m_occupant;
	bool m_bOccupied;
	RewardsMap m_rewardMap;

	bool AddRow(Row i_row);
	int DetermineMoveReward(Position const i_from, Position const i_to);
	void FillRewardsMap();
	bool LeaveCell(Position const i_position);
	double Move(Position i_from, Position i_to, Action i_action, std::list<Action> &io_validMoves);
	bool OccupyCell(Position const i_position);
};

#endif