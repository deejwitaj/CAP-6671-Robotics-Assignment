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

}

//Prints out the grid world. The grid world assumes the file it was created from was formatted correctly.
//If a conflict between one cell stating it can enter another and the entering cell saying it cannot be entered
//exists, it will not be reflected in the outputted string
std::string GridWorld::PrintGridWorld()
{
	if (m_gridWorldRows.empty())
		return "";

	std::string gridWorldString = m_gridWorldRows[0].PrintTopWalls() + "\n";

	for (auto it : m_gridWorldRows)
		gridWorldString += it.PrintSideAndBottomWalls() + "\n";

	return gridWorldString;
}

bool GridWorld::AddRow(Row i_row)
{
	if (i_row.GetWidth() < m_width || i_row.GetWidth() > m_width)
		return false;

	m_gridWorldRows.push_back(i_row);
	return true;
}