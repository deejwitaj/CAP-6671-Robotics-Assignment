#ifndef INC_488087FB218D4BD1BB20D0749D156DCC
#define INC_488087FB218D4BD1BB20D0749D156DCC

#include <list>

#include "GridWorld.h"
#include "PathPlanner.h"

class Robot
{
public:
	Robot(PathPlanner i_planner);
	Action GetNextMove(Position i_current, std::list<Action> i_validMoves);
	void ProcessMove(Position i_from, Position i_to, double i_reward, std::list<Action> i_validMoves);
protected:
private:
	PathPlanner m_pathPlanner;
	Action m_lastMove;
};
#endif