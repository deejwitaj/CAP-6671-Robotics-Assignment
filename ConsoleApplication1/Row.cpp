#include "stdafx.h"
#include "Row.h"

//Creates an entire row of cells with an open stae of i_bIsOpen
/*When i_bIsOpen is false, the row is made up of only completely walled off cells
  When i_bIsOpen is true, the row is made up of only completely open cells*/
Row::Row(bool const i_bIsOpen, int const i_width)
{
	for (int i = 0; i <= i_width; i++)
		AddCell(Cell(i_bIsOpen));
}

//Creates a row of cells with all non passed in columns completely open
Row::Row(Cell const i_cell, int const i_width, int const i_startingColumn)
{
	for (int i = 0; i <= i_width; i++)
	{
		if (i_startingColumn == i)
			AddCell(i_cell);
		else
			AddCell(Cell(false));
	}
}

//Creates a row of cells with all non passed in columns completely closed open
/*If no starting column is given, the row will automatically start at the 0th position
  i_Width is the width of the entire desired row
	i_startingColumn is the column i_row begins*/
Row::Row(std::list<Cell> i_row, int const i_Width, int const i_startingColumn)
{
	//The number of beginning default cells will be equal to the first specified column
	AddRow(i_startingColumn, new Cell(false));
	AddRow(i_row);
	AddRow(i_Width - m_row.size(), new Cell(false));
}

//Prints out only the top wall of the cells in the row on a single line
//The format of the ending line will be " _ _ _ _ _ "
std::string const Row::PrintTopWalls()
{
	if (m_row.empty())
		return "";

	std::string topWallString = " ";
	for (auto it : m_row)
		topWallString += it.PrintWall(TOP) + " ";

	return topWallString;
}

//Prints out only the side walls of the cells in the row on a single line
//The format of the ending line will be "| | | | | |"
std::string const Row::PrintSideWalls()
{
	if (m_row.empty())
		return "";

	std::string sideWallString = m_row.begin()->PrintWall(LEFT);

	for (auto it : m_row)
		sideWallString += " " + it.PrintWall(RIGHT);

	return sideWallString;
}

//Prints out only the bottom walls of the cells in the rown on a single line
//The format of the ending line will be " _ _ _ _ _ _ "
std::string const Row::PrintBottomWalls()
{
	if (m_row.empty())
		return "";

	std::string bottomWallString = " ";
	for (auto it : m_row)
		bottomWallString += it.PrintWall(BOTTOM) + " ";

	return bottomWallString;
}
//Prints out the entir row
std::string const Row::PrintRow()
{
	if (m_row.empty())
		return "";

	std::string rowString = "";
	rowString += PrintTopWalls() + "\n" + PrintSideWalls() + "\n" + PrintBottomWalls();
	return rowString;
}

//Adds cell to the end of the row
void Row::AddCell(Cell i_cell)
{
	m_row.emplace_back(i_cell);
}

//Adds amount of cells specified
void Row::AddRow(int const i_numOfCells, Cell i_cell)
{
	if (i_numOfCells < 0)
		return;

	for (int i = 0; i < i_numOfCells; i++)
		AddCell(i_cell);
}

void Row::AddRow(std::list<Cell> i_row)
{
	for (auto it : i_row)
		AddCell(it);
}