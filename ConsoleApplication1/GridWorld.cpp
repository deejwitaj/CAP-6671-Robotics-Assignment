#include "stdafx.h"
#include "GridWorld.h"
#include "GridWorldReader.h"

//Defaults to an 8x8 grid world with no obstacles or walls other than the outside border
GridWorld::GridWorld(int const i_gridWidth, int const i_gridHeight)
{
	m_width = i_gridWidth;
	m_height = i_gridHeight;
	Row row(true, i_gridWidth);
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

GridWorld::GridWorld(const char* i_gridWorldFile)
{
	std::vector<Row> potentialGridWorldRows;
	if (GridWorldReader::CreateGridWorld(i_gridWorldFile, potentialGridWorldRows))
		m_gridWorldRows = potentialGridWorldRows;
	m_width = m_gridWorldRows[0].GetWidth();
	m_height = m_gridWorldRows.size();
	FillRewardsMap();
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

//Enters the robot in the first available grid. The order of checked cells goes from left to right, top to bottom
bool GridWorld::Enter()
{
	if (m_bOccupied)
		return false;

	Position position;
	bool bCelIsAvailable = false;
	for (int checkedRow = 0; checkedRow < m_height; checkedRow++)
	{
		for (int checkedCell = 0; checkedCell < m_width; checkedCell++)
		{
			if (bIsPositionValid(position) && OccupyCell(position))
			{
				m_bOccupied = true;
				PrintGridWorld();
				return true;
			}
			position.SetXPosition(checkedCell);
		}
		position.SetXPosition(0);
		position.SetYPosition(checkedRow);
	}

	return false;
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

//Move from i_from to i_to
bool GridWorld::Move(Position i_from, Position i_to)
{
	if (m_bOccupied)
	{
		//If move is valid, we update the occupant position and return that the move was successful
		if (bIsMoveValid(i_from, i_to) && LeaveCell(i_from) && OccupyCell(i_to))
		{
			PrintGridWorld();
			return true;
		}
	}

	return false;
}

//Move down one cell
bool GridWorld::MoveDown()
{
	Position to = m_occupant;
	to.SetYPosition(m_occupant.GetYPosition() + 1);
	return Move(m_occupant, to);
}

//Move left one cell
bool GridWorld::MoveLeft()
{
	Position to = m_occupant;
	to.SetXPosition(m_occupant.GetXPosition() - 1);
	return Move(m_occupant, to);
}

//Move right one cell
bool GridWorld::MoveRight()
{
	Position to = m_occupant;
	to.SetXPosition(m_occupant.GetXPosition() + 1);
	return Move(m_occupant, to);
}

//Move up one cell
bool GridWorld::MoveUp()
{
	Position to = m_occupant;
	to.SetYPosition(m_occupant.GetYPosition() - 1);
	return Move(m_occupant, to);
}

//Initializes a q map with values corresponding to the grid world
//A -1 represents a not valid move, a 0 represents a valid move...
//...and a 100 represents the goal
void GridWorld::InitializeQMap(QMap &io_qMap)
{
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Position position(x, y);
			//Determine initial q values for moving in all four directions
			Position newPosition(position.GetXPosition(), position.GetYPosition() - 1);
			if (bIsPositionValid(newPosition))
			{
				if (bIsGoal(newPosition))
					io_qMap.SetQ(R(position, MOVE_UP), 100);
				else
					io_qMap.SetQ(R(position, MOVE_UP), 0);
			}
			else
				io_qMap.SetQ(R(position, MOVE_UP), -1);

			newPosition = Position(position.GetXPosition(), position.GetYPosition() + 1);
			if (bIsPositionValid(newPosition))
			{
				if (bIsGoal(newPosition))
					io_qMap.SetQ(R(position, MOVE_DOWN), 100);
				else
					io_qMap.SetQ(R(position, MOVE_DOWN), 0);
			}
			else
				io_qMap.SetQ(R(position, MOVE_DOWN), -1);

			newPosition = Position(position.GetXPosition() - 1, position.GetYPosition());
			if (bIsPositionValid(newPosition))
			{
				if (bIsGoal(newPosition))
					io_qMap.SetQ(R(position, MOVE_LEFT), 100);
				else
					io_qMap.SetQ(R(position, MOVE_LEFT), 0);
			}
			else
				io_qMap.SetQ(R(position, MOVE_LEFT), -1);

			newPosition = Position(position.GetXPosition() + 1, position.GetYPosition());
			if (bIsPositionValid(newPosition))
			{
				if (bIsGoal(newPosition))
					io_qMap.SetQ(R(position, MOVE_RIGHT), 100);
				else
					io_qMap.SetQ(R(position, MOVE_RIGHT), 0);
			}
			else
				io_qMap.SetQ(R(position, MOVE_RIGHT), -1);
		}
	}
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
