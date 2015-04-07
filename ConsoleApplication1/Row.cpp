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
Row::Row(std::vector<Cell> i_row, int const i_Width, int const i_startingColumn)
{
	//The number of beginning default cells will be equal to the first specified column
	Cell i_cell(false);
	AddRow(i_startingColumn, i_cell);
	AddRow(i_row);
	AddRow(i_Width - m_row.size(), i_cell);
}

void Row::Reset()
{
  for (int i = 0; i < m_row.size(); i++)
    m_row[i].Reset();
}

//Returns a copy of the requested cell in the passed in position
bool Row::GetCell(int const i_cellPosition, Cell &io_cell) const
{
	if ((i_cellPosition < 0) || (i_cellPosition >= m_row.size()))
		return false;

	io_cell = m_row[i_cellPosition];
	return true;;
}

//Leaves the cell in the selected position
bool Row::LeaveCell(int const i_cellPosition)
{
	if ((i_cellPosition >= 0) && (i_cellPosition < GetWidth()))
		return m_row[i_cellPosition].Leave();

	return false;
}

//Occupies the cell in the selected position
bool Row::OccupyCell(int const i_cellPosition)
{
	if ((i_cellPosition >= 0) && (i_cellPosition < GetWidth()))
		return m_row[i_cellPosition].Occupy();

	return false;
}

void Row::AcceptCell(int const i_cellPosition)
{
  if ((i_cellPosition >= 0) && (i_cellPosition < GetWidth()))
    m_row[i_cellPosition].Accept();
}

void Row::ConsiderCell(int const i_cellPosition)
{
  if ((i_cellPosition >= 0) && (i_cellPosition < GetWidth()))
    m_row[i_cellPosition].Consider();
}

void Row::UnConsiderCell(int const i_cellPosition)
{
  if ((i_cellPosition >= 0) && (i_cellPosition < GetWidth()))
    m_row[i_cellPosition].Unconsider();
}

//Prints out the entir row
std::string const Row::PrintRow()
{
	if (m_row.empty())
		return "";

	std::string rowString = "";
	for (auto it : m_row)
		rowString += it.PrintCell();

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

void Row::AddRow(std::vector<Cell> i_row)
{
	for (auto it : i_row)
		AddCell(it);
}