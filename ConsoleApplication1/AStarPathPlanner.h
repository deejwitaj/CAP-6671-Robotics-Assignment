#ifndef INC_3753C86449114DBFB2314982C2BD5585
#define INC_3753C86449114DBFB2314982C2BD5585

#include <map>

#include "Common.h"
#include "GridWorld.h"

class AStarPathPlanner
{
public:
  AStarPathPlanner(GridWorld *i_gridWorld);

  Node * FindPath();
  double CalculateDistance(Position i_from, Position i_to);
  void AddChildrenToToBeExploredPositions(Node * i_parentNode);
  void AddChild(Node * i_parentNode, Position i_childNode);
  void ConsiderCell(Position i_pos);

  std::vector<Action> GetPath();
protected:
private:
  std::map<Position, Node*> m_toBeExploredPositions;
  std::map<Position, Node*> m_exploredPositions;
  GridWorld *m_gridWorld;
  Position m_goalPosition, m_startingPosition;

  Node * GetMinToBeExploredNode();
};

#endif