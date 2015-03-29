#include "stdafx.h"
#include "Cell.h"

//If no walls are given, then the cell defaults to a barrier
Cell::Cell(bool i_bIsOpen, int i_reward)
{
	m_reward = i_reward;
	MakeOpen(i_bIsOpen);
}

//Creates a cell with all other sides having no exit
Cell::Cell(CellSide i_side, Wall i_wall, int i_reward)
{
	m_reward = i_reward;
	MakeOpen(false);
	AddWall(i_side, i_wall);
}

//Creates a cell with the four passed in walls
Cell::Cell(Wall i_topWall, Wall i_bottomWall, Wall i_leftWall, Wall i_rightWall, int i_reward)
{
	m_reward = i_reward;
	AddWall(TOP, i_topWall);
	AddWall(BOTTOM, i_bottomWall);
	AddWall(LEFT, i_leftWall);
	AddWall(RIGHT, i_rightWall);
}

//Creates a cell with all other sides having no exit
Cell::Cell(std::pair<CellSide, Wall> i_wall, int i_reward)
{
	m_reward = i_reward;
	MakeOpen(false);
	AddWall(i_wall);
}

//Creates a cell with passed in four walls
Cell::Cell(std::map<CellSide, Wall> i_walls, int i_reward)
{
	m_reward = i_reward;
	m_walls = i_walls;
}

//Adds the passed in wall or replaces the existing wall
void Cell::AddWall(CellSide i_side, Wall i_newWall)
{
	RemoveWall(i_side);
	m_walls.insert(std::pair<CellSide, Wall>(i_side, i_newWall));		
}

//Adds the passed in wall or replaces the existing wall
void Cell::AddWall(std::pair<CellSide, Wall> i_wall)
{
	RemoveWall(i_wall.first);
	m_walls.insert(i_wall);
}

//Removes the wall in the side passed in
void Cell::RemoveWall(CellSide i_side)
{
	//Remove cell wall if it already exists
	auto side = m_walls.find(i_side);
	if (side != m_walls.end())
		m_walls.erase(side);
}

//Creates a cell with no walls if true is passed in and surrounded by walls if false
void Cell::MakeOpen(bool i_open)
{
	AddWall(TOP, Wall(i_open));
	AddWall(BOTTOM, Wall(i_open));
	AddWall(LEFT, Wall(i_open));
	AddWall(RIGHT, Wall(i_open));
}

//Returns the requested wall
Wall const Cell::GetWall(CellSide i_side)
{
	return m_walls[i_side];
}

//Returns true if cell wall has an exit
bool const Cell::bIsExit(CellSide i_side)
{
	auto side = m_walls.find(i_side);
	if (side != m_walls.end())
		return m_walls[i_side].bHasExit();

	return false;
}

bool const Cell::bHasExit()
{
	for (auto it : m_walls)
		if (it.second.bHasExit())
			return true;

	return false;
}

//Returns true if cell wall has been created for passed in cell side
bool const Cell::bCellWallValid(CellSide i_cellSide)
{
	auto side = m_walls.find(i_cellSide);
	return (m_walls.find(i_cellSide) != m_walls.end());
}