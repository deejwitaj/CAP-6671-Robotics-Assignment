#ifndef INC_488087FB218D4BD1BB20D0749D156DCC
#define INC_488087FB218D4BD1BB20D0749D156DCC

#include <list>

#include "GridWorld.h"
#include "PathPlanner.h"

class Robot
{
public:
	Robot(PathPlanner i_planner);
  void FinishLearning();
	Action GetNextMove(Position i_current, std::list<Action> i_validMoves);
	void ProcessMove(Position i_from, Position i_to, double i_reward, std::list<Action> i_validMoves, Action i_toAction);
	void PrintQMap();
protected:
private:
	PathPlanner m_pathPlanner;
};
#endif