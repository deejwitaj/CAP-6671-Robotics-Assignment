/*Represents a single cell in a grid world.*/
#include <map>
#include "Common.h"
#include "Wall.h"

class Cell
{
public:
	Cell(bool i_bIsOpen = true, int i_reward = 1);
	Cell(CellSide i_side, Wall i_wall, int i_reward = 1);
	Cell(std::pair<CellSide, Wall> i_wall, int i_reward = 1);
	Cell(std::map<CellSide, Wall> i_walls, int i_reward = 1);

	Wall GetWall(CellSide i_side);
	int GetReward(){ return m_reward; }

	bool bIsExit(CellSide i_cellSide);
	bool bHasExit();

private:
	std::map<CellSide, Wall> m_walls;
	int m_reward;

	void AddWall(CellSide i_side, Wall i_newWall);
	void AddWall(std::pair<CellSide, Wall> i_wall);
	void RemoveWall(CellSide i_side);
	void MakeOpen(bool i_open);

	bool bCellWallValid(CellSide i_cellSide);
};