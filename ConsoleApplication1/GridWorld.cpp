#include "stdafx.h"
#include "GridWorld.h"
#include "GridWorldReader.h"

#include "time.h"

//Defaults to an 8x8 grid world with no obstacles or walls other than the outside border
GridWorld::GridWorld(int const i_gridWidth, int const i_gridHeight, bool i_bIsStochastic)
{
	m_width = i_gridWidth;
	m_height = i_gridHeight;
	Row row(true, i_gridWidth);
	m_bIsStochastic = i_bIsStochastic;
	for (int i = 0; i < i_gridHeight; i++)
		AddRow(row);
	FillRewardsMap();
}

/*Takes in a vector of Rows and equates it to the member vector. The constructor assumes
  that the rows are all equal length, and so uses the first row as its reference for the 
	needed width. The height is assumed to be the number of rows in the vector*/
GridWorld::GridWorld(std::vector<Row> i_gridWorldRows)
{
	m_width = i_gridWorldRows[0].GetWidth();
	m_height = i_gridWorldRows.size();
	
	m_gridWorldRows = i_gridWorldRows;
	FillRewardsMap();
}

GridWorld::GridWorld(const char* i_gridWorldFile, bool i_bIsStochastic)
{
	std::vector<Row> potentialGridWorldRows;
	if (GridWorldReader::CreateGridWorld(i_gridWorldFile, potentialGridWorldRows))
		m_gridWorldRows = potentialGridWorldRows;
	m_width = m_gridWorldRows[0].GetWidth();
	m_height = m_gridWorldRows.size();
  m_bIsStochastic = i_bIsStochastic;
	FillRewardsMap();
}

void GridWorld::Reset()
{
  for (int i = 0; i < m_height; i++)
    m_gridWorldRows[i].Reset();
}

//Returns the cell in the passed in position
bool GridWorld::GetCell(Position i_cellPosition, Cell &io_cell) const
{
	if ((m_gridWorldRows.empty()) || (!bIsPositionValid(i_cellPosition)))
		return false;

	Row cellRow;
	if (GetRow(i_cellPosition.GetYPosition(), cellRow))
		if (cellRow.GetCell(i_cellPosition.GetXPosition(), io_cell))
			return true;

	return false;
}

//Returns the row in the passed in position
bool GridWorld::GetRow(int rowPosition, Row &io_row) const
{
	//If the grid has no rows or if the position is not valid, return false
	if ((m_gridWorldRows.empty()) || (rowPosition < 0) || (rowPosition > m_height))
		return false;

	io_row = m_gridWorldRows[rowPosition];
	return true;
}

//Returns all valid actions in a given position
std::list<Action> GridWorld::GetValidMoves(Position i_position)
{
	std::list<Action> validMoves;

	if (bIsMoveValid(i_position, MOVE_UP))
		validMoves.push_back(MOVE_UP);
	if (bIsMoveValid(i_position, MOVE_DOWN))
		validMoves.push_back(MOVE_DOWN);
	if (bIsMoveValid(i_position, MOVE_LEFT))
		validMoves.push_back(MOVE_LEFT);
	if (bIsMoveValid(i_position, MOVE_RIGHT))
		validMoves.push_back(MOVE_RIGHT);

	return validMoves;
}


void GridWorld::ConsiderCell(Position i_pos)
{
  if (bIsPositionValid(i_pos))
    m_gridWorldRows[i_pos.GetYPosition()].ConsiderCell(i_pos.GetXPosition());
  PrintGridWorld();
}

void GridWorld::UnConsiderCell(Position i_pos)
{
  if (bIsPositionValid(i_pos))
    m_gridWorldRows[i_pos.GetYPosition()].UnConsiderCell(i_pos.GetXPosition());
  PrintGridWorld();
}

void GridWorld::AcceptCell(Position i_pos)
{
  if (bIsPositionValid(i_pos))
    m_gridWorldRows[i_pos.GetYPosition()].AcceptCell(i_pos.GetXPosition());
  PrintGridWorld();
}

