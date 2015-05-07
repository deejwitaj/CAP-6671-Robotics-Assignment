#include "stdafx.h"

#include <cmath>
#include <math.h>

#include "AStarPathPlanner.h"

AStarPathPlanner::AStarPathPlanner(GridWorld *i_gridWorld) :
  m_gridWorld(i_gridWorld)
{
  m_goalPosition = m_gridWorld->GetGoalPosition();
  m_startingPosition = m_gridWorld->GetCurrentPosition();

  Node * i_startingNode = new Node(m_startingPosition, 0);
  i_startingNode->SetDistanceToGoal(CalculateDistance(m_startingPosition, m_goalPosition));

  m_exploredPositions[m_startingPosition] = i_startingNode;
  AddChildrenToToBeExploredPositions(i_startingNode);
}

Node * AStarPathPlanner::FindPath()
{
  if (m_toBeExploredPositions.empty())
    return nullptr;

  else
  {
    Node * minNode = GetMinToBeExploredNode();
    if (m_gridWorld->bIsGoal(minNode->pos))
      return minNode;

    else
    {
      if ((m_exploredPositions.find(minNode->pos) == m_exploredPositions.end()))
      {
        m_exploredPositions[minNode->pos] = minNode;
        AddChildrenToToBeExploredPositions(minNode);
      }
      return FindPath();
    }
  }
}

double AStarPathPlanner::CalculateDistance(Position i_from, Position i_to)
{
  double xDistance = i_to.GetXPosition() - i_from.GetXPosition();
  double yDistance = i_to.GetYPosition() - i_from.GetYPosition();
  double xSquared = pow(xDistance, 2);
  double ySquared = pow(yDistance, 2);
  return sqrt(ySquared + xSquared);
}

void AStarPathPlanner::AddChildrenToToBeExploredPositions(Node * i_parentNode)
{
  Position topChild = Position(i_parentNode->pos.GetXPosition(), i_parentNode->pos.GetYPosition() - 1);
  AddChild(i_parentNode, topChild);

  Position bottomChild = Position(i_parentNode->pos.GetXPosition(), i_parentNode->pos.GetYPosition() + 1);
  AddChild(i_parentNode, bottomChild);

  Position leftChild = Position(i_parentNode->pos.GetXPosition() - 1, i_parentNode->pos.GetYPosition());
  AddChild(i_parentNode, leftChild);

  Position rightChild = Position(i_parentNode->pos.GetXPosition() + 1, i_parentNode->pos.GetYPosition());
  AddChild(i_parentNode, rightChild);
}

void AStarPathPlanner::AddChild(Node * i_parentNode, Position i_childNode)
{
  if (m_gridWorld->bIsPositionValid(i_childNode) && m_gridWorld->bIsPositionOpen(i_childNode))
  {
    auto it = m_exploredPositions.find(i_childNode);
    if (it == m_exploredPositions.end())
    {
      double parentDistance = i_parentNode->distanceFromStart;
      double childParentDistance = CalculateDistance(i_parentNode->pos, i_childNode);
      Node * childNode = new Node(i_childNode, (parentDistance + childParentDistance));
      childNode->SetParent(i_parentNode);
      childNode->SetDistanceToGoal(CalculateDistance(childNode->pos, m_goalPosition));
      m_toBeExploredPositions[i_childNode] = childNode;
    }
    else
      m_toBeExploredPositions[i_childNode] = it->second;

    ConsiderCell(i_childNode);
  }
}

void AStarPathPlanner::ConsiderCell(Position i_pos)
{
  if (m_gridWorld->bIsPositionValid(i_pos) && m_gridWorld->bIsPositionOpen(i_pos))
  {
    m_gridWorld->ConsiderCell(i_pos);
    system("pause");
  }
}

Node * AStarPathPlanner::GetMinToBeExploredNode()
{
  double min = -1.0;
  Node * node = nullptr;

  auto minIt = m_toBeExploredPositions.end();

  for (auto it = m_toBeExploredPositions.begin(); it != m_toBeExploredPositions.end(); it++)
  {
    if ((min < 0) || (it->second->distanceToGoal < min))
    {
      node = it->second;
      min = node->distanceToGoal;
      minIt = it;
    }
  }

  if (minIt != m_toBeExploredPositions.end() && node)
  {
    m_toBeExploredPositions.erase(minIt);
  }

  return node;
}