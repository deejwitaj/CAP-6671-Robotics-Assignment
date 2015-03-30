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
	AddRow(i_startingColumn);
	AddRow(i_row);
	AddRow(i_Width - m_row.size());
}

//Adds a closed cell to the end of the row
void Row::AddCell(Cell i_cell)
{
	m_row.emplace_back(i_cell);
}

//Adds amount of default cells specified
void Row::AddRow(int const i_numOfCells)
{
	if (i_numOfCells < 0)
		return;

	for (int i = 0; i < i_numOfCells; i++)
		AddCell(new Cell());
}

void Row::AddRow(std::list<Cell> i_row)
{
	for (auto it : i_row)
		AddCell(it);
}