#include "stdafx.h"

#include "Robot.h"

Robot::Robot(PathPlanner i_planner) :
	m_lastMove(NO_MOVE)
{
}

Action Robot::GetNextMove(Position i_current, std::list<Action> i_validMoves)
{
	m_lastMove = m_pathPlanner.GetNextMove(i_current, i_validMoves);
	return m_lastMove;
}

void Robot::ProcessMove(Position i_from, Position i_to, double i_reward, std::list<Action> i_validMoves)
{
	m_pathPlanner.DidMove(i_from, i_to, m_lastMove, i_reward, i_validMoves);
}