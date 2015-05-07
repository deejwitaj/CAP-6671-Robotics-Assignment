#include "stdafx.h"

#include <list>
#include <iostream>
#include <fstream>

#include "PathPlanner.h"
#include "time.h"

PathPlanner::PathPlanner(bool i_bIsQLearning, double i_discountFactor, double i_learningRate) :
  m_bIsQLearning(i_bIsQLearning)
, m_bIsExploring(true)
, m_discountFactor(i_discountFactor)
, m_learningRate(i_learningRate)
{
}

double PathPlanner::CalculateNextQ(double i_reward, Position i_from, Position i_to, Action i_action, std::list<Action> i_validMoves)
{
	double OldQ = m_qMap.GetQ(i_from, i_action);
	double MaxQ = GetMaxQ(i_to, i_validMoves);
	return OldQ + (m_learningRate * (i_reward + (m_discountFactor * MaxQ) - OldQ));
}

double PathPlanner::CalculateOppositeQ(double i_reward, Position i_from, Position i_to, Action i_action, std::list<Action> i_validMoves)
{
  auto it = i_validMoves.begin();

  i_to = i_from;

  switch (i_action)
  {
  case NO_MOVE:
    return -1;
  case MOVE_UP:
    it = std::find(i_validMoves.begin(), i_validMoves.end(), MOVE_DOWN);
    i_to.MoveDown();
    break;
  case MOVE_DOWN:
    it = std::find(i_validMoves.begin(), i_validMoves.end(), MOVE_UP);
    i_to.MoveUp();
    break;
  case MOVE_LEFT:
    it = std::find(i_validMoves.begin(), i_validMoves.end(), MOVE_RIGHT);
    i_to.MoveRight();
    break;
  case MOVE_RIGHT:
    it = std::find(i_validMoves.begin(), i_validMoves.end(), MOVE_LEFT);
    i_to.MoveLeft();
    break;
  }

  if (it != i_validMoves.end())
  {
    double OldQ = m_qMap.GetQ(i_from, *it);
    double MaxQ = GetMaxQ(i_to, i_validMoves);
    return OldQ + (m_learningRate * (i_reward + ((1 - m_discountFactor) * MaxQ) - OldQ));
  }

  return -1;
}

//Updates the amount of times a cell was visited
void PathPlanner::UpdateCellVisited(Position const i_visitedCell)
{
  auto it = m_timesCellVisited.find(i_visitedCell);
  if (it == m_timesCellVisited.end())
    m_timesCellVisited[i_visitedCell] = 1;
  else
    ++m_timesCellVisited[i_visitedCell];

}

void PathPlanner::DidMove(Position i_from, Position i_to, Action i_action, double i_reward, double i_oppositeReward, std::list<Action> i_validMoves)
{
	if (m_bIsExploring)
	{
		double nextQ = CalculateNextQ(i_reward, i_from, i_to, i_action, i_validMoves);
		m_qMap.SetQ(R(i_from, i_action), nextQ);
    UpdateCellVisited(i_from);

    double oppositeQ = CalculateOppositeQ(i_oppositeReward, i_from, i_to, i_action, i_validMoves);
    if (oppositeQ >= 0)
    {
      Action oppositeAction;
      switch (i_action)
      {
      case MOVE_UP:
        oppositeAction = MOVE_DOWN;
        break;
      case MOVE_DOWN:
        oppositeAction = MOVE_UP;
        break;
      case MOVE_LEFT:
        oppositeAction = MOVE_RIGHT;
        break;
      case MOVE_RIGHT:
        oppositeAction = MOVE_LEFT;
        break;
      default:
        oppositeAction = NO_MOVE;
        break;
      }
      //m_qMap.SetQ(R(i_from, oppositeAction), oppositeQ);
      //UpdateCellVisited(i_from);
    }

	}
}

