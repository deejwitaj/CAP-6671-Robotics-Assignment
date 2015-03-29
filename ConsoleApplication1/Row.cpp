#include "stdafx.h"
#include "Row.h"

//Creates an entire row of cells with an open stae of i_bIsOpen
/*When i_bIsOpen is false, the row is made up of only completely walled off cells
  When i_bIsOpen is true, the row is made up of only completely open cells*/
Row::Row(bool i_bIsOpen, int i_width)
{
	for (int i = 0; i <= i_width; i++)
		AddCell(Cell(i_bIsOpen), i);
}

//Creates a row of cells with all non passed in columns completely closed off
Row::Row(Cell i_cell, int i_width, int i_startingColumn)
{
	for (int i = 0; i <= i_width; i++)
	{
		if (i_startingColumn == i)
			AddCell(i_cell, i_startingColumn);
		else
			AddCell(Cell(false), i);
	}
}

//Creates a row of cells with all non passed in columns completely closed off
/*If no starting column is given, the row will automatically start at the 0th position*/
Row::Row(std::list<Cell> i_row, int i_width, int i_startingColumn)
{
	AddRow(0, i_startingColumn-1);
	AddRow(i_row, i_startingColumn);
	AddRow(i_row.size() + i_startingColumn, i_width);
}

//Adds a closed cell to the end of the row
void Row::AddCell()
{
	m_row.emplace_back(Cell(false));
}

//Adds a cell to the passed in column of the row
void Row::AddCell(Cell i_cell, int i_column)
{
	if (i_column < 0)
		return;

	auto it = m_row.begin();
	std::advance(it, i_column);
	m_row.emplace(it, i_cell);
}

//Adds columns from the starting column to the ending column
void Row::AddRow(int i_startingColumn, int i_endingColumn)
{
	if (i_startingColumn < 0)
		return;

	auto it = m_row.begin();
	std::advance(it, i_startingColumn);
}

void Row::AddRow(std::list<Cell> i_row, int i_startingColumn)
{
	if (i_startingColumn < 0)
		return;

	auto it = m_row.begin();
	std::advance(it, i_startingColumn);
	m_row.insert(it, i_row.begin(), i_row.end());
}