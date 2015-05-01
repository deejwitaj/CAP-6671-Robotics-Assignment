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
	GridWorld(int const i_gridWidth = 8, int const i_gridHeight = 8, bool i_bIsStochastic = true);
	GridWorld(std::vector<Row> i_gridWorldRows);
	GridWorld(const char* i_gridWorldFile, bool i_bIsStochastic);

  void Reset();
	bool bIsGoal(Position const i_position) const;
	bool bIsPositionOpen(const Position i_position) const;
	bool bIsPositionValid(const Position i_position) const;
	bool bIsMoveValid(Action i_action) const;

	Position GetCurrentPosition() const{ return m_occupant; }
  Position GetGoalPosition() const;
	std::list<Action> GetValidMoves();
	std::list<Action> GetValidMoves(Position i_position);

  void SetStochasticity(bool i_bIsStochastic){ m_bIsStochastic = i_bIsStochastic; }
	
  void AcceptCell(Position i_pos);
  void ConsiderCell(Position i_pos);
  void UnConsiderCell(Position i_pos);
	std::string const PrintGridWorld();

	bool Enter();
	void Leave();
	double Move(Action i_action, Action &io_actualAction);
  double MoveDown(Action &io_actualAction);
  double MoveLeft(Action &io_actualAction);
  double MoveRight(Action &io_actualAction);
  double MoveUp(Action &io_actualAction);
  double NoMove(Action &io_actualAction);

  double GetReward(Action i_action){ return m_rewardMap.GetReward(m_occupant, i_action); }

protected:
private:
	std::vector<Row> m_gridWorldRows;
	int m_width, m_height;
	Position m_occupant;
	bool m_bOccupied, m_bIsStochastic;
	RewardsMap m_rewardMap;

	bool Enter(Position i_position);

	bool bIsMoveValid(Position const i_from, Position const i_to) const;
	bool bIsMoveValid(Position const i_from, Action const i_action) const;

	bool GetCell(Position i_cellPosition, Cell &io_cell) const;
	bool GetRow(int rowPosition, Row &io_row) const;
	int GetHeight() const{ return m_height; }
	int GetWidth() const{ return m_width; }

	bool AddRow(Row i_row);
	int DetermineMoveReward(Position const i_from, Position const i_to);
	void FillRewardsMap();
	bool LeaveCell(Position const i_position);
  double Move(Position i_from, Position i_to, Action i_action, Action &io_actualAction);
	bool OccupyCell(Position const i_position);
};

#endif