//Depending on state of planner, q learning or a star path finding, returns the next move in the seqence
Action PathPlanner::GetNextMove(Position i_from, std::list<Action> i_validMoves)
{
	Action action;
	//If we are still exploring, return the greediest move as our exploration process and update the q table
	if (m_bIsExploring)
	{
		int chance = rand() % 101;
    if (chance < 50)
      action = GetGreediestMove(i_from, i_validMoves);
		else
		{
			chance = rand() % i_validMoves.size();
			auto it = i_validMoves.begin();
			std::advance(it, chance);
			action = *it;
		}
		return action;
	}
	//Otherwise we return the maximum q value for the position we are in
	else
		return GetMaxQMove(i_from, i_validMoves);
}

//Returns the maximum q value for the position we are in
double PathPlanner::GetMaxQ(Position i_position, std::list<Action> i_validMoves) const
{
	double maxQ = 0;
	double tempQ = 0;

	for (auto it : i_validMoves)
	{
		tempQ = m_qMap.GetQ(i_position, it);
		if ((tempQ > maxQ) && (tempQ >= 0))
			maxQ = tempQ;
	}

	return maxQ;
}

//Compare current maxQ to potential Q and returns the action with the highest q value
Action PathPlanner::GetMaxQAction(double &i_maxQ, Action i_currentAction, Action i_potentialAction, Position i_position) const
{
	double tempQ = 0;

	tempQ = m_qMap.GetQ(i_position, i_potentialAction);
	if ((tempQ > i_maxQ) && (tempQ >= 0))
	{
		i_maxQ = tempQ;
		return i_potentialAction;
	}

	//If the q values are equal, then we randomly choose to either select the new potential action or stick with the curent action
	else if (tempQ == i_maxQ && i_currentAction != NO_MOVE)
	{
		int choice = rand() % 11;
		if (choice > 6)
			return i_potentialAction;
	}

	else if (tempQ == i_maxQ)
		return i_potentialAction;

	return i_currentAction;
}

//Returns the move with the highest stored q value in the q map
Action PathPlanner::GetMaxQMove(Position i_position, std::list<Action> i_validActions) const
{
	double maxQ = 0;
	Action action = NO_MOVE;

	for (auto const it : i_validActions)
		action = GetMaxQAction(maxQ, action, it, i_position);

	return action;
}

//Returns the move with the lowest stored q value in the q map
Action PathPlanner::GetMinQAction(double i_maxQ, Action i_currentAction, Action i_potentialAction, Position i_position) const
{
	double tempQ = 0;

	tempQ = m_qMap.GetQ(i_position, i_potentialAction);
	if ((tempQ < i_maxQ) && (tempQ >= 0))
	{
		i_maxQ = tempQ;
		return i_potentialAction;
	}

	//If the q values are equal, then we randomly choose to either select the new potential action or stick with the curent action
	else if (tempQ == i_maxQ && i_currentAction != NO_MOVE)
	{
		int choice = rand() % 101;
		if (choice > 50)
			return i_potentialAction;
		return i_currentAction;
	}

	else if (tempQ == i_maxQ)
		return i_potentialAction;

	return i_currentAction;
}

//Returns the move with the lowest current Q value, in accordance with the greedy learning algorithm
Action PathPlanner::GetGreediestMove(Position i_position, std::list<Action> i_validMoves) const
{
	double maxQ = 0;
  if (i_validMoves.empty())
    return NO_MOVE;

  Action action = *i_validMoves.begin();
  if (i_validMoves.size() == 1)
    return action;

  auto it = i_validMoves.begin();
  it++;
  for (; it != i_validMoves.end(); it++)
    action = GetMaxQAction(maxQ, action, *it, i_position);

	return action;
}

//Prints out the Q Map
void PathPlanner::PrintQMap()
{
	m_qMap.Print();
}

void PathPlanner::PrintTimesCellVisited()
{
  using namespace std;
  double average = 0;

  for (auto it : m_timesCellVisited)
    average += it.second;

  average = average / m_timesCellVisited.size();

  ofstream myfile("CellsVisited.txt");
  if (myfile.is_open())
  {
    myfile << "There were " << m_timesCellVisited.size() << " cells visited\n";
    myfile << "Average: " << average << "\n";

    for (auto it : m_timesCellVisited)
      myfile << "Cell: " << it.first.GetXPosition() << ',' << it.first.GetYPosition() << " " << it.second << " times\n";
  }
}