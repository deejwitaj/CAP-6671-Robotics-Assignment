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
}

/*Takes in a vector of Rows and equates it to the member vector. The constructor assumes
  that the rows are all equal length, and so uses the first row as its reference for the 
	needed width. The height is assumed to be the number of rows in the vector*/
GridWorld::GridWorld(std::vector<Row> i_gridWorldRows)
{
	m_width = i_gridWorldRows[0].GetWidth();
	m_height = i_gridWorldRows.size();
	
	m_gridWorldRows = i_gridWorldRows;
}

GridWorld::GridWorld(const char* i_gridWorldFile)
{
	std::vector<Row> potentialGridWorldRows;
	if (GridWorldReader::CreateGridWorld(i_gridWorldFile, potentialGridWorldRows))
		m_gridWorldRows = potentialGridWorldRows;
	m_width = m_gridWorldRows[0].GetWidth();
	m_height = m_gridWorldRows.size() - 1;
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

		//Ensure the requested cells are valid
		if (GetCell(i_from, fromCell) && GetCell(i_to, toCell))
		{
			//Ensure the cells have exits and, as a consequence, entrances
			if (fromCell.bHasExit() && toCell.bHasExit())
			{
				//If xDistance is the one that is non zero, then the one cell is to the left or right of the other
				if (xDistance != 0)
				{
					//Moving from fromCell's right exit to toCell's left exit, if they are valid
					if ((xDistance < 0) && (fromCell.bIsExit(RIGHT)) && (toCell.bIsExit(LEFT)))
						return true;

					//Moving from fromCell's left exit to toCell's right exit, if they are valid
					if ((xDistance > 0) && (fromCell.bIsExit(LEFT)) && (toCell.bIsExit(RIGHT)))
						return true;
				}

				//yDistance is the one that is non zero, so one cell is to the top or bottom of the other
				else
				{
					//Moving from fromCell's bottom exit to toCell's top exit, if they are valid
					if ((yDistance < 0) && (fromCell.bIsExit(BOTTOM)) && (toCell.bIsExit(TOP)))
						return true;

					//Moving from fromCell's top exit to toCell's bottom exit, if they are valid
					if ((yDistance > 0) && (fromCell.bIsExit(TOP)) && (toCell.bIsExit(BOTTOM)))
						return true;
				}
			}
		}
	}

	return false;
}

//Prints out the grid world. The grid world assumes the file it was created from was formatted correctly.
//If a conflict between one cell stating it can enter another and the entering cell saying it cannot be entered
//exists, it will not be reflected in the outputted string
std::string const GridWorld::PrintGridWorld()
{
	if (m_gridWorldRows.empty())
		return "";

	std::string gridWorldString = m_gridWorldRows[0].PrintTopWalls() + "\n";

	for (auto it : m_gridWorldRows)
		gridWorldString += it.PrintSideAndBottomWalls() + "\n";

	return gridWorldString;
}

//Returns the entrance cell's position in the grid
bool GridWorld::Enter()
{
	if (m_bOccupied)
		return false;

	m_occupant = GetStartingCellPosition();
	m_bOccupied = true;
	return true;
}

//Move from i_from to i_to
bool GridWorld::Move(Position i_from, Position i_to)
{
	if (m_bOccupied)
	{
		//If move is valid, we update the occupant position and return that the move was successful
		if (bIsMoveValid(i_from, i_to))
		{
			m_occupant = i_to;
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

bool GridWorld::AddRow(Row i_row)
{
	if (i_row.GetWidth() < m_width || i_row.GetWidth() > m_width)
		return false;

	m_gridWorldRows.push_back(i_row);
	return true;
}
