#include "stdafx.h"

#include "PathPlanner.h"

PathPlanner::PathPlanner(QMap i_qMap, bool i_bIsQLearning, double i_discountFactor, double i_learningRate) :
  m_bIsQLearning(i_bIsQLearning)
, m_bIsExploring(false)
, m_discountFactor(i_discountFactor)
, m_learningRate(i_learningRate)
, m_qMap(i_qMap)
{
}

double PathPlanner::CalculateNextQ(double i_reward, Position i_currentPosition, Action i_action)
{
	double OldQ = m_qMap.GetQ(i_currentPosition, i_action);
	double MaxQ = GetMaxQ(i_currentPosition);
	return OldQ + (m_learningRate * (i_reward + (m_discountFactor * MaxQ) - OldQ));
}

//Depending on state of planner, q learning or a star path finding, returns the next move in the seqence
Action PathPlanner::GetNextMove(Position i_position, double i_reward)
{
	Action action;
	//If we are still exploring, return the greediest move as our exploration process and update the q table
	if (m_bIsExploring)
	{
		action = GetGreediestMove(i_position);
		m_qMap.SetQ(R(i_position, action), CalculateNextQ(i_reward, i_position, action));
		return action;
	}
	//Otherwise we return the maximum q value for the position we are in
	else
		return GetMaxQMove(i_position);
}

//Returns the maximum q value for the position we are in
double PathPlanner::GetMaxQ(Position i_position) const
{
	double maxQ = 0;
	double tempQ = -1;

	tempQ = m_qMap.GetQ(i_position, MOVE_UP);
	if ((tempQ > maxQ) && (tempQ >= 0))
		maxQ = tempQ;

	tempQ = m_qMap.GetQ(i_position, MOVE_DOWN);
	if ((tempQ > maxQ) && (tempQ >= 0))
		maxQ = tempQ;

	tempQ = m_qMap.GetQ(i_position, MOVE_LEFT);
	if ((tempQ > maxQ) && (tempQ >= 0))
		maxQ = tempQ;

	tempQ = m_qMap.GetQ(i_position, MOVE_RIGHT);
	if ((tempQ > maxQ) && (tempQ >= 0))
		maxQ = tempQ;

	return maxQ;
}

//Returns the move with the highest stored q value in the q map
Action PathPlanner::GetMaxQMove(Position i_position) const
{
	double maxQ = -1;
	double tempQ = -1;
	Action action = NO_MOVE;

	tempQ = m_qMap.GetQ(i_position, MOVE_UP);
	if ((tempQ > maxQ) && (tempQ >= 0))
	{
		maxQ = tempQ;
		action = MOVE_UP;
	}

	tempQ = m_qMap.GetQ(i_position, MOVE_DOWN);
	if ((tempQ > maxQ) && (tempQ >= 0))
	{
		maxQ = tempQ;
		action = MOVE_DOWN;
	}

	tempQ = m_qMap.GetQ(i_position, MOVE_LEFT);
	if ((tempQ > maxQ) && (tempQ >= 0))
	{
		maxQ = tempQ;
		action = MOVE_LEFT;
	}

	tempQ = m_qMap.GetQ(i_position, MOVE_RIGHT);
	if ((tempQ > maxQ) && (tempQ >= 0))
	{
		maxQ = tempQ;
		action = MOVE_RIGHT;
	}

	return action;
}
//Returns the move with the lowest current Q value, in accordance with the greedy learning algorithm
Action PathPlanner::GetGreediestMove(Position i_position) const
{
	double minQ = -1;
	double tempQ = -1;
	Action action = NO_MOVE;

	tempQ = m_qMap.GetQ(i_position, MOVE_UP);
	if ((tempQ < minQ) && (tempQ >= 0))
	{
		minQ = tempQ;
		action = MOVE_UP;
	}

	tempQ = m_qMap.GetQ(i_position, MOVE_DOWN);
	if ((tempQ < minQ) && (tempQ >= 0))
	{
		minQ = tempQ;
		action = MOVE_DOWN;
	}

	tempQ = m_qMap.GetQ(i_position, MOVE_LEFT);
	if ((tempQ < minQ) && (tempQ >= 0))
	{
		minQ = tempQ;
		action = MOVE_LEFT;
	}

	tempQ = m_qMap.GetQ(i_position, MOVE_RIGHT);
	if ((tempQ < minQ) && (tempQ >= 0))
	{
		minQ = tempQ;
		action = MOVE_RIGHT;
	}

	return action;
}