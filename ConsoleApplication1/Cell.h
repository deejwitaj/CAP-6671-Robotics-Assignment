#ifndef INC_93E1D27140414CBCBDC94F51395C287E
#define INC_93E1D27140414CBCBDC94F51395C287E

/*Represents a single cell in a grid world.*/
#include <map>
#include "Common.h"
#include "Wall.h"

/*Makes up the entire grid. Each cell is made up of four walls with each wall potentially having an exit.*/
class Cell
{
public:
	typedef std::map<CellSide, Wall>::const_iterator wallIt;

	Cell(bool i_bIsOpen = true, int i_reward = 1);
	Cell(CellSide i_side, Wall i_wall, int i_reward = 1);
	Cell(Wall i_topWall, Wall i_bottomWall, Wall i_leftWall, Wall i_rightWall, int i_reward = 1);
	Cell(std::pair<CellSide, Wall> i_wall, int i_reward = 1);
	Cell(std::map<CellSide, Wall> i_walls, int i_reward = 1);

	Wall const GetWall(CellSide i_side);
	int const GetReward(){ return m_reward; }

	void SetReward(int const i_reward){ m_reward = i_reward; }

	bool const bIsExit(CellSide i_cellSide);
	bool const bHasExit();

	std::string const PrintWall(CellSide i_side);

	wallIt cbegin(){ return m_walls.cbegin(); }
	wallIt cend(){ return m_walls.cend(); }

private:
	std::map<CellSide, Wall> m_walls;
	int m_reward;

	void AddWall(CellSide i_side, Wall i_newWall);
	void AddWall(std::pair<CellSide, Wall> i_wall);
	void RemoveWall(CellSide i_side);
	void MakeOpen(bool i_open);

	bool const bCellWallValid(CellSide i_cellSide);
};

#endif