bool GridWorld::bIsPositionOpen(Position i_position) const
{
	Row row;
	if (GetRow(i_position.GetYPosition(), row))
	{
		Cell cell;
		if (row.GetCell(i_position.GetXPosition(), cell))
			return cell.bIsOpen();
	}

	return false;
}

//Returns if the cell in the passed position is the goal
bool GridWorld::bIsGoal(Position i_position) const
{
	Row row;
	if (GetRow(i_position.GetYPosition(), row))
	{
		Cell cell;
		if (row.GetCell(i_position.GetXPosition(), cell))
			return cell.bIsGoal();
	}

	return false;
}

//Determines if passed in position is in grid world
bool GridWorld::bIsPositionValid(const Position i_position) const
{
	if (m_gridWorldRows.empty())
		return false;

	auto xPosition = i_position.GetXPosition();
	auto yPosition = i_position.GetYPosition();

	//Passed in position is not on the actual grid world
	if ((xPosition < 0) || (yPosition < 0)
		|| (xPosition >= m_width) || (yPosition >= m_height))
		return false;

	return true;
}

//Determines if a move from the current occupant position is valid
bool GridWorld::bIsMoveValid(Action i_action) const
{
	if (m_bOccupied)
		return bIsMoveValid(m_occupant, i_action);

	return false;
}

//Returns position of the goal cell
Position GridWorld::GetGoalPosition() const
{
  for (int height = 0; height < m_height; height++)
  {
    Row row;
    GetRow(height, row);
    for (int width = 0; width < m_width; width++)
    {
      Cell cell;
      row.GetCell(width, cell);
      if (cell.bIsGoal())
        return Position(width, height);
    }
  }

  return Position(0, 0);
}

//Returns valid moves from the occupnat's position
std::list<Action> GridWorld::GetValidMoves()
{
	std::list<Action> validMoves;

	if (!m_bOccupied)
		return validMoves;

	return GetValidMoves(m_occupant);
}

//Determines if a move between the two positions is possible
bool GridWorld::bIsMoveValid(Position const i_from, Position const i_to) const
{
	//If grid world has no rows, then we simply return false as no moves are valid
	if (m_gridWorldRows.empty())
		return false;

	//Positions are the same, so move is valid, though unnecessary
	if (i_from == i_to)
		return true;

	int const xDistance = i_from.GetXPosition() - i_to.GetXPosition();
	int const yDistance = i_from.GetYPosition() - i_to.GetYPosition();

	//Positions may only differ in distance by 1 for x and 0 for y...
	//or they may differ by 0 for x and 1 for y for them to be right next to each other
	if (((abs(xDistance) == 1) && (abs(yDistance) == 0)) || ((abs(xDistance) == 0) && (abs(yDistance) == 1)))
	{
		Cell toCell, fromCell;

		//Ensure the requested cells are valid and both cells are open
		if (GetCell(i_from, fromCell) && GetCell(i_to, toCell))
			if (fromCell.bIsOpen() && toCell.bIsOpen())
				return true;
	}

	return false;
}

//Determines if an action in a position is valid
bool GridWorld::bIsMoveValid(Position const i_from, Action const i_action) const
{
	Position i_to;

	switch (i_action)
	{
	case MOVE_UP:
		i_to = Position(i_from.GetXPosition(), i_from.GetYPosition() - 1);
		return bIsMoveValid(i_from, i_to);
	case MOVE_DOWN:
		i_to = Position(i_from.GetXPosition(), i_from.GetYPosition() + 1);
		return bIsMoveValid(i_from, i_to);
	case MOVE_LEFT:
		i_to = Position(i_from.GetXPosition() - 1, i_from.GetYPosition());
		return bIsMoveValid(i_from, i_to);
	case MOVE_RIGHT:
		i_to = Position(i_from.GetXPosition() + 1, i_from.GetYPosition());
		return bIsMoveValid(i_from, i_to);
	}

	return false;
}

//Prints out the grid world. The grid world assumes the file it was created from was formatted correctly.
//If a conflict between one cell stating it can enter another and the entering cell saying it cannot be entered
//exists, it will not be reflected in the outputted string
std::string const GridWorld::PrintGridWorld()
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	if (m_gridWorldRows.empty())
		return "";

	std::string gridWorldString = "";

	for (auto it : m_gridWorldRows)
		gridWorldString += it.PrintRow() + "\n";

	printf(gridWorldString.c_str());
	return gridWorldString;
}

//Enters the robot in a random position on the grid
bool GridWorld::Enter()
{
	if (m_bOccupied)
		return false;

	Position position;
	bool bCelIsAvailable = false;
	std::list<Position> validPositions;
	for (int checkedRow = 0; checkedRow < m_height; checkedRow++)
	{
		for (int checkedCell = 0; checkedCell < m_width; checkedCell++)
		{
			if (bIsPositionValid(position) && bIsPositionOpen(position))
				validPositions.push_back(position);
			position.SetXPosition(checkedCell);
		}
		position.SetXPosition(0);
		position.SetYPosition(checkedRow);
	}

	if (validPositions.empty())
		return false;

	int randomPosition = rand() % validPositions.size();
	auto it = validPositions.cbegin();
	std::advance(it, randomPosition);
	return Enter(*it);
}

void GridWorld::Leave()
{
	LeaveCell(m_occupant);
	m_bOccupied = false;
}

//Enters the robot into the requested position if it is available
bool GridWorld::Enter(Position i_position)
{
	if (m_bOccupied)
		return false;

	if (bIsPositionValid(i_position) && OccupyCell(i_position))
	{
		m_bOccupied = true;
		PrintGridWorld();
		return true;
	}

	return false;
}

//Moves the occupant using the passed in action
double GridWorld::Move(Action i_action, Action &io_actualAction)
{
	int chance;

	if (m_bIsStochastic)
		chance = rand() % 101;
	else
		chance = 0;

	if (chance < 60)
	{
		switch (i_action)
		{
		case MOVE_UP:
			return MoveUp(io_actualAction);
		case MOVE_DOWN:
      return MoveDown(io_actualAction);
		case MOVE_LEFT:
      return MoveLeft(io_actualAction);
		case MOVE_RIGHT:
      return MoveRight(io_actualAction);
		}
	}

	switch (i_action)
	{
	case MOVE_UP:
	{
		if (chance < 70)
      return MoveRight(io_actualAction);
		else if (chance < 80)
      return MoveDown(io_actualAction);
		else if (chance < 90)
      return MoveLeft(io_actualAction);
    return NoMove(io_actualAction);
	}
	case MOVE_DOWN:
	{
		if (chance < 70)
      return MoveUp(io_actualAction);
		else if (chance < 80)
      return MoveRight(io_actualAction);
		else if (chance < 90)
      return MoveLeft(io_actualAction);
    return NoMove(io_actualAction);
	}
	case MOVE_LEFT:
	{
		if (chance < 70)
      return MoveUp(io_actualAction);
		else if (chance < 80)
      return MoveDown(io_actualAction);
		else if (chance < 90)
      return MoveRight(io_actualAction);
    return NoMove(io_actualAction);
	}
	case MOVE_RIGHT:
	{
		if (chance < 70)
      return MoveUp(io_actualAction);
		else if (chance < 80)
      return MoveDown(io_actualAction);
		else if (chance < 90)
      return MoveLeft(io_actualAction);
    return NoMove(io_actualAction);
	}
	}

	return -1;
}

//Move from i_from to i_to
double GridWorld::Move(Position i_from, Position i_to, Action i_action, Action &io_actualAction)
{
	if (m_bOccupied)
	{
		//If move is valid, we update the occupant position and return that the move was successful
		if (bIsMoveValid(i_from, i_to) && LeaveCell(i_from) && OccupyCell(i_to))
		{
			PrintGridWorld();
			int reward = m_rewardMap.GetReward(i_from, i_action);
      io_actualAction = i_action;
			return reward;
		}
	}

  io_actualAction = NO_MOVE;
	return m_rewardMap.GetReward(i_from, NO_MOVE);
}

//Move down one cell
double GridWorld::MoveDown(Action &io_actualAction)
{
	Position to = m_occupant;
	to.SetYPosition(m_occupant.GetYPosition() + 1);
  return Move(m_occupant, to, MOVE_DOWN, io_actualAction);
}

//Move left one cell
double GridWorld::MoveLeft(Action &io_actualAction)
{
	Position to = m_occupant;
	to.SetXPosition(m_occupant.GetXPosition() - 1);
  return Move(m_occupant, to, MOVE_LEFT, io_actualAction);
}

//Move right one cell
double GridWorld::MoveRight(Action &io_actualAction)
{
	Position to = m_occupant;
	to.SetXPosition(m_occupant.GetXPosition() + 1);
  return Move(m_occupant, to, MOVE_RIGHT, io_actualAction);
}

//Move up one cell
double GridWorld::MoveUp(Action &io_actualAction)
{
	Position to = m_occupant;
	to.SetYPosition(m_occupant.GetYPosition() - 1);
  return Move(m_occupant, to, MOVE_UP, io_actualAction);
}

double GridWorld::NoMove(Action &io_actualAction)
{
  Position to = m_occupant;
  return Move(m_occupant, m_occupant, NO_MOVE, io_actualAction);
}
bool GridWorld::AddRow(Row i_row)
{
	if (i_row.GetWidth() < m_width || i_row.GetWidth() > m_width)
		return false;

	m_gridWorldRows.push_back(i_row);
	return true;
}

int GridWorld::DetermineMoveReward(Position const i_from, Position const i_to)
{

	if (bIsPositionValid(i_from) && bIsPositionValid(i_to) && bIsMoveValid(i_from, i_to))
	{
		Cell cell;
		if (GetCell(i_to, cell))
		{
			if (!cell.bIsOpen())
				return -1;
			if (cell.bIsGoal())
				return 100;
			else
				return 0;
		}
	}

	return -1;
}

//Leaves the cell in the passed in position
bool GridWorld::LeaveCell(Position const i_position)
{
	if (bIsPositionValid(i_position))
		return m_gridWorldRows[i_position.GetYPosition()].LeaveCell(i_position.GetXPosition());

	return false;
}

//Fills the rewards map using the completed grid world
void GridWorld::FillRewardsMap()
{
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Position position(x, y);
			//Determine rewards for moving in all four directions
			Position newPosition(position.GetXPosition(), position.GetYPosition() - 1);
			if (bIsPositionValid(newPosition))
				m_rewardMap.SetReward(R(position, MOVE_UP), DetermineMoveReward(position, newPosition));

			newPosition = Position(position.GetXPosition(), position.GetYPosition() + 1);
			if (bIsPositionValid(newPosition))
				m_rewardMap.SetReward(R(position, MOVE_DOWN), DetermineMoveReward(position, newPosition));

			newPosition = Position(position.GetXPosition() - 1, position.GetYPosition());
			if (bIsPositionValid(newPosition))
				m_rewardMap.SetReward(R(position, MOVE_LEFT), DetermineMoveReward(position, newPosition));

			newPosition = Position(position.GetXPosition() + 1, position.GetYPosition());
			if (bIsPositionValid(newPosition))
				m_rewardMap.SetReward(R(position, MOVE_RIGHT), DetermineMoveReward(position, newPosition));

      m_rewardMap.SetReward(R(position, NO_MOVE), DetermineMoveReward(position, position));
		}
	}
}

//Occupies the cell in the passed in position
bool GridWorld::OccupyCell(Position const i_position)
{
	if (bIsPositionValid(i_position))
		if (m_gridWorldRows[i_position.GetYPosition()].OccupyCell(i_position.GetXPosition()))
		{
			m_occupant = i_position;
			return true;
		}

	return false;
